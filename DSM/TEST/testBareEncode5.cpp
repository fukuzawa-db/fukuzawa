#include<iostream>
#include<fstream>
#include<string>
#include<stdlib.h>

#include"Encode.h"
#include"BareEncode.h"
#include"CommonDataDef.h"
#include"PosVal.h"


#define DATAFILE ("data2.txt")
#define DATATYPE (DATE)
#define DATASIZE (sizeof(unsigned int))

using namespace std;

int main()
{
	Encode *encode;
	encode = new BareEncode(DATAFILE, DATATYPE, DATASIZE);

	unsigned char buffer[32];
	unsigned int bufSize,key;

	memset(buffer, 0 , DSM_BUFFER_SIZE);
	ofstream ofs("output.txt", ios_base::binary | ios_base::out);

	while(encode->getBuffer(buffer, &bufSize, &key) != NULL){
		ofs.write((char *)buffer, bufSize);
		cout << "key = " << key << " Buffer size = " << bufSize << endl;
	}

	delete encode;

	ifstream ifs(DATAFILE);
	unsigned int inData;
	cout.setf(std::ios::hex, std::ios::basefield);
	for(ifs >> inData; !ifs.eof() ; ifs >> inData){
		cout.write((char *)&inData, sizeof(inData));
		cout << endl;
	}
/*
	for(int i=0; i < (int )bufSize; i++){
		ofs << buffer[i];
	}
*/
}
