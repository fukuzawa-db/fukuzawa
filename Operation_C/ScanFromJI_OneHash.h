#ifndef __ScanFromJI_OneHash_H
#define __ScanFromJI_OneHash_H

#include<iostream>
#include<string>
#include<cstdlib>
#include<cassert>
#include<db_cxx.h>

#include"CommonDataDef.h"
#include"BDBOpe.h"
#include"JoinIndexDef.h"
#include"Hash.h"
#include"Operator.h"
#include"PosVal.h"
#include"IntPosVal.h"
#include"LongPosVal.h"
#include"FloatPosVal.h"
#include"DoublePosVal.h"
#include"FixStrPosVal.h"
#include"VarStrPosVal.h"
#include"DatePosVal.h"
#include"ScanJoinIndex.h"




class ScanFromJI_OneHash : public Operator{
	public:
		ScanFromJI_OneHash(Operator *innerOpeNode_, Operator *outerOpeNode_);
		ScanFromJI_OneHash(Operator *innerOpeNode_, Operator *outerOpeNode_, JOIN_OPERATION_NODE *joinOpeNode_);
		~ScanFromJI_OneHash();

		virtual void init(DbEnv *env_);
		virtual int getRow(PosVal **pv_, unsigned int pvNum_);
		virtual unsigned int getAttriNum(void);
		virtual void getAttriRec(ATTRIBUTE_REC **attriRec_, unsigned int attriNum_);

	private:
		void delHash();

		void initHash(void);
		void setJoinPos(void);

		void storeInnerNode(void);
		int getInnerDataBuffSize(void);
		unsigned int getDataBuffer(char *dataBuffer_, unsigned int dataBufSize_, unsigned int startPos_, unsigned int getNum_);


		/*object*/
	
		Operator *innerOpeNode, *outerOpeNode;
		JOIN_OPERATION_NODE *joinOpeNode;
		unsigned int innerAttriNum, outerAttriNum;
		unsigned int nodeNum;


		ONESIDE_HASH_NODE *innerHash;
		JOIN_INDEX	*joinIndex;
		
		unsigned int *innerPos, *outerPos;
		int getRowFlag;
		
		char tmpFileName[L_tmpnam + 1];
		string filename;
};


#endif
