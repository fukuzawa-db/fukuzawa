#ifndef __AggreOut_H
#define __AggreOut_H


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


class AggreOut : public Operator {
	public:
		AggreOut(Aggregation **aggreSet_, unsigned int aggreNum_);
		~AggreOut(void);
		
		virtual void init(DbEnv *env_);
		virtual int getRow(PosVal **pv_, unsigned int pvNum_);
		virtual unsigned int getAttriNum(void);
		virtual void getAttriRec(ATTRIBUTE_REC **attriRec_, unsigned int attriNum_);
		
	private:
		void initAggreSet(void);
		void setRow(PosVal **pv_);
	
	
	
	
	/*			*/
	
		Aggregation **aggreSet;
		unsigned int aggreNum;
		
		int getRowFlag;
		
};



#endif
