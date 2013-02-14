#include"SecondDB.h"

using namespace std;


SecondDB::SecondDB(string bdbFileName_)
{
	accessMethod = BTREE;
	env = NULL;
	this->init(env, bdbFileName_, false);
}

SecondDB::SecondDB(string bdbFileName_, bool isUnique_)
{
	accessMethod = BTREE;
	env = NULL;
	this->init(env, bdbFileName_, isUnique_);
}

SecondDB::SecondDB(string bdbFileName_, bool isUnique_, AccessMethod accessMethod_)
{
	
	accessMethod = accessMethod_;
	env = NULL;
	this->init(env, bdbFileName_, isUnique_);
}

SecondDB::SecondDB(DbEnv *env_, string bdbFileName_)
{
	accessMethod = BTREE;
	env = env_;
	this->init(env, bdbFileName_, false);
}

SecondDB::SecondDB(DbEnv *env_, string bdbFileName_, bool isUnique_)
{
	accessMethod = BTREE;
	env = env_;
	this->init(env, bdbFileName_, isUnique_);
}

SecondDB::SecondDB(DbEnv *env_, string bdbFileName_, bool isUnique_, AccessMethod accessMethod_)
{
	accessMethod = accessMethod_;
	env = env_;
	this->init(env, bdbFileName_, isUnique_);
}


void SecondDB::init(DbEnv *env_, string bdbFileName_, bool isUnique_)
{
	isUnique = isUnique_;
	bdbFileName = bdbFileName_;
	dbHandle = new Db(env_, 0);
	dbHandle->set_error_stream(&cerr);
	if(!isUnique){
		dbHandle->set_flags(DB_DUP);
		dbHandle->set_flags(DB_DUPSORT);
	}
}

SecondDB::~SecondDB()
{
	delete dbHandle;
}

int SecondDB::open(){
	return this->open(1);
}


int SecondDB::open(int cursuropen_)
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
//		throw UnexpectedException("SecondDB.cpp: Failed on open");
	}
	
	
	return 0;
}

int SecondDB::reopen()
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
//		throw UnexpectedException("SecondDB.cpp: Failed on open");
	}
	return 0;
}

int SecondDB::close()
{
	assert(dbHandle != NULL);
	this->closeCursor();
	return dbHandle->close(0);
}

void SecondDB::openCursor()
{
	assert(dbHandle != NULL);
	dbHandle->cursor(NULL, &dbCursor, 0);
}

void SecondDB::closeCursor()
{
	if(dbCursor != NULL) dbCursor->close();
}

int SecondDB::flush()
{
	assert(dbHandle != NULL);
	return dbHandle->sync(0);
}

int SecondDB::remove(){
	assert(dbHandle != NULL);
	delete dbHandle;
	dbHandle = new Db(NULL, 0);
	dbHandle->set_error_stream(&cerr);
	if(!isUnique)	dbHandle->set_flags(DB_DUP);
	setNumCmp();
	return dbHandle->remove(bdbFileName.c_str(), NULL, 0);
}


int SecondDB::writeRecord(void *key_, unsigned int keySize_, void *data_, unsigned int dataSize_, bool allowOverwrite_)
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
int SecondDB::writeJoinIndex(string fileName_){
	assert(accessMethod == QUEUE);

	int lineNum;
	ifstream ifs(fileName.c_str());
	
	if >> lineNum;
	while(!ifs.eof()){
		dbHandle
*/		

int SecondDB::readFirstRecord(Dbt *key_, Dbt *data_)
{
	int returnCode;
	try{
		returnCode = dbCursor->get(key_, data_, DB_FIRST);
		if(returnCode > 0) dbHandle->err(returnCode, "SecondDB::dumpDB");
	}
	catch(DbException &dbe){
		cout << "SecondDB::dump " << dbe.what() << endl;
	}
	return returnCode;
}

int SecondDB::readNextRecord(Dbt *key_, Dbt *data_)
{
	int returnCode;
	try{
		returnCode = dbCursor->get(key_, data_, DB_NEXT);
		if(returnCode > 0) dbHandle->err(returnCode, "SecondDB::dumpDB");
	}
	catch(DbException &dbe){
		cout << "SecondDB::dump " << dbe.what() << endl;
	}
	return returnCode;
}


int SecondDB::readDupFirstRecord(Dbt *key_, Dbt *data_)
{
	int returnCode;
	try{
		returnCode = dbCursor->get(key_, data_, DB_SET);
		if(returnCode > 0) dbHandle->err(returnCode, "SecondDB::dumpDB");
	}
	catch(DbException &dbe){
		cout << "SecondDB::dump " << dbe.what() << endl;
	}
	return returnCode;
}


int SecondDB::readDupNextRecord(Dbt *key_, Dbt *data_)
{
	int returnCode;
	try{
		returnCode = dbCursor->get(key_, data_, DB_NEXT_DUP);
		if(returnCode > 0) dbHandle->err(returnCode, "SecondDB::dumpDB");
	}
	catch(DbException &dbe){
		cout << "SecondDB::dump " << dbe.what() << endl;
	}
	return returnCode;
}


int SecondDB::readForKey(Dbt *key_, Dbt *data_)
{
	int returnCode;

	returnCode = dbHandle->get(NULL, key_, data_, 0);
	return false;
}



void SecondDB::showRecordCount()
{
	DB_BTREE_STAT *pStat;

	if(0 != dbHandle->stat( NULL,&pStat, 0)){
		cout << "Error SecondDB" << endl;
		exit(1);
	}
	//dbHandle->stat(&pStat, 0);
	cout << bdbFileName << " contains " << pStat->bt_ndata << " records\n";
	
	//dbHandle->stat_print(0);
	free(pStat);
}

u_long SecondDB::getRecordCount()
{
	DB_BTREE_STAT *pStat;

	dbHandle->stat(NULL, &pStat, 0);
	u_long cnt = pStat->bt_ndata;
	free(pStat);
	return cnt;
}

void SecondDB::dumpDB()
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
		if(returnCode > 0) dbHandle->err(returnCode, "SecondDB::dumpDB");
		dbcp->close();
		cout << "\n\n========== total of " << count << " records =========\n" << endl;
	}
	catch(DbException &dbe){
		cout << "SecondDB::dump " <<dbe.what() << endl;
	}
}

