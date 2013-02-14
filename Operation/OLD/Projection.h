#ifndef __PROJECTION_H
#define __PROJECTION_H


#include<iostream>
#include<fstream>
#include<string>
#include"db_cxx.h"

#include"BDBOpe.h"
#include"CommonDataDef.h"
#include"PosVal.h"
#include"IntPosVal.h"
#include"LongPosVal.h"
#include"FloatPosVal.h"
#include"DoublePosVal.h"
#include"FixStrPosVal.h"
#include"VarStrPosVal.h"
#include"DatePosVal.h"


#define DEBUG	(1)


class Projection{
	public:
		Projection(string fileName_, ATTRIBUTE_REC *attriRec_, unsigned int attriNum_, unsigned int *projectionAttriNum, unsigned int projectionNum_, OUT_FLAG outFlag_);
		Projection(string fileName_, ATTRIBUTE_REC *attriRec_, unsigned int attriNum_, unsigned int *projectionAttriNum, unsigned int projectionNum_, OUT_FLAG outFlag_, BDBOpe *outDb_);
		~Projection();

		void exec(void);
	private:
		void init(void);
		void initPosVal(void);
		void printPosVal(void);
		void printDb(void);

		string fileName;
		ATTRIBUTE_REC *attriRec;
		unsigned int attriNum;
		unsigned int *projectionAttriNum;
		unsigned int projectionNum;
		OUT_FLAG outFlag;

		PosVal **pv;
		unsigned int *attriLen;

		unsigned char *buffer;
		unsigned int bufferSize;
		BDBOpe *Db, *outDb;
		Dbt key,data;
	
		unsigned char *oBuffer;
		unsigned int oBufferSize;

};

#endif
