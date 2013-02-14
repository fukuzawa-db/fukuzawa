#ifndef __SCANDSM_U_H
#define __SCANDSM_U_H

#include<iostream>
#include<cstdlib>
#include<string>
#include<cassert>
#include<db_cxx.h>

#include"CommonDataDef.h"
#include"Operator.h"
#include"BDBOpe.h"
#include"Timer.h"

#define GET_DSM_DATA	(1000000)

class ScanDSM_U : public Operator{
	public:
		ScanDSM_U(BDBOpe *db_, ATTRIBUTE_REC *attriRec_, unsigned int attriNum_);
		ScanDSM_U(BDBOpe *db_, ATTRIBUTE_REC *attriRec_, unsigned int attriNum_, unsigned int num_);
		ScanDSM_U(BDBOpe *db_, ATTRIBUTE_REC *attrIRec_, unsigned int attriNum_, unsigned int num_, unsigned int loop_);
		~ScanDSM_U();

		void init(DbEnv *env_);
		void resetGetPos(void);

		int getRow(PosVal **pv_, unsigned int pvNum_);
		unsigned int getAttriNum(void);
		void getAttriRec(ATTRIBUTE_REC **attriRec_, unsigned int attriNum_);
		
		void storeData(void);


	private:
		int setPosVal(PosVal **pv_, unsigned int pvNum_);
	
		
		BDBOpe *db;
		int readFlag;
		Dbt key,data;
		unsigned int count;

		unsigned int dataItemNum;
		unsigned int readItemNum;
		unsigned int dataPos;
		
		int getFlag;
		unsigned int num;
		unsigned int loop;
		PosVal ***storePosVal;
		int bufferPoint;
		
#ifdef SanDSMTime
		Timer t;
#endif

};

#endif
