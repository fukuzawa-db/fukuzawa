#ifndef __SELECTBITOUT_U_H
#define __SELECTBITOUT_U_H



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

#define BUF_NUM	(1024)

class SelectBitOut_U : public Operator{
	public:
		SelectBitOut_U(Node *root_, unsigned int refNum_);
		~SelectBitOut_U();

		virtual void init(DbEnv *env_);
		virtual int getRow(PosVal **pv_, unsigned int pvNum_);
		virtual unsigned int getAttriNum(void);
		virtual void getAttriRec(ATTRIBUTE_REC **attriRec_, unsigned int attriNum_);
		
		void storeData(void);

	private:
		void setRefNode(Node *node);

		unsigned int index;
		Node *root;
		ColumnRefNode **refNode;
		unsigned int refNum;
		
		int getFlag;
		
		int *buf;
		unsigned int p, current, max;
};



#endif
