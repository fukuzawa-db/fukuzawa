#ifndef __AVG_H
#define __AVG_H

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


class Avg : public Aggregation {
	public:
		Avg(Node *root_, unsigned int refNum_);
		Avg(Node *root_, unsigned int refNum_, unsigned int *pos_, unsigned int index_);
		~Avg();
		virtual void init(ATTRIBUTE_REC **attriRec_, unsigned int attriNum_);
		
		virtual Aggregation* clone(void);
		void copyPos(unsigned int *pos_, unsigned int index_);
		
		virtual void inputData(PosVal **pv_, unsigned int pvNum_);
		void setRefNode(Node *node);
		void setAttriName(string attriName_);
		ATTRIBUTE_REC getAttriRec(void);
		virtual PosVal *getValue(void);
		
			
		
	private:
		unsigned int *pos;
		PosVal *tmpPV;
		double tmpVal;
		long count;
		double avg;
		int flag;
		
	
};

#endif
