#ifndef __SELECT_H
#define __SELECT_H


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


class Select{
	public:
		Select(string fileName_, ATTRIBUTE_REC *attriRec_, unsigned int attriNum_, PosVal **selectAttri_, unsigned int selectNum_, OUT_FLAG outFlag_);
		Select(string fileName_, ATTRIBUTE_REC *attriRec_, unsigned int attriNum_, PosVal **selectAttri_, unsigned int selectNum_, OUT_FLAG outFlag_, BDBOpe *outDb_);
		~Select();

		void exec(void);

	private:
		void init(void);
		void initPosVal(void);

		string fileName;
		ATTRIBUTE_REC *attriRec;
		unsigned int attriNum;
		PosVal **selectAttri;
		unsigned int selectNum;
		OUT_FLAG outFlag;

		PosVal **pv;
		unsigned int *attriLen;

		unsigned char *buffer;
		unsigned int bufferSize;
		BDBOpe *Db, *outDb;
		Dbt key,data;
	
};

#endif
