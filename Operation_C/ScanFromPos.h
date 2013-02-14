#ifndef __SCANFROMPOS_H__
#define __SCANFROMPOS_H__

#include<iostream>
#include<cstdlib>
#include<string>
#include<cassert>
#include<db_cxx.h>

#include"CommonDataDef.h"
#include"Operator.h"
#include"BDBOpe.h"

class ScanFromPos : public Operator
{
	public:
		ScanFromPos(Operator *op_, BDBOpe *db_, ATTRIBUTE_REC *attriRec_, unsigned int attriNum_);
		~ScanFromPos();
		
		void init(DbEnv *env_);
		
		int getRow(PosVal **pv_, unsigned int pvNum_);
		unsigned int getAttriNum(void);
		void getAttriRec(ATTRIBUTE_REC **attriRec_, unsigned int attriNum_);
	
	private:
		void initOutAttriRec(unsigned int attriNum_);
		void setHeader(void);
		void setOffset(void);
		
		BDBOpe *db;
		Dbt key, data;
		unsigned int outAttriNum;
		ATTRIBUTE_REC** outAttriRec;
		
		unsigned int indexPos, start, end, itemNum;
		unsigned int currentPos, currentOffset;
		int getFlag;

};

#endif
		

