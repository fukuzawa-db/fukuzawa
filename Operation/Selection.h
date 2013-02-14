#ifndef __SELECTION_H
#define __SELECTION_H



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


class Selection : public Operator{
	public:
		Selection(Node *root_, unsigned int refNum_);
		~Selection();

		virtual void init(DbEnv *env_);
		virtual int getRow(PosVal **pv_, unsigned int pvNum_);
		virtual unsigned int getAttriNum(void);
		virtual void getAttriRec(ATTRIBUTE_REC **atriRec_, unsigned int attriNum_);

	private:
		void setRefNode(Node *node);

		unsigned int index;
		Node *root;
		ColumnRefNode **refNode;
		unsigned int refNum;

};



#endif
