#include<iostream>
#include<fstream>
#include<string>
#include<db_cxx.h>
#include<cassert>
#include <db.h>

#include"CommonDataDef.h"
#include"BDBOpe.h"

using namespace std;


BDBOpe::BDBOpe(string bdbFileName_) : accessMethod(BTREE)
{
	env = NULL;
	this->init(env, bdbFileName_, true);
}

BDBOpe::BDBOpe(string bdbFileName_, bool isUnique_) : accessMethod(BTREE)
{
	env = NULL;
	this->init(env, bdbFileName_, isUnique_);
}

BDBOpe::BDBOpe(string bdbFileName_, bool isUnique_, AccessMethod accessMethod_)
{
	
	accessMethod = accessMethod_;
	env = NULL;
	this->init(env, bdbFileName_, isUnique_);
}

BDBOpe::BDBOpe(DbEnv *env_, string bdbFileName_) : accessMethod(BTREE)
{
	env = env_;
	this->init(env, bdbFileName_, true);
}

BDBOpe::BDBOpe(DbEnv *env_, string bdbFileName_, bool isUnique_) : accessMethod(BTREE)
{
	env = env_;
	this->init(env, bdbFileName_, isUnique_);
}

BDBOpe::BDBOpe(DbEnv *env_, string bdbFileName_, bool isUnique_, AccessMethod accessMethod_)
{
	accessMethod = accessMethod_;
	env = env_;
	this->init(env, bdbFileName_, isUnique_);
}


void BDBOpe::init(DbEnv *env_, string bdbFileName_, bool isUnique_)
{
	isUnique = isUnique_;
	bdbFileName = bdbFileName_;
	dbHandle = new Db(env_, 0);
	dbHandle->set_error_stream(&cerr);
	if(!isUnique)	dbHandle->set_flags(DB_DUP);
	setNumCmp();
}

BDBOpe::~BDBOpe()
{
	delete dbHandle;
}

void BDBOpe::associate(Db *db_, int (*pfunc_)(Db *sdbp, const Dbt *pkey, const Dbt *pdata, Dbt *skey)){
	dbHandle->associate(NULL, db_, pfunc_, 0);
}							

int BDBOpe::open(){
	return open(1);
}


int BDBOpe::open(int cursuropen_)
{
	assert(dbHandle != NULL);
	dbFlags = DB_CREATE;
	try{
		
		if(env == NULL){
		//Set page size
			dbHandle->set_pagesize(BDB_PAGE_SIZE);
		//Set cache size
			dbHandle->set_cachesize(BDB_CACHE_SIZE_GBYTE, BDB_CACHE_SIZE_BYTE, 0);
		}
		
		if(accessMethod == BTREE){
			dbHandle->open(
				NULL,
				bdbFileName.c_str(),
				NULL,
				DB_BTREE,
				dbFlags,
				0664
			);
		//	cout << "access Btree" << endl;
		}
		else if(accessMethod == QUEUE){
			dbHandle->open(
				NULL,
				bdbFileName.c_str(),
				NULL,
				DB_QUEUE,
				dbFlags,
				0664
			);
		//	cout << "access Queue" << endl;
		}
		else{
			cout << "BDB open Error" << endl;
			exit (EXIT_FAILURE);
		}
		if(cursuropen_ == 1){
			this->openCursor();
		}
	}catch (DbException &e){
		cout << "ERROR BDB open" << endl;
		return e.get_errno();
	}catch (std::exception &e){
//		throw UnexpectedException("BDBOpe.cpp: Failed on open");
	}
	
	
	return 0;
}

int BDBOpe::reopen()
{
	assert(dbHandle != NULL);
	delete dbHandle;
	dbHandle = new Db(env, 0);
	dbHandle->set_error_stream(&cerr);
	if(!isUnique)	dbHandle->set_flags(DB_DUP);
	setNumCmp();
	
		
	dbFlags = DB_CREATE;
	try{
		if(accessMethod == BTREE){
			dbHandle->open(
				NULL,
				bdbFileName.c_str(),
				NULL,
				DB_BTREE,
				dbFlags,
				0664
			);
		//	cout << "access Btree" << endl;
		}
		else if(accessMethod == QUEUE){
			dbHandle->open(
				NULL,
				bdbFileName.c_str(),
				NULL,
				DB_QUEUE,
				dbFlags,
				0664
			);
		//	cout << "access Queue" << endl;
		}
		else{
			cout << "BDB open Error" << endl;
			exit (EXIT_FAILURE);
		}
		this->openCursor();
	}catch (DbException &e){
		cout << "ERROR BDB open" << endl;
		return e.get_errno();
	}catch (std::exception &e){
//		throw UnexpectedException("BDBOpe.cpp: Failed on open");
	}
	return 0;
}

