#ifndef __NESTEDJOIN_INDEX_H
#define __NESTEDJOIN_INDEX_H

#include<iostream>
#include<cstdio>
#include<string>
#include<cstdlib>
#include<cassert>

#include"CommonDataDef.h"
#include"BDBOpe.h"
#include"Operator.h"
#include"PosVal.h"
#include"IntPosVal.h"
#include"LongPosVal.h"
#include"FloatPosVal.h"
#include"DoublePosVal.h"
#include"FixStrPosVal.h"
#include"VarStrPosVal.h"
#include"DatePosVal.h"
#include"Scan.h"
#include"IndexScan.h"

class NestedJoin_Index : public Operator{
	public:
		NestedJoin_Index(IndexScan *innerOpeNode_, Operator *outerOpeNode_, OPERATION_NODE *op_);
		~NestedJoin_Index();

		virtual void init(DbEnv *env_);

		virtual int getRow(PosVal **pv_, unsigned int pvNum_);
		virtual unsigned int getAttriNum(void);
		virtual void getAttriRec(ATTRIBUTE_REC **attriRec_, unsigned int attriNum_);

	private:
		void setPos(void);

		IndexScan *innerOpeNode;
		Operator *outerOpeNode;
		OPERATION_NODE *op;
		unsigned int innerAttriNum, outerAttriNum;
		unsigned int outerPos;

		/* */
		
		int getRowFlag;

};


#endif

