#ifndef __ATTRIBUTEMANAGER_H
#define __ATTRIBUTEMANAGER_H


#include<iostream>
#include<cstring>
#include<db_cxx.h>


#include"CommonDataDef.h"
#include"BDBOpe.h"

#define ATTRIBUTE_MANEGE_FILE 		("ATTRIBUTE_MANEGE_FILE")
#define BDB_ATTRIBUTE_MANEGE_FILE 	("BDB_ATTRIBUTE_MANEGE_FILE.db")

using namespace std;

class AttributeManager
{
	public:
		AttributeManager();
		AttributeManager(DbEnv *env_);
		~AttributeManager();
		int writeRecord(ATTRIBUTE_REC *attributeRec_);
		int getForTableID(TABLE_REC tableRec_, ATTRIBUTE_REC *attriRec_);
		
		inline void dump()
		{
			assert(db != NULL);
			db->dumpDB();
		}
		void showAllRecord();

	private:
		string 	attributeFileName;
		string 	dbAttributeFileName;
		BDBOpe	*db;
};


#endif