int BDBOpe::close()
{
	assert(dbHandle != NULL);
	this->closeCursor();
	return dbHandle->close(0);
}

void BDBOpe::openCursor()
{
	assert(dbHandle != NULL);
	dbHandle->cursor(NULL, &dbCursor, 0);
}

void BDBOpe::closeCursor()
{
	if(dbCursor != NULL) dbCursor->close();
}

int BDBOpe::flush()
{
	assert(dbHandle != NULL);
	return dbHandle->sync(0);
}

int BDBOpe::remove(){
	assert(dbHandle != NULL);
	delete dbHandle;
	dbHandle = new Db(NULL, 0);
	dbHandle->set_error_stream(&cerr);
	if(!isUnique)	dbHandle->set_flags(DB_DUP);
	setNumCmp();
	return dbHandle->remove(bdbFileName.c_str(), NULL, 0);
}


int BDBOpe::writeRecord(void *key_, unsigned int keySize_, void *data_, unsigned int dataSize_, bool allowOverwrite_)
{
	assert(dbHandle != NULL);

	Dbt key(key_, keySize_);
	Dbt data(data_, dataSize_);

	int returnCode;
	u_int32_t flags=0;

	if(!allowOverwrite_) flags = DB_NOOVERWRITE;
	try{
		returnCode = dbHandle->put(NULL, &key, &data, flags);
		if(returnCode != 0){
			dbHandle->err(returnCode, "DBDOpe::writeRecord");
			if(returnCode == DB_REP_HANDLE_DEAD){
				cout << "The database handle has been invalidated!" << endl;
			}else if(returnCode == DB_SECONDARY_BAD){
				cout << "A secondary index references a nonexistent primary key!" << endl;
			}else{
				cout << "EINVAL" << endl;
			}
		}
	}catch(DbException &e){
		cout << "DbException " << e.what() << endl;
		throw;
	}
	return returnCode;
}
/*
int BDBOpe::writeJoinIndex(string fileName_){
	assert(accessMethod == QUEUE);

	int lineNum;
	ifstream ifs(fileName.c_str());
	
	if >> lineNum;
	while(!ifs.eof()){
		dbHandle
*/		

int BDBOpe::readFirstRecord(Dbt *key_, Dbt *data_)
{
	int returnCode;
	try{
		returnCode = dbCursor->get(key_, data_, DB_FIRST);
		if(returnCode > 0) dbHandle->err(returnCode, "BDBOpe::dumpDB");
	}
	catch(DbException &dbe){
		cout << "BDBOpe::dump " << dbe.what() << endl;
	}
	return returnCode;
}

int BDBOpe::readNextRecord(Dbt *key_, Dbt *data_)
{
	int returnCode;
	try{
		returnCode = dbCursor->get(key_, data_, DB_NEXT);
		if(returnCode > 0) dbHandle->err(returnCode, "BDBOpe::dumpDB");
	}
	catch(DbException &dbe){
		cout << "BDBOpe::dump " << dbe.what() << endl;
	}
	return returnCode;
}


int BDBOpe::readDupFirstRecord(Dbt *key_, Dbt *data_)
{
	int returnCode;
	try{
		returnCode = dbCursor->get(key_, data_, DB_SET);
		if(returnCode > 0) dbHandle->err(returnCode, "BDBOpe::dumpDB");
	}
	catch(DbException &dbe){
		cout << "BDBOpe::dump " << dbe.what() << endl;
	}
	return returnCode;
}


int BDBOpe::readDupNextRecord(Dbt *key_, Dbt *data_)
{
	int returnCode;
	try{
		returnCode = dbCursor->get(key_, data_, DB_NEXT_DUP);
		if(returnCode > 0) dbHandle->err(returnCode, "BDBOpe::dumpDB");
	}
	catch(DbException &dbe){
		cout << "BDBOpe::dump " << dbe.what() << endl;
	}
	return returnCode;
}


int BDBOpe::readRangeRecord(Dbt *key_, Dbt *data_)
{
	int returnCode;
	try{
		returnCode = dbCursor->get(key_, data_, DB_SET_RANGE);
		if(returnCode > 0) dbHandle->err(returnCode, "BDBOpe::dumpDB");
	}
	catch(DbException &dbe){
		cout << "BDBOpe::dump " << dbe.what() << endl;
	}
	return returnCode;
}

