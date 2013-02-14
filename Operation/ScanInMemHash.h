#ifndef __SCANINMEMHASH_H
#define __SCANINMEMHASH_H

#include<iostream>
#include<cstdlib>
#include<string>
#include<db_cxx.h>

#include"Operator.h"
#include"InMemDB.h"
#include"CommonDataDef.h"

class ScanInMemHash : public Operator{
	public:
		ScanInMemHash(InMemDB *db_, ATTRIBUTE_REC *attrIRec_, unsigned int attriNum_);
		ScanInMemHash(InMemDB *db_, ATTRIBUTE_REC **attrIRec_, unsigned int attriNum_);
		virtual ~ScanInMemHash();
		virtual void init(DbEnv *env_);
		virtual int getRow(PosVal **pv_, unsigned int pvNum_);
		virtual unsigned int getAttriNum(void);
		virtual void getAttriRec(ATTRIBUTE_REC **attriRec_, unsigned int attriNum_);

		void resetGetPos(void);
		void setHashkey(unsigned int hashkey);
	
	private:
		void setPosVal(PosVal **pv_, unsigned int pvNum_);


		InMemDB *db;
		int initFlag;
		unsigned int hashKey;
		Dbt key, data;
};

#endif
