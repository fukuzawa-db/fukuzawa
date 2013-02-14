#ifndef __MARGEJOIN_H
#define __MARGEJOIN_H

#include<iostream>
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

typedef struct PV_LIST_STRUCT{
	PosVal** pv;
	struct PV_LIST_STRUCT *next;
} PV_LIST;

class MargeJoin : public Operator{
	public:
		MargeJoin(Operator *innerOpeNode_, Operator *outerOpeNode_, JOIN_OPERATION_NODE *joinOpeNode_, unsigned int nodeNum_);
		~MargeJoin();

		virtual void init(DbEnv *env_);

		virtual int getRow(PosVal **pv_, unsigned int pvNum_);
		virtual unsigned int getAttriNum(void);
		virtual void getAttriRec(ATTRIBUTE_REC **attriRec_, unsigned int attriNum_);

	private:
		void setJoinPos(void);
		void deleteNode(PV_LIST *node_, unsigned int attriNum_);
		Operator *innerOpeNode,*outerOpeNode;
		JOIN_OPERATION_NODE *joinOpeNode;
		unsigned int nodeNum;
		unsigned int innerAttriNum, outerAttriNum;
		unsigned int *innerPos, *outerPos, *options;

		int cmpPV(void);
		int cmpPV(PosVal **innerPV_, PosVal **outerPV_);
		int cmpInnerPV(PosVal **innerPV1_, PosVal **innerPV2_);

		int getRowFlag;

		PV_LIST *rootNode, *newNode, *lastNodePos, *listIndex;
};


#endif

