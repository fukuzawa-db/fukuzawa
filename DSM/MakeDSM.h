#ifndef __MAKEDSM_H
#define __MAKEDSM_H

#include<iostream>
#include<fstream>
#include<iostream>

#include"CommonDataDef.h"
#include"Encode.h"
#include"BareEncode.h"
#include"RLEEncode.h"
#include"IndexEncode.h"
#include"SortColumn.h"
#include"BDBOpe.h"

//#define DEBUG 1

const int BUFFER_SIZE = 1024;

class MakeDSM{
	public:
		MakeDSM(string fileName_, ATTRIBUTE_REC *attriRec_);
		~MakeDSM();

		void run();
	
	private:
		string fileName;
		ATTRIBUTE_REC  *attriRec;
		Encode *encode;
		string DbName;
		unsigned char buffer[DSM_BUFFER_SIZE];
		unsigned int bufSize;
		unsigned int key;
		BDBOpe *Db;

};

#endif
