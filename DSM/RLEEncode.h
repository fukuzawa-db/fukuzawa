#ifndef __RLEENCODE_H
#define __RLEENCODE_H

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
#include"RLEElement.h"
#include"Encode.h"


class  RLEEncode : public Encode{
	public:
		RLEEncode(string fileName_, DataType dataType_, unsigned short dataLength_);
		~RLEEncode();

		unsigned char *getBuffer(unsigned char *buffer_, unsigned int *bufSize_, unsigned int *key_);

	private:
		PosVal *fetchPV;
		RLEElement rleElement;
		unsigned short RLEElementSize;
};

#endif
