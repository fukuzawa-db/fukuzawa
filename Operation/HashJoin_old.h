#ifndef __HASHJOIN_OLD_H
#define __HASHJOIN_OLD_H

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


typedef struct HASH_NODE_OLD_STRUCT{
	unsigned int num;
	string dbName;
	BDBOpe	*db;
} HASH_NODE_OLD;


class HashJoin_old : public Operator{
	public:
		HashJoin_old(Operator *innerOpeNode_, Operator *outerOpeNode_, JOIN_OPERATION_NODE *joinOpeNode_, unsigned int nodeNum_);
		~HashJoin_old();

		virtual void init(DbEnv *env_);
		virtual int getRow(PosVal **pv_, unsigned int pvNum_);
		virtual unsigned int getAttriNum(void);
		virtual void getAttriRec(ATTRIBUTE_REC **attriRec_, unsigned int attriNum_);

	private:
		void del(void);
		void deleteNode(HASH_NODE_OLD *hnp_);
		
		void initHashTable(void);
		HASH_NODE_OLD *initHashNode(void);
		void setJoinPos(void);

		void storeInnerNode(void);
		void storeOuterNode(void);
		HASH_NODE_OLD *findGetHashTable(HASH_NODE_OLD* outerhnp_, unsigned int hashkey_);
		HASH_NODE_OLD *findSetHashTable(HASH_NODE_OLD **hashTable_, unsigned int hashkey_, unsigned int *posSet_);
		int cmpHashNode(HASH_NODE_OLD *hnp_, unsigned int *posSet_);
		int getInnerDataBuffSize(void);
		int getOuterDataBuffSize(void);
		unsigned int getDataBuffer(char *dataBuffer_, unsigned int dataBufSize_, unsigned int startPos_, unsigned int getNum_);


		/*object*/
	
		Operator *innerOpeNode, *outerOpeNode;
		unsigned int innerAttriNum, outerAttriNum;
		JOIN_OPERATION_NODE *joinOpeNode;		
		unsigned int nodeNum;

		HASH_NODE_OLD *outerHashTable[HASH_SIZE];
		HASH_NODE_OLD *innerHashTable[HASH_SIZE];

		HASH_NODE_OLD *innerHnp, *outerHnp;
		unsigned int *innerPos, *outerPos;

		int getRowFlag;
		char tmpFileName[L_tmpnam + 1];
		string filename;
		unsigned int outerHashkey;
		Scan *innerScanNode, *outerScanNode;
};


#endif
