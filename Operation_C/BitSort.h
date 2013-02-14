#ifndef __BITSORT_H
#define __BITSORT_H


#include<iostream>
#include<cstdlib>
#include<string>
#include<db_cxx.h>
#include<stdio.h>

#include"Operator.h"
#include"BDBOpe.h"
#include"CommonDataDef.h"
#include"ScanDSM.h"


#define setByte(n)	(((n-1)/(4*8))*4)
#define setBit(n)	((n-1) % (4*8))


class BitSort : public Operator{
	public:
		BitSort();
		~BitSort();

		virtual void init(DbEnv *env_);
		virtual int getRow(PosVal **pv, unsigned int pvNum_);
		virtual unsigned int getAttriNum(void);
		virtual void getAttriRec(ATTRIBUTE_REC **attriRec_, unsigned int attriNum);

	private:
		void setData(void);

		void openJoinIndex(void);
		void openTmpFile(void);
		

		unsigned int tableID, attriID;

		string indexFile;
		BDBOpe *joinIndex;
		ScanDSM *JoinDSM;
		ATTRIBUTE_REC JoinAttriRec;
		PosVal *indexPV;
		FILE *fp;
		int c0, c1, c2, c3;

		unsigned long maxNum, readNum;
		unsigned int readBuf;
		int returnValue;
		bool initFlag;
};

#endif
