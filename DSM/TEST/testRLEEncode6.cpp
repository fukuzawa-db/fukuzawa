#include<iostream>
#include<fstream>
#include<string>
#include<stdlib.h>

#include"Encode.h"
#include"RLEEncode.h"
#include"CommonDataDef.h"
#include"PosVal.h"

#define DATAFILE ("rledata3.txt")
#define DATATYPE (FIXED_TEXT)
#define DATASIZE (10)

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

	delete encode;

	ifstream ifs(DATAFILE);
	char f[11];
	while(!ifs.eof()){
		ifs >> f;
		cout.write((char *)&f, 10);
		cout << endl;
	}

}
