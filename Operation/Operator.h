#ifndef __OPERATOR_H
#define __OPERATOR_H

#include<iostream>
#include<db_cxx.h>


#include"CommonDataDef.h"
#include"PosVal.h"
#include"IntPosVal.h"
#include"LongPosVal.h"
#include"FloatPosVal.h"
#include"DoublePosVal.h"
#include"FixStrPosVal.h"
#include"VarStrPosVal.h"
#include"DatePosVal.h"


class Operator{
	public:
		Operator();
		virtual ~Operator();
		virtual void init(DbEnv *env_) = 0;

		inline void setPreOperator(Operator *preOpe_){preOperator = preOpe_;}
		virtual int getRow(PosVal **pv_, unsigned int pvNum_) = 0; 
		virtual unsigned int getAttriNum(void) = 0;
		virtual void getAttriRec(ATTRIBUTE_REC **attriRec_, unsigned int attriNum) = 0; 
		void initPosVal(void);
		void initPosVal(PosVal **&pv_);
		void initPosVal(PosVal **&pv_, unsigned int start_, unsigned int end_);
		void initAttriRec(unsigned int attriNum_);

		virtual void exec(void){};
		
	protected:
		Operator *preOperator;
		ATTRIBUTE_REC **attriRec;
		PosVal **pv;
		DbEnv *env;
		unsigned int attriNum;
};



#endif
