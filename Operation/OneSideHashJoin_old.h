#ifndef __ONESIDEHASHJOIN_OLD_H
#define __ONESIDEHASHJOIN_OLD_H

#include<iostream>
#include<string>
#include<cstdlib>
#include<cassert>

#include"Hash.h"
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


typedef struct ONESIDE_HASH_NODE_OLD_STRUCT{
	unsigned int num;
	string dbName;
	BDBOpe	*db;
	Scan *ScanNode;
} ONESIDE_HASH_NODE_OLD;


class OneSideHashJoin_old : public Operator{
	public:
		OneSideHashJoin_old(Operator *innerOpeNode_, Operator *outerOpeNode_, JOIN_OPERATION_NODE *joinOpeNode_, unsigned int nodeNum_);
		~OneSideHashJoin_old();

		virtual void init(DbEnv *env_);
		virtual int getRow(PosVal **pv_, unsigned int pvNum_);
		virtual unsigned int getAttriNum(void);
		virtual void getAttriRec(ATTRIBUTE_REC **attriRec_, unsigned int attriNum_);

	private:
		void del(void);
		void deleteNode(ONESIDE_HASH_NODE_OLD *hnp_);
		
		void initHashTable(void);
		ONESIDE_HASH_NODE_OLD *initHashNode(void);
		void setJoinPos(void);

		void storeInnerNode(void);
		ONESIDE_HASH_NODE_OLD *findGetHashTable(unsigned int hashkey_);
		ONESIDE_HASH_NODE_OLD *findSetHashTable(ONESIDE_HASH_NODE_OLD **hashTable_, unsigned int hashkey_, unsigned int *posSet_);
		int getInnerDataBuffSize(void);
		unsigned int getDataBuffer(char *dataBuffer_, unsigned int dataBufSize_, unsigned int startPos_, unsigned int getNum_);


		/*object*/
	
		Operator *innerOpeNode, *outerOpeNode;
		unsigned int innerAttriNum, outerAttriNum;
		JOIN_OPERATION_NODE *joinOpeNode;		
		unsigned int nodeNum;

		ONESIDE_HASH_NODE_OLD *innerHashTable[HASH_SIZE];


		unsigned int *innerPos, *outerPos;

		int getRowFlag;
		char tmpFileName[L_tmpnam + 1];
		string filename;
		Scan *innerScanNode;
};


#endif
