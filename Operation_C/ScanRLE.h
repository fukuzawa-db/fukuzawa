#ifndef __SCANRLE_H
#define __SCANRLE_H

#include<iostream>
#include<cstdlib>
#include<string>
#include<cassert>
#include<db_cxx.h>

#include"Operator.h"
#include"BDBOpe.h"
#include"CommonDataDef.h"
#include"ScanDSM.h"

class ScanRLE : public Operator{
	public:
		ScanRLE(BDBOpe *db_, ATTRIBUTE_REC *attriRec_, unsigned int attriNum_);
		~ScanRLE();

		void init(DbEnv *env_);
		void resetGetPos(void);

		int getRow(PosVal **pv_, unsigned int pvNum_);
		unsigned int getAttriNum(void);
		void getAttriRec(ATTRIBUTE_REC **attriRec_, unsigned int attriNum_);

	private:
		void getRLE(void);

		BDBOpe *db;
		int readFlag;
		Dbt key,data;
		unsigned int count;

		unsigned int dataItemNum, readItemNum, dataPos;
		unsigned int repeat, repeatMax;
		unsigned int startPos;
		
		unsigned int position;
		char buf[256];
		PosVal *pos;
		BDBOpe *joinIndex;
		ATTRIBUTE_REC *posAttri;
		ScanDSM *scanJI;
};

#endif
