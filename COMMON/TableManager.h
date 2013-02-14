#ifndef __TABLEMANAGER_H
#define __TABLEMANAGER_H


#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cassert>
#include<db_cxx.h>

#include"CommonDataDef.h"
#include"BDBOpe.h"

#define TABLE_MANEGE_FILE 		("TABLE_MANEGE_FILE")
#define BDB_TABLE_MANEGE_FILE 	("BDB_TABLE_MANEGE_FILE.db")

using namespace std;

class TableManager
{
	public:
		TableManager();
		TableManager(DbEnv *env_);
		~TableManager();

		inline unsigned int getNextID()
		{
			assert(db != NULL);
			return ((unsigned int)db->getRecordCount() + 1);
		}
		inline void showRecordCount()
		{
			db->showRecordCount();
		}
		int writeRecord(TABLE_REC *tableRec_);
		void showAllRecord();


		inline void dump()
		{
			assert(db != NULL);
			db->dumpDB();
		}

	private:
		string 	tableFileName;
		string 	dbTableFileName;
		BDBOpe	*db;
		Dbt *key,*data;
};


#endif

