#ifndef __ARITHMETICNODE_H
#define __ARITHMETICNODE_H

#include<iostream>
#include<cstdlib>
#include<cassert>

#include"CommonDataDef.h"
#include"Node.h"
#include"PosVal.h"
#include"IntPosVal.h"
#include"LongPosVal.h"
#include"FloatPosVal.h"
#include"DoublePosVal.h"
#include"FixStrPosVal.h"
#include"VarStrPosVal.h"
#include"DatePosVal.h"

class ArithmeticNode : public Node{
	public:
		ArithmeticNode(ARITH_TYPE axpr_);
		ArithmeticNode(ARITH_TYPE axpr_, Node *leftNode_, Node *rightNode_);
		~ArithmeticNode();
		
		void setAxpr(ARITH_TYPE axpr_);
		void setLeftNode(Node *leftNode_);
		void setRightNode(Node *rightNode_);
		void setNode(Node *leftNode_, Node *rightNode_);
		
		ARITH_TYPE getAxpr(void);
		Node *getLeftNode(void);
		Node *getRightNode(void);
		
		void *getValue(void);
		
	private:
		void setLeftValue(Node *node_);
		void setRightValue(Node *node_);
		int typeFlag;
		ARITH_TYPE axpr;
		
		void *leftVal, *rightVal;
		PosVal *pv;

};

#endif
