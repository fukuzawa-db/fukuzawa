#ifndef __BITMANAGER_H
#define __BITMANAGER_H

#include<iostream>
#include<cstdlib>
#include<string>
#include<cassert>

using namespace std;

class BitManager{
	public:
		BitManager(unsigned int maxBitNum_);
		~BitManager();

		bool writeBits(unsigned int value_, unsigned int numBit_);
		bool skipBit(unsigned int nnumBit_);
		int getWriteNum();
		unsigned char *getBuffer(void);
		bool clearBuffer();
		bool resetBuffer();

	private:
		unsigned int bufferSize;
		unsigned char *buffer;

		unsigned int *currentInt;
		unsigned int bitPosition;
		unsigned int maxBitNum;
		unsigned int writeNum;
};

#endif
