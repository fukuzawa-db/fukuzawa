#ifndef __JOINC_H
#define __JOINC_H

#include<iostream>
#include<string>
#include<cstdlib>
#include<cassert>
#include<vector>

#include"CommonDataDef.h"
#include"Hash.h"
#include"JoinIndexDef.h"
#include"BDBOpe.h"
#include"Operator.h"
#include"Scan.h"
#include"PosVal.h"
#include"IntPosVal.h"
#include"LongPosVal.h"
#include"FloatPosVal.h"
#include"DoublePosVal.h"
#include"FixStrPosVal.h"
#include"VarStrPosVal.h"
#include"DatePosVal.h"
#include"JoinIndex_OneHash.h"
#include"ScanJoinIndex.h"




class JoinC : public Operator{
	public:
		JoinC(Operator *innerOpeNode_, OPERATION_NODE *on_, vector <Operator *> outerOpeNode_);
		~JoinC();

		virtual void init(DbEnv *env_);
		virtual int getRow(PosVal **pv_, unsigned int pvNum_);
		virtual unsigned int getAttriNum(void);
		virtual void getAttriRec(ATTRIBUTE_REC **attriRec_, unsigned int attriNum_);

	private:;
		void setJoinPos(void);


		/*object*/
	
		Operator *innerOpeNode, **outerOpeNode;
		unsigned int innerAttriNum, outerAttriNum;
		OPERATION_NODE *on;
		int opNum;

		int innerPos;
		
		unsigned int currentPos, targetPos;
		int getFlag;
};


#endif
