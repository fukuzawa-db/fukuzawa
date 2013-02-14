#ifndef __SCANHASH_H
#define __SCANHASH_H

#include<iostream>
#include<cstdlib>
#include<string>
#include<db_cxx.h>

#include"Operator.h"
#include"BDBOpe.h"
#include"InMemDB.h"
#include"CommonDataDef.h"

class ScanHash : public Operator{
	public:
		ScanHash(BDBOpe *db_, ATTRIBUTE_REC *attrIRec_, unsigned int attriNum_);
		ScanHash(BDBOpe *db_, ATTRIBUTE_REC **attrIRec_, unsigned int attriNum_);
		virtual ~ScanHash();
		virtual void init(DbEnv *env_);
		virtual int getRow(PosVal **pv_, unsigned int pvNum_);
		virtual unsigned int getAttriNum(void);
		virtual void getAttriRec(ATTRIBUTE_REC **attriRec_, unsigned int attriNum_);

		void resetGetPos(void);
		void setHashkey(unsigned int hashkey);
	
	private:
		void setPosVal(PosVal **pv_, unsigned int pvNum_);


		BDBOpe *db;
		int initFlag;
		Dbt key, data;
};

#endif
