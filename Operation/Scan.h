#ifndef __SCAN_H
#define __SCAN_H

#include<iostream>
#include<cstdlib>
#include<string>
#include<db_cxx.h>

#include"Operator.h"
#include"BDBOpe.h"
#include"CommonDataDef.h"

class Scan : public Operator{
	public:
		Scan(BDBOpe *db_, ATTRIBUTE_REC *attrIRec_, unsigned int attriNum_);
		Scan(BDBOpe *db_, ATTRIBUTE_REC **attrIRec_, unsigned int attriNum_);
		virtual ~Scan();
		virtual void init(DbEnv *env_);
		virtual int getRow(PosVal **pv_, unsigned int pvNum_);
		int getRowKey(PosVal **pv_, unsigned int pvNum_);
		virtual unsigned int getAttriNum(void);
		virtual void getAttriRec(ATTRIBUTE_REC **attriRec_, unsigned int attriNum_);

		void resetGetPos(void);
	
	private:
		void setPosVal(PosVal **pv_, unsigned int pvNum_);


		BDBOpe *db;
		int initFlag;
		int getFlag;	
		Dbt key, data;
		
#ifdef SanTime
		Timer t;
#endif
};


typedef struct TMP_NODE_STRUCT{
	string dbName;
	BDBOpe	*db;
	Scan *ScanNode;
} TMP_NODE;
#endif
