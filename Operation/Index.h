#ifndef __INDEX_H__
#define __INDEX_H__

#include<iostream>
#include<cstdlib>
#include<string>
#include<db_cxx.h>

#include"Operator.h"
#include"BDBOpe.h"
#include"CommonDataDef.h"

class Index : public Operator{
	public:
		Index(BDBOpe *db_, PosVal *skey_, ATTRIBUTE_REC *attriRec_, unsigned int attriNum_);
		virtual ~Index();
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
