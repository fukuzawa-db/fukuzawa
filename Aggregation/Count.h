#ifndef __COUNT_H
#define __COUNT_H

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

#include"Aggregation.h"


class Count : public Aggregation {
	public:
		Count(Node *root_, unsigned int refNum_);
		~Count();
		virtual void init(ATTRIBUTE_REC **attriRec_, unsigned int attriNum_);
		
		virtual Aggregation* clone(void);
		virtual void inputData(PosVal **pv_, unsigned int pvNum_);
		void setRefNode(Node *node);
		void setAttriName(string attriName_);
		ATTRIBUTE_REC getAttriRec(void);
		virtual PosVal *getValue(void);
		
	private:
		PosVal *tmpPV;
		long count;
};

#endif
