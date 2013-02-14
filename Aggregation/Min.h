#ifndef __MIN_H
#define __MIN_H

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


class Min : public Aggregation {
	public:
		Min(Node *root_, unsigned int refNum_, DataType type_);
		Min(Node *root_, unsigned int refNum_, DataType type_, unsigned int *pos_, unsigned int index_);
		~Min();
		virtual void init(ATTRIBUTE_REC **attriRec_, unsigned int attriNum_);
		void copyPos(unsigned int *pos_, unsigned int index_);
		
		virtual Aggregation* clone(void);
		virtual void inputData(PosVal **pv_, unsigned int pvNum_);
		void setRefNode(Node *node);
		void setAttriName(string attriName_);
		ATTRIBUTE_REC getAttriRec(void);
		
	private:
		unsigned int *pos;
		PosVal *tmpPV;
};

#endif
