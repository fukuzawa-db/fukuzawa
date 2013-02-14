#ifndef __JOINFROMJOININDEX_H
#define __JOINFROMJOININDEX_H

#include<iostream>
#include<string>
#include<cstdlib>
#include<cassert>

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




class JoinFromJoinIndex : public Operator{
	public:
		JoinFromJoinIndex(Operator *innerOpeNode_, Operator *outerOpeNode_, JOIN_INDEX *joinIndex_, JOIN_OPERATION_NODE *jo_);
		~JoinFromJoinIndex();

		virtual void init(DbEnv *env_);
		virtual int getRow(PosVal **pv_, unsigned int pvNum_);
		virtual unsigned int getAttriNum(void);
		virtual void getAttriRec(ATTRIBUTE_REC **attriRec_, unsigned int attriNum_);

	private:;
		void setJoinPos(void);
		
		void initTmp(void);
		void storeInnerNode(void);
		int getInnerDataBuffSize(void);
		unsigned int getDataBuffer(char *dataBuffer_, unsigned int dataBufSize_, unsigned int startPos_, unsigned int getNum_);


		/*object*/
	
		Operator *innerOpeNode, *outerOpeNode;
		unsigned int innerAttriNum, outerAttriNum;
		
		JOIN_INDEX *joinIndex;
		JOIN_OPERATION_NODE *joinOpeNode;

		int innerIndex, outerIndex;
		int innerPos, outerPos;
		
		unsigned int currentPos;
		int getRowFlag;
		
		TMP_NODE *innerTmp;
		char tmpFileName[L_tmpnam + 1];
};


#endif
