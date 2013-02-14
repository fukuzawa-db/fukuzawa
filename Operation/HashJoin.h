#ifndef __HASHJOIN_H
#define __HASHJOIN_H

#include<iostream>
#include<string>
#include<cstdlib>
#include<cassert>

#include"Hash.h"
#include"CommonDataDef.h"
#include"BDBOpe.h"
#include"InMemDB.h"
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
#include"ScanHash.h"

typedef struct HASH_NODE_STRUCT{
	//unsigned int num;
	string dbName;
	BDBOpe	*db;
	ScanHash *ScanNode;
} HASH_NODE;

typedef struct HASH_INMEM_NODE_STRUCT{
	//unsigned int num;
	string dbName;
	InMemDB	*db;
	ScanInMemHash *ScanNode;
} HASH_INMEM_NODE;



class HashJoin : public Operator{
	public:
		HashJoin(Operator *innerOpeNode_, Operator *outerOpeNode_, JOIN_OPERATION_NODE *joinOpeNode_, unsigned int nodeNum_);
		~HashJoin();

		virtual void init(DbEnv *env_);
		virtual int getRow(PosVal **pv_, unsigned int pvNum_);
		virtual unsigned int getAttriNum(void);
		virtual void getAttriRec(ATTRIBUTE_REC **attriRec_, unsigned int attriNum_);

	private:
		void delHash(void);
		
		void initHash(void);
		void setJoinPos(void);

		void storeInnerNode(void);
		void storeOuterNode(void);
		int getInnerDataBuffSize(void);
		int getOuterDataBuffSize(void);
		unsigned int getDataBuffer(char *dataBuffer_, unsigned int dataBufSize_, unsigned int startPos_, unsigned int getNum_);


		/*object*/
	
		Operator *innerOpeNode, *outerOpeNode;
		unsigned int innerAttriNum, outerAttriNum;
		JOIN_OPERATION_NODE *joinOpeNode;		
		unsigned int nodeNum;

		HASH_INMEM_NODE *outerHash;
		HASH_INMEM_NODE *innerHash;

		unsigned int *innerPos, *outerPos;

		int getRowFlag;
		char tmpFileName[L_tmpnam + 1];
		string filename;
		unsigned int searchHashkey;
};


#endif
