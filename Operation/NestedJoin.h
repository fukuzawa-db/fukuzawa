#ifndef __NESTEDJOIN_H
#define __NESTEDJOIN_H

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

class NestedJoin : public Operator{
	public:
		NestedJoin(Operator *innerOpeNode_, Operator *outerOpeNode_, JOIN_OPERATION_NODE *joinOpeNode_, unsigned int nodeNum_);
		~NestedJoin();

		virtual void init(DbEnv *env_);

		virtual int getRow(PosVal **pv_, unsigned int pvNum_);
		virtual unsigned int getAttriNum(void);
		virtual void getAttriRec(ATTRIBUTE_REC **attriRec_, unsigned int attriNum_);

	private:
		void setJoinPos(void);
		void storeInnerNode(void);
		int getInnerDataBuffSize(void);
		unsigned int getInnerDataBuffer(char *dataBuffer_, unsigned int dataBufSize_);


		Operator *innerOpeNode,*outerOpeNode;
		JOIN_OPERATION_NODE *joinOpeNode;
		unsigned int nodeNum;
		unsigned int innerAttriNum, outerAttriNum;
		unsigned int *innerPos, *outerPos;

		/* */
		
		int getRowFlag;

		char tmpFileName[L_tmpnam + 1];
		string fileName;
		BDBOpe *db;
		Scan *innerScanNode;

};


#endif

