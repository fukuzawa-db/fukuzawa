#include<iostream>
#include<fstream>
#include<string>
#include<stdlib.h>

#include"Encode.h"
#include"RLEEncode.h"
#include"CommonDataDef.h"
#include"PosVal.h"


#define DATAFILE ("rledata.txt")
#define DATATYPE (INT)
#define DATASIZE (sizeof(int))

using namespace std;

int main()
{
	Encode *encode;
	encode = new RLEEncode(DATAFILE, DATATYPE, DATASIZE);

	unsigned char buffer[DSM_BUFFER_SIZE];
	unsigned int bufSize,key;

	memset(buffer, 0 , DSM_BUFFER_SIZE);
	ofstream ofs("output.txt", ios_base::binary | ios_base::out);

	while(encode->getBuffer(buffer, &bufSize, &key) != NULL){
		ofs.write((char *)buffer, bufSize);
		cout << "key = " << key << " Buffer size = " << bufSize << endl;
	}
/*
	for(int i=0; i < (int )bufSize; i++){
		ofs << buffer[i];
	}
*/
}
