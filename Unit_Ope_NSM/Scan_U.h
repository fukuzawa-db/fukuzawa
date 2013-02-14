#ifndef __SCAN_U_H
#define __SCAN_U_H

#include<iostream>
#include<cstdlib>
#include<string>
#include<db_cxx.h>

#include"Operator.h"
#include"BDBOpe.h"
#include"CommonDataDef.h"

#define GET_NSM_DATA	(1000000)

class Scan_U : public Operator{
	public:
		Scan_U(BDBOpe *db_, ATTRIBUTE_REC *attrIRec_, unsigned int attriNum_);
		Scan_U(BDBOpe *db_, ATTRIBUTE_REC *attrIRec_, unsigned int attriNum_, unsigned int num_);
		Scan_U(BDBOpe *db_, ATTRIBUTE_REC *attrIRec_, unsigned int attriNum_, unsigned int num_, unsigned int loop_);
		virtual ~Scan_U();
		virtual void init(DbEnv *env_);
		virtual int getRow(PosVal **pv_, unsigned int pvNum_);
		int getRowKey(PosVal **pv_, unsigned int pvNum_);
		virtual unsigned int getAttriNum(void);
		virtual void getAttriRec(ATTRIBUTE_REC **attriRec_, unsigned int attriNum_);

		void resetGetPos(void);
		void storeData(void);

	private:
		
		void setPosVal(PosVal **pv_, unsigned int pvNum_);


		BDBOpe *db;
		int initFlag;
		int getFlag;	
		Dbt key, data;
		
		unsigned int num;
		unsigned int loop;
		PosVal ***storePosVal;
		int bufferPoint;
		
#ifdef SanTime
		Timer t;
#endif
};

#endif
