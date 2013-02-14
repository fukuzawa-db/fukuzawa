#ifndef __AGGREGATION_H
#define __AGGREGATION_H

#include<iostream>
#include<cstdlib>
#include<string>
#include<cassert>

#include"CommonDataDef.h"
#include"PosVal.h"
#include"IntPosVal.h"
#include"LongPosVal.h"
#include"FloatPosVal.h"
#include"DoublePosVal.h"
#include"FixStrPosVal.h"
#include"VarStrPosVal.h"
#include"DatePosVal.h"

#include"Node.h"
#include"ArithmeticNode.h"
#include"ColumnRefNode.h"
#include"ValueNode.h"



class Aggregation{
	public:
		Aggregation();
		virtual ~Aggregation();
		virtual void init(ATTRIBUTE_REC **attriRec_, unsigned int attriNum_) = 0;
		
		virtual Aggregation* clone(void)=0;
		virtual void inputData(PosVal **pv_, unsigned int pvNum_) = 0;
		PosVal *outPut(void);
		ATTRIBUTE_REC getAttriRec(void);
		virtual PosVal *getValue(void);
		
		
	protected:
		Node *root;
		ColumnRefNode **refNode;
		unsigned int index;
		unsigned int refNum;
		ATTRIBUTE_REC attriRec;
		PosVal *pv;
		
};

#endif
