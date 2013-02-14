#include"BitManager.h"

BitManager::BitManager(unsigned int maxBitNum_){
	bufferSize = maxBitNum / 8;
	if((maxBitNum_ % (sizeof(unsigned int) * 8)) != 0)bufferSize += sizeof(unsigned int);
	buffer = new unsigned char[bufferSize];
	memset(buffer, 0, bufferSize);

	currentInt = (unsigned int *)buffer;
	bitPosition = 0;
	writeNum = 0;
	maxBitNum = maxBitNum_;
}


BitManager::~BitManager(){
	delete[] buffer;
}

bool BitManager::writeBits(unsigned int value_, unsigned int numBit_){
	if(sizeof(unsigned int) == 4)
		assert(value_ <= (0xFFFFFFFF >> (32 - numBit_)));
	else{
		cout << "Not support unsigned int size = " << sizeof(unsigned int) << endl;
		exit (EXIT_FAILURE);
	}

	if(writeNum + numBit_ > maxBitNum){
		return false;
	}

	unsigned int currentSpace = sizeof(unsigned int) * 8 - bitPosition;
	if(currentSpace == numBit_){
		unsigned int orValue = value_ << (currentSpace - numBit_);
		*currentInt |= orValue;
		bitPosition = 0;
		currentInt++;
	}
	else if(currentSpace > numBit_){
		unsigned int orValue = value_ << (currentSpace - numBit_);
		*currentInt |= orValue;
		bitPosition += numBit_;
	}
	else{
		unsigned int orValue = value_ >> (numBit_ - currentSpace);
		*currentInt |= orValue;
		currentInt++;
		orValue = value_ << (sizeof(unsigned int) - (numBit_ - currentSpace));
		*currentInt |= orValue;
		bitPosition = (numBit_ - currentSpace);
	}
	writeNum += numBit_;
	return true;
}



bool BitManager::skipBit(unsigned int numBit_){
	if(writeNum + numBit_ < maxBitNum){
		currentInt += (numBit_/(sizeof(unsigned int) * 8));
		bitPosition += (numBit_ % (8 * sizeof(unsigned int)));
		currentInt += bitPosition / (8 * sizeof(unsigned int));
		bitPosition += bitPosition % (8 * sizeof(unsigned int));
		writeNum += numBit_;
		return true;
	}
	else{
		return false;
	}
}



int BitManager::getWriteNum(){
	return writeNum;
}



unsigned char* BitManager::getBuffer(){
	return buffer;
}


bool BitManager::clearBuffer(){
	bool success = this->resetBuffer();
	memset(buffer, 0 , bufferSize);
	return  success;
}


bool BitManager::resetBuffer(){
	writeNum = 0;
	currentInt = (unsigned int *)buffer;
	bitPosition = 0;
	return true;
}	
