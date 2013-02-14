#ifndef __KEYINDEX_H__
#define __KEYINDEX_H__

#include<iostream>
#include<cstdlib>
#include<string>
#include<db_cxx.h>

#include"Operator.h"
#include"BDBOpe.h"
#include"CommonDataDef.h"

class KeyIndex : public Operator{
	public:
		KeyIndex(BDBOpe *db_, Operator *keyOpe_, ATTRIBUTE_REC *attriRec_, unsigned int attriNum_);
		virtual ~KeyIndex();
		virtual void init(DbEnv *env_);
		virtual int getRow(PosVal **pv_, unsigned int pvNum_);
		virtual unsigned int getAttriNum(void);
		virtual void getAttriRec(ATTRIBUTE_REC **attriRec_, unsigned int attriNum_);
		
	private:
		void setPosVal(PosVal **pv_, unsigned int pvNum_);
		
		BDBOpe *db;
		//int initFlag;
		//int getFlag;	
		Dbt key, data;
};

#endif
