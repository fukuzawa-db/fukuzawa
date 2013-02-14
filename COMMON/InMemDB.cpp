#include<iostream>
#include<fstream>
#include<string>
#include<db_cxx.h>
#include<cassert>
#include <db.h>

#include"CommonDataDef.h"
#include"InMemDB.h"

using namespace std;

InMemDB::InMemDB(DbEnv *env_, string bdbFileName_) : accessMethod(BTREE)
{
	env = env_;
	this->init(bdbFileName_, true);
}

InMemDB::InMemDB(DbEnv *env_, string bdbFileName_, bool isUnique_) : accessMethod(BTREE)
{
	env = env_;
	this->init(bdbFileName_, isUnique_);
}

void InMemDB::init(string bdbFileName_, bool isUnique_)
{
	isUnique = isUnique_;
	dbLogicalName = bdbFileName_;
	dbHandle = new Db(env, 0);
	dbHandle->set_error_stream(&cerr);
	if(!isUnique)	dbHandle->set_flags(DB_DUP);
	setNumCmp();
}

InMemDB::~InMemDB()
{
	delete dbHandle;
}


int InMemDB::open()
{
	assert(dbHandle != NULL);
	dbFlags = DB_CREATE;
	try{
	//Set page size
		dbHandle->set_pagesize(BDB_PAGE_SIZE);
	/*
	//Set cache size
		dbHandle->set_cachesize(BDB_CACHE_SIZE_GBYTE, BDB_CACHE_SIZE_BYTE, 0);
	*/	
		if(accessMethod == BTREE){
			dbHandle->open(
				NULL,
				NULL,
				dbLogicalName.c_str(),
				DB_BTREE,
				dbFlags,
				0
			);
		//	cout << "access Btree" << endl;
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
//		throw UnexpectedException("InMemDB.cpp: Failed on open");
	}
	return 0;
}

int InMemDB::close()
{
	assert(dbHandle != NULL);
	this->closeCursor();
	return dbHandle->close(0);
}

void InMemDB::openCursor()
{
	assert(dbHandle != NULL);
	dbHandle->cursor(NULL, &dbCursor, 0);
}

void InMemDB::closeCursor()
{
	if(dbCursor != NULL) dbCursor->close();
}

int InMemDB::writeRecord(void *key_, unsigned int keySize_, void *data_, unsigned int dataSize_, bool allowOverwrite_)
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

int InMemDB::readNextRecord(Dbt *key_, Dbt *data_)
{
	int returnCode;
	try{
		returnCode = dbCursor->get(key_, data_, DB_NEXT);
		if(returnCode > 0) dbHandle->err(returnCode, "InMemDB::dumpDB");
	}
	catch(DbException &dbe){
		cout << "InMemDB::dump " << dbe.what() << endl;
	}
	return returnCode;
}


int InMemDB::readDupFirstRecord(Dbt *key_, Dbt *data_)
{
	int returnCode;
	try{
		returnCode = dbCursor->get(key_, data_, DB_SET);
		if(returnCode > 0) dbHandle->err(returnCode, "InMemDB::dumpDB");
	}
	catch(DbException &dbe){
		cout << "InMemDB::dump " << dbe.what() << endl;
	}
	return returnCode;
}


int InMemDB::readDupNextRecord(Dbt *key_, Dbt *data_)
{
	int returnCode;
	try{
		returnCode = dbCursor->get(key_, data_, DB_NEXT_DUP);
		if(returnCode > 0) dbHandle->err(returnCode, "InMemDB::dumpDB");
	}
	catch(DbException &dbe){
		cout << "InMemDB::dump " << dbe.what() << endl;
	}
	return returnCode;
}


int InMemDB::readForKey(Dbt *key_, Dbt *data_)
{
	int returnCode;

	returnCode = dbHandle->get(NULL, key_, data_, 0);
	return false;
}



void InMemDB::setNumCmp(){
	dbHandle->set_bt_compare(compare_int_InMem);
}

int compare_int_InMem(Db *dbp, const Dbt *a, const Dbt *b){
	int ai, bi;
	memcpy(&ai, a->get_data(), sizeof(int));
	memcpy(&bi, b->get_data(), sizeof(int));
	return (ai-bi);
}


