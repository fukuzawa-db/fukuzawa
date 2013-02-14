#ifndef __ONESIDEHASHJOIN_H
#define __ONESIDEHASHJOIN_H

#include<iostream>
#include<string>
#include<cstdlib>
#include<cassert>

#include"CommonDataDef.h"
#include"Hash.h"
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
#include"ScanHash.h"




class OneSideHashJoin : public Operator{
	public:
		OneSideHashJoin(Operator *innerOpeNode_, Operator *outerOpeNode_, JOIN_OPERATION_NODE *joinOpeNode_, unsigned int nodeNum_);
		~OneSideHashJoin();

		virtual void init(DbEnv *env_);
		virtual int getRow(PosVal **pv_, unsigned int pvNum_);
		virtual unsigned int getAttriNum(void);
		virtual void getAttriRec(ATTRIBUTE_REC **attriRec_, unsigned int attriNum_);

	private:
		//void del(void);
		//void deleteNode(ONESIDE_HASH_NODE *hnp_);
		void delHash();
		
		//void initHashTable(void);
		void initHash(void);
		//ONESIDE_HASH_NODE *initHashNode(void);
		void setJoinPos(void);

		void storeInnerNode(void);
		//ONESIDE_HASH_NODE *findGetHashTable(unsigned int hashkey_);
		//ONESIDE_HASH_NODE *findSetHashTable(ONESIDE_HASH_NODE **hashTable_, unsigned int hashkey_, unsigned int *posSet_);
		int getInnerDataBuffSize(void);
		unsigned int getDataBuffer(char *dataBuffer_, unsigned int dataBufSize_, unsigned int startPos_, unsigned int getNum_);


		/*object*/
	
		Operator *innerOpeNode, *outerOpeNode;
		unsigned int innerAttriNum, outerAttriNum;
		JOIN_OPERATION_NODE *joinOpeNode;		
		unsigned int nodeNum;

		ONESIDE_INMEM_HASH_NODE *innerHash;


		unsigned int *innerPos, *outerPos;

		int getRowFlag;
		char tmpFileName[L_tmpnam + 1];
		string filename;
};


#endif
