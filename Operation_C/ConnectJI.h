#ifndef __CONNECT_JI_H
#define __CONNECT_JI_H

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




class ConnectJI : public Operator{
	public:
		ConnectJI(JOIN_INDEX *joinIndex1_, JOIN_INDEX *joinIndex2_);
		~ConnectJI();

		virtual void init(DbEnv *env_);
		virtual int getRow(PosVal **pv_, unsigned int pvNum_){return -1;}
		virtual unsigned int getAttriNum(void);
		virtual void getAttriRec(ATTRIBUTE_REC **attriRec_, unsigned int attriNum_);
		JOIN_INDEX *createJoinIndex(void);

	private:
		void initJoinIndex(void);

		/*object*/
	
		JOIN_INDEX *joinIndex1, *joinIndex2;
		JOIN_INDEX	*joinIndex;


		char tmpFileName[L_tmpnam + 1];
		string filename;
};


#endif
