#ifndef __SORT_H
#define __SORT_H

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

#define MAX_MARGE_BLOCK	(4)

typedef struct SORT_POS_STRUCT{
	unsigned int pos;
	unsigned int option;
} SORT_POS;


typedef struct DB_LIST_NODE_STRUCT{
	BDBOpe *db;
	struct DB_LIST_NODE_STRUCT *next;
} DB_LIST_NODE;

typedef struct RECORD_LIST_NODE_STRUCT{
	struct RECORD_LIST_NODE_STRUCT *next;
	PosVal **pv;
} RECORD_LIST_NODE;

class Sort : public Operator{
	public:
		Sort(OPERATION_NODE *sortNode_, unsigned int sortNum_);
		~Sort();

		virtual void init(DbEnv *env_);
		virtual int getRow(PosVal **pv_, unsigned int pvNum_);
		virtual unsigned int getAttriNum(void);
		virtual void getAttriRec(ATTRIBUTE_REC **attriRec_, unsigned int attruNum_);

	private:
		void setSortPosition(void);
		void initSort(void);
		void qsortList(RECORD_LIST_NODE *array_[], int left_, int right_);
		void swap(RECORD_LIST_NODE *array_[], int i, int j);

		RECORD_LIST_NODE *getList(void);
		unsigned int getPosValSize(PosVal **pv_);
		unsigned int getDataBufSize();
		unsigned int getDataBuffer(char *dataBuffer_,unsigned int dataBufSize_, RECORD_LIST_NODE *node);

		void deleteRecList(RECORD_LIST_NODE *node);
		
		unsigned int readIndex;
		Scan *readDb;
		
		OPERATION_NODE *sortNode;
		unsigned int sortNum;

		SORT_POS *sortPosition;
		bool sortEqualFlag;

		unsigned int margeFileNum;
		bool inMemFlag;
		bool margeEndFlag;
		DB_LIST_NODE *rootDbNode, *newDbNode, *tailDbNode, *pivotDbNode, *preDbNode, *tmpDbNode;
		RECORD_LIST_NODE **sortArray;


		unsigned int listNodeNum;
		RECORD_LIST_NODE *rootNode, *currentNode, *preNode;
		unsigned int work_space;

		char tmpFileName[L_tmpnam + 1];
		string fileName;


		bool initSortFlag;
};

#endif

