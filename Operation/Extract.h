#ifndef __EXTRACT_H
#define __EXTRACT_H



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


class Extract : public Operator{
	public:
		Extract(OPERATION_NODE *extractNode_,  bool yBool_, bool mBool_, bool dBool_);
		~Extract();
		

		virtual void init(DbEnv *env_);
		virtual int getRow(PosVal **pv_, unsigned int pvNum_);
		virtual unsigned int getAttriNum(void);
		virtual void getAttriRec(ATTRIBUTE_REC **atriRec_, unsigned int attriNum_);

	private:
		void setPos(void);
	
	
		OPERATION_NODE *extractNode;
		bool yBool;
		bool mBool;
		bool dBool;
		
		unsigned int datePos;
};

#endif
