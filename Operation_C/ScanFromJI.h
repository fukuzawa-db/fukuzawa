#ifndef __SCANFROMJI_H
#define __SCANFROMJI_H

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

class ScanFromJI : public Operator{
	public:
		ScanFromJI(Operator *innerOpe_, Operator *outerOpe_, OPERATION_NODE *opNode_);
		~ScanFromJI();
		
		virtual void init(DbEnv *env_);
		virtual int getRow(PosVal **pv_, unsigned int pvNum_);
		virtual unsigned int getAttriNum(void);
		virtual void getAttriRec(ATTRIBUTE_REC **attriRec_, unsigned int attriNum_);
	
	private:
		void setPos(void);
		
	
		Operator *innerOpe, *outerOpe;
		OPERATION_NODE *opNode;
		unsigned int innerAttriNum, outerAttriNum;
		unsigned int nodeNum;
		
		int pos, getPos;
		int getRowFlag;
};

#endif