int BDBOpe::readForKey(Dbt *key_, Dbt *data_)
{
	int returnCode;

	returnCode = dbHandle->get(NULL, key_, data_, 0);
	return false;
}



void BDBOpe::showRecordCount()
{
	DB_BTREE_STAT *pStat;

	if(0 != dbHandle->stat( NULL,&pStat, 0)){
		cout << "Error BDBOpe" << endl;
		exit(1);
	}
	//dbHandle->stat(&pStat, 0);
	cout << bdbFileName << " contains " << pStat->bt_ndata << " records\n";
	
	//dbHandle->stat_print(0);
	free(pStat);
}

u_long BDBOpe::getRecordCount()
{
	DB_BTREE_STAT *pStat;

	dbHandle->stat(NULL, &pStat, 0);
	u_long cnt = pStat->bt_ndata;
	free(pStat);
	return cnt;
}

void BDBOpe::dumpDB()
{
	cout << "\n\n========== dump of " << bdbFileName << " =========\n" << endl;

	try{
		Dbc *dbcp;
		dbHandle->cursor(NULL, &dbcp, 0);

		Dbt key;
		Dbt data;
		int returnCode = 0;
		int count = 0;
		while((returnCode = dbcp->get(&key, &data, DB_NEXT) == 0)){
			char c[1024];
			int *key_string = (int *)key.get_data();
			char *data_string = (char *)data.get_data();
			strcpy(c,(char *)data.get_data());
			cout << *key_string << " : " << data_string << endl;
			cout << c << endl;
			++count;
		}
		if(returnCode > 0) dbHandle->err(returnCode, "BDBOpe::dumpDB");
		dbcp->close();
		cout << "\n\n========== total of " << count << " records =========\n" << endl;
	}
	catch(DbException &dbe){
		cout << "BDBOpe::dump " <<dbe.what() << endl;
	}
}
/*
void BDBOpe::printMemSize(){

}
*/

void BDBOpe::setNumCmp(){
	dbHandle->set_bt_compare(compare_int);
}

int compare_int(Db *dbp, const Dbt *a, const Dbt *b){
	int ai, bi;
	memcpy(&ai, a->get_data(), sizeof(int));
	memcpy(&bi, b->get_data(), sizeof(int));
	return (ai-bi);
}


void BDBOpe::setLongCmp(){
	dbHandle->set_bt_compare(compare_long);
}
int compare_long(Db *dbp, const Dbt *a, const Dbt *b){
	long al, bl;
	memcpy(&al, a->get_data(), sizeof(int));
	memcpy(&bl, b->get_data(), sizeof(int));
	return (al-bl);
}


void BDBOpe::setFloatCmp(){
	dbHandle->set_bt_compare(compare_float);
}
int compare_float(Db *dbp, const Dbt *a, const Dbt *b){
	float af, bf;
	memcpy(&af, a->get_data(), sizeof(int));
	memcpy(&bf, b->get_data(), sizeof(int));
	return (af-bf);
}


void BDBOpe::setDoubleCmp(){
	dbHandle->set_bt_compare(compare_double);
}
int compare_double(Db *dbp, const Dbt *a, const Dbt *b){
	double ad, bd;
	memcpy(&ad, a->get_data(), sizeof(int));
	memcpy(&bd, b->get_data(), sizeof(int));
	return (ad-bd);
}


void BDBOpe::setfStrCmp(){
	dbHandle->set_bt_compare(compare_fstr);
}
int compare_fstr(Db *dbp, const Dbt *a, const Dbt *b){
	return (strncmp((char *)a->get_data(), (char *)b->get_data(), a->get_size()));
}


void BDBOpe::setvStrCmp(){
	dbHandle->set_bt_compare(compare_vstr);
}
int compare_vstr(Db *dbp, const Dbt *a, const Dbt *b){
	return (strcmp((char *)a->get_data(), (char *)b->get_data()));
}


void BDBOpe::setDupCompare()
{
	dbHandle->set_dup_compare(compare_pos);
}

int compare_pos(Db *dbp, const Dbt *a, const Dbt *b){
	unsigned int ai, bi;
	memcpy(&ai, a->get_data(), sizeof(unsigned int));
	memcpy(&bi, b->get_data(), sizeof(unsigned int));
	return (ai - bi);
}
