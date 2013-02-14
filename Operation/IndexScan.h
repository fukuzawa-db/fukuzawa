#ifndef __INDEXSCAN_H__
#define __INDEXSCAN_H__

#include<iostream>
#include<cstdlib>
#include<string>
#include<db_cxx.h>

#include"Operator.h"
#include"BDBOpe.h"
#include"CommonDataDef.h"

class IndexScan : public Operator{
	public:
		IndexScan(BDBOpe *db_, ATTRIBUTE_REC *attriRec_, unsigned int attriNum_);
		virtual ~IndexScan();
		virtual void init(DbEnv *env_);
		virtual int getRow(PosVal **pv_, unsigned int pvNum_);
		virtual unsigned int getAttriNum(void);
		virtual void getAttriRec(ATTRIBUTE_REC **attriRec_, unsigned int attriNum_);
		
		void keySet(PosVal *skey_);
		
	private:
		void setPosVal(PosVal **pv_, unsigned int pvNum_);
		
		BDBOpe *db;
		int initFlag;
		int getFlag;	
		Dbt key;
		Dbt data;
};

#endif
