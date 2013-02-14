#ifndef __SCANJOININDEX_H
#define __SCANJOININDEX_H

#include<iostream>
#include<cstdlib>
#include<string>
#include<db_cxx.h>

#include"Operator.h"
#include"BDBOpe.h"
#include"CommonDataDef.h"


class ScanJoinIndex : public Operator{
	public:
		ScanJoinIndex(BDBOpe *db_, ATTRIBUTE_REC *attrIRec_, unsigned int attriNum_);
		ScanJoinIndex(BDBOpe *db_, ATTRIBUTE_REC **attrIRec_, unsigned int attriNum_);
		virtual ~ScanJoinIndex();
		virtual void init(DbEnv *env_);
		virtual int getRow(PosVal **pv_, unsigned int pvNum_);
		int getKey(void);
		int getData(unsigned int *key_, unsigned int *data_);
		virtual unsigned int getAttriNum(void);
		virtual void getAttriRec(ATTRIBUTE_REC **attriRec_, unsigned int attriNum_);

		void resetGetPos(void);
		void setkey(unsigned int key_);
	
	private:
		//void setPosVal(PosVal **pv_, unsigned int pvNum_);

		BDBOpe *db;
		int initFlag;
		int initKeyFlag;
		unsigned int preKey;
		
		Dbt key, data;
};

#endif
