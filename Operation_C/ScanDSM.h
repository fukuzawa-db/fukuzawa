#ifndef __SCANDSM_H
#define __SCANDSM_H

#include<iostream>
#include<cstdlib>
#include<string>
#include<cassert>
#include<db_cxx.h>

#include"CommonDataDef.h"
#include"Operator.h"
#include"BDBOpe.h"

class ScanDSM : public Operator{
	public:
		ScanDSM(BDBOpe *db_, ATTRIBUTE_REC *attriRec_, unsigned int attriNum_);
		~ScanDSM();

		void init(DbEnv *env_);
		void resetGetPos(void);

		int getRow(PosVal **pv_, unsigned int pvNum_);
		unsigned int getAttriNum(void);
		void getAttriRec(ATTRIBUTE_REC **attriRec_, unsigned int attriNum_);

	private:
		BDBOpe *db;
		int readFlag;
		Dbt key,data;
		unsigned int count;

		unsigned int dataItemNum;
		unsigned int readItemNum;
		unsigned int dataPos;
};

#endif
