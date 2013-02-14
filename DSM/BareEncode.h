#ifndef __BAREENCODE_H
#define __BAREENCODE_H

#include<iostream>
#include<fstream>
#include<cstdlib>

#include"CommonDataDef.h"
#include"PosVal.h"
#include"IntPosVal.h"
#include"LongPosVal.h"
#include"FloatPosVal.h"
#include"DoublePosVal.h"
#include"FixStrPosVal.h"
#include"VarStrPosVal.h"
#include"DatePosVal.h"
#include"Encode.h"


class  BareEncode : public Encode{
	public:
		BareEncode(string fileName_, DataType dataType_, unsigned short dataLength_);
		virtual ~BareEncode();

		unsigned char *getBuffer(unsigned char *buffer_, unsigned int *bufSize_, unsigned int *key_);
};
#endif
