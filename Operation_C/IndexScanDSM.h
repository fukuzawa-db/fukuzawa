#ifndef __INDEXSCANDSM_H__
#define __INDEXSCANDSM_H__

#include<iostream>
#include<cstdlib>
#include<string>
#include<db_cxx.h>

#include"Operator.h"
#include"BDBOpe.h"
#include"CommonDataDef.h"

class IndexScanDSM : public Operator{
	public:
		IndexScanDSM(BDBOpe *db_, PosVal *skey_, ATTRIBUTE_REC *attriRec_, unsigned int attriNum_);
		virtual ~IndexScanDSM();
		virtual void init(DbEnv *env_);
		virtual int getRow(PosVal **pv_, unsigned int pvNum_);
		virtual unsigned int getAttriNum(void);
		virtual void getAttriRec(ATTRIBUTE_REC **attriRec_, unsigned int attriNum_);
		
	private:
		void setPosVal(PosVal **pv_, unsigned int pvNum_);
		
		BDBOpe *db;
		int initFlag;
		int getFlag;	
		Dbt key, data;
		PosVal *skey;

};

#endif
