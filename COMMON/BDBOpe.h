#ifndef __BDBOpe_H
#define __BDBOpe_H

#include<db_cxx.h>
#include<cstdlib>
#include<cstring>
#include<cassert>
#include<fstream>

#include"IndexExtract.h"

using namespace std;

int compare_int(Db *dbp, const Dbt *a, const Dbt *b);
int compare_long(Db *dbp, const Dbt *a, const Dbt *b);
int compare_float(Db *dbp, const Dbt *a, const Dbt *b);
int compare_double(Db *dbp, const Dbt *a, const Dbt *b);
int compare_fstr(Db *dbp, const Dbt *a, const Dbt *b);
int compare_vstr(Db *dbp, const Dbt *a, const Dbt *b);
int compare_pos(Db *dbp, const Dbt *a, const Dbt *b);

class BDBOpe
{
	public:
		BDBOpe(){}
		BDBOpe(string bdbFileName_);
		BDBOpe(string bdbFileName_, bool isUnique_);
		BDBOpe(string bdbFileName_, bool isUnique_, AccessMethod accessMethod_);
		BDBOpe(DbEnv *env_, string bdbFileName_);
		BDBOpe(DbEnv *env_, string bdbFileName_, bool isUnique_);
		BDBOpe(DbEnv *env_, string bdbFileName_, bool isUnique_, AccessMethod accessMethod_);
		~BDBOpe();
		
		void associate(Db *db_, int (*pfunc_)(Db *sdbp, const Dbt *pkey, const Dbt *pdata, Dbt *skey));
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
		int readRangeRecord(Dbt *key_, Dbt *data_);
		int readForKey(Dbt *key_, Dbt *data_);

		inline Db *getDb() {return dbHandle;}
		void showRecordCount();
		u_long getRecordCount();

		void dumpDB();
		//void printMemSize();
		void setDupCompare();
		
		void setNumCmp();
		void setLongCmp();
		void setFloatCmp();
		void setDoubleCmp();
		void setfStrCmp();
		void setvStrCmp();

	protected:
		Db *dbHandle;
		Dbc *dbCursor;
		DbEnv *env;
		u_int32_t	dbFlags;
		string bdbFileName;
		AccessMethod accessMethod;

		bool isUnique;
		void init(DbEnv *env_, string bdbFileName_, bool isUnique_);
		void closeCursor();

		
};		

#endif
