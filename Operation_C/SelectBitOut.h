#ifndef __SELECTBITOUT_H
#define __SELECTBITOUT_H



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

#include"Node.h"
#include"AxprNode.h"
#include"ColumnRefNode.h"
#include"ValueNode.h"


class SelectBitOut : public Operator{
	public:
		SelectBitOut(Node *root_, unsigned int refNum_);
		~SelectBitOut();

		virtual void init(DbEnv *env_);
		virtual int getRow(PosVal **pv_, unsigned int pvNum_);
		virtual unsigned int getAttriNum(void);
		virtual void getAttriRec(ATTRIBUTE_REC **attriRec_, unsigned int attriNum_);

	private:
		void setRefNode(Node *node);

		unsigned int index;
		Node *root;
		ColumnRefNode **refNode;
		unsigned int refNum;
		
		int getFlag;

};



#endif
