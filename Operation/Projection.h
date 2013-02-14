#ifndef __PRIJECTION_H
#define __PROJECTION_H



#include<iostream>
#include<cassert>
#include<string>

#include"CommonDataDef.h"
#include"PosVal.h"
#include"IntPosVal.h"
#include"LongPosVal.h"
#include"FloatPosVal.h"
#include"DoublePosVal.h"
#include"FixStrPosVal.h"
#include"VarStrPosVal.h"
#include"DatePosVal.h"
#include"Operator.h"


class Projection : public Operator{
	public:
		Projection(OPERATION_NODE *projectionNode_, unsigned int projNum_);
		~Projection();

		virtual void init(DbEnv *env_);
		virtual int getRow(PosVal **pv_, unsigned int pvNum_);
		virtual unsigned int getAttriNum(void);
		virtual void getAttriRec(ATTRIBUTE_REC **atriRec_, unsigned int attriNum_);

	private:
		OPERATION_NODE *projectionNode;
		unsigned int projNum;
};

#endif
