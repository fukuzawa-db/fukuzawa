#ifndef __SCANFROMJI_COM_H
#define __SCANFROMJI_COM_H

#include<iostream>
#include<cassert>
#include<string>

#include"CommonDataDef.h"
#include"PosVal.h"
#include"IntPosVal.h"
#include"LongPosVal.h"
#include"FloatPosVal.h"
#include"DoublePosVal.h"
#include"FixStrPosVal.h"
#include"VarStrPosVal.h"
#include"DatePosVal.h"
#include"Operator.h"

#include"JoinIndexDef.h"
#include"ScanJoinIndex.h"
#include"JoinIndex_OneHash.h"

class ScanFromJI_Com : public Operator{
	public:
		ScanFromJI_Com(Operator *preOperator_, JOIN_INDEX *joinIndex_);
		~ScanFromJI_Com();
		
		virtual void init(DbEnv *env_);
		virtual int getRow(PosVal **pv_, unsigned int pvNum_);
		virtual unsigned int getAttriNum(void);
		virtual void getAttriRec(ATTRIBUTE_REC **attriRec_, unsigned int attriNum_);
	
	private:
		JOIN_INDEX *joinIndex;
		unsigned int getPos;
		int getFlag;
};

#endif
