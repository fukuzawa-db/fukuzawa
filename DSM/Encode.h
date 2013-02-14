#ifndef __ENCODE_H
#define __ENCODE_H

#include<iostream>
#include<fstream>
#include<cstdlib>
#include<string>
#include<cassert>

#include"CommonDataDef.h"
#include"PosVal.h"
#include"IntPosVal.h"
#include"LongPosVal.h"
#include"FloatPosVal.h"
#include"DoublePosVal.h"
#include"FixStrPosVal.h"
#include"VarStrPosVal.h"
#include"DatePosVal.h"
#include"RLEElement.h"


class Encode{
	public:
		Encode() : startOffset(sizeof(unsigned int) * 2){}
		virtual ~Encode(){};

		virtual unsigned char *getBuffer(unsigned char *buffer_, unsigned int *bufSize_, unsigned int *key_) = 0;

	protected:	
		void initVal(void);
		void getVal(void);
		void freeVal(void);

		string fileName;
		DataType dataType;
		PosVal *pv,*fetchPV;
		unsigned short dataLength;
		ifstream ifs;
		void *val;
		unsigned int pos;

		unsigned int *itemNum;
		unsigned int *startPos;
		const unsigned int startOffset;
};

#endif
	
