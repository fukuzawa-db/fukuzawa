#ifndef __SECONDDB_H
#define __SECONDDB_H

#include<db_cxx.h>
#include<cstdlib>
#include<cstring>
#include<cassert>
#include<fstream>
#include<iostream>

#include"CommonDataDef.h"
#include"BDBOpe.h"

using namespace std;

class SecondDB : public BDBOpe
{
	public:
		SecondDB(string bdbFileName_);
		SecondDB(string bdbFileName_, bool isUnique_);
		SecondDB(string bdbFileName_, bool isUnique_, AccessMethod accessMethod_);
		SecondDB(DbEnv *env_, string bdbFileName_);
		SecondDB(DbEnv *env_, string bdbFileName_, bool isUnique_);
		SecondDB(DbEnv *env_, string bdbFileName_, bool isUnique_, AccessMethod accessMethod_);
		~SecondDB();
		
		int open();
		int open(int cursuropen_);
		void openCursor();
		int reopen();
		int close();

		int flush();
		int remove();
		
		int writeRecord(void *key_, unsigned int keySize_, void *data_, unsigned int dataSize_, bool allowOverWrote);
		//int writeJoinIndex(string fileName_);
		int readFirstRecord(Dbt *key_, Dbt *data_);
		int readNextRecord(Dbt *key_, Dbt *data_);
		int readDupFirstRecord(Dbt *key_, Dbt *data_);
		int readDupNextRecord(Dbt *key_, Dbt *data_);
		int readForKey(Dbt *key_, Dbt *data_);

		inline Db *getDb() {return dbHandle;}
		void showRecordCount();
		u_long getRecordCount();

		void dumpDB();
		//void printMemSize();
		void setDupCompare();

	protected:

		bool isUnique;
		void init(DbEnv *env_, string bdbFileName_, bool isUnique_);
		void closeCursor();

};		

#endif
