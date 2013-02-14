#ifndef __INMEMDB_H
#define __INMEMDB_H

#include<db_cxx.h>
#include<cstdlib>
#include<cstring>
#include<cassert>
#include<fstream>

using namespace std;

int compare_int_InMem(Db *dbp, const Dbt *a, const Dbt *b);


class InMemDB
{
	public:
		InMemDB(DbEnv *env_, string bdbFileName_);
		InMemDB(DbEnv *env_, string bdbFileName_, bool isUnique_);
		~InMemDB();
		
		int open();
		int close();
		
		int writeRecord(void *key_, unsigned int keySize_, void *data_, unsigned int dataSize_, bool allowOverWrote);

		int readFirstRecord(Dbt *key_, Dbt *data_);
		int readNextRecord(Dbt *key_, Dbt *data_);
		int readDupFirstRecord(Dbt *key_, Dbt *data_);
		int readDupNextRecord(Dbt *key_, Dbt *data_);
		int readForKey(Dbt *key_, Dbt *data_);

		inline Db *getDb() {return dbHandle;}
		
		//void printMemSize();
		void setDupCompare();
		

	private:
		Db *dbHandle;
		Dbc *dbCursor;
		DbEnv *env;
		u_int32_t	dbFlags;
		char tmpFileName[L_tmpnam + 1];
		string dbLogicalName;
		AccessMethod accessMethod;

		bool isUnique;
		void init(string bdbFileName_, bool isUnique_);
		void openCursor();
		void closeCursor();

		void setNumCmp();
};		

#endif
