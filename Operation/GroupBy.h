#ifndef __GROUPBY_H
#define __GROUPBY_H


#include<iostream>
#include<cstdio>
#include<string>
#include<cstdlib>
#include<cassert>

#include"CommonDataDef.h"
#include"Operator.h"
#include"PosVal.h"
#include"IntPosVal.h"
#include"LongPosVal.h"
#include"FloatPosVal.h"
#include"DoublePosVal.h"
#include"FixStrPosVal.h"
#include"VarStrPosVal.h"
#include"DatePosVal.h"
#include"Hash.h"

#include"Aggregation.h"
#include"Max.h"
#include"Min.h"
#include"Count.h"
#include"Sum.h"
#include"Avg.h"


typedef struct GROUP_HASH_NODE_STRUCT{
	PosVal **pv;
	Aggregation **aggreSet;
	struct GROUP_HASH_NODE_STRUCT *next;
} GROUP_HASH_NODE;



class GroupBy : public Operator {
	public:
		GroupBy(OPERATION_NODE *groupNode_, unsigned int nodeNum_, Aggregation **aggreSet_, unsigned int aggreNum_);
		~GroupBy(void);
		
		virtual void init(DbEnv *env_);
		virtual int getRow(PosVal **pv_, unsigned int pvNum_);
		virtual unsigned int getAttriNum(void);
		virtual void getAttriRec(ATTRIBUTE_REC **attriRec_, unsigned int attriNum_);
		
	private:
		void setPos(void);
		void initHashTable(void);
		GROUP_HASH_NODE *initHashNode(void);
	
		void storeHashTable(void);
		void setRow(PosVal **pv_, GROUP_HASH_NODE *np);
		GROUP_HASH_NODE *findSetHashTable(unsigned int hashkey_);
		int cmpHashNode(GROUP_HASH_NODE *hnp_);
	
	
	
	
	/*			*/
	
	
		OPERATION_NODE *groupNode;
		unsigned int nodeNum;
		Aggregation **aggreSet;
		unsigned int aggreNum;
		unsigned int setAttriNum;	

		GROUP_HASH_NODE *hashTable[HASH_SIZE];
		unsigned int *position;
	
		unsigned int searchIndex;
		GROUP_HASH_NODE *searchNode;
		int getRowFlag;
		
};



#endif
