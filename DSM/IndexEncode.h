#ifndef __IndexEncode_H
#define __IndexEncode_H

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


class  IndexEncode : public Encode{
	public:
		IndexEncode(string fileName_, DataType dataType_, unsigned short dataLength_);
		~IndexEncode();

		unsigned char *getBuffer(unsigned char *buffer_, unsigned int *bufSize_, unsigned int *key_);

	private:
};

#endif
