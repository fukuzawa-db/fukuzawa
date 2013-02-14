#ifndef __OUTPUT_H
#define __OUTPUT_H

#include<iostream>
#include<cstdlib>
#include<cassert>

#include"Operator.h"
#include"CommonDataDef.h"
#include"BDBOpe.h"
#include"Timer.h"

#include"PosVal.h"
#include"IntPosVal.h"
#include"LongPosVal.h"
#include"FloatPosVal.h"
#include"DoublePosVal.h"
#include"FixStrPosVal.h"
#include"VarStrPosVal.h"
#include"DatePosVal.h"

class OutPut : public Operator{
	public:
		OutPut(OUT_FLAG outFlag_);
		OutPut(OUT_FLAG outFlag_, BDBOpe *outDb_);

		virtual ~OutPut();
		virtual void init(DbEnv *env_);

		void setOutCount(int count_);
		void exec();
		virtual int getRow(PosVal **pv_, unsigned int pvNum_);
		virtual unsigned int getAttriNum(void);
		virtual void getAttriRec(ATTRIBUTE_REC **attriRec_, unsigned int attriNum); 

	private:
		void countOut(void);
		void timeOut(void);
		void allOut(void);


		int count;
		OUT_FLAG outFlag;
		BDBOpe *outDb;
		
		Timer t;
};

#endif
