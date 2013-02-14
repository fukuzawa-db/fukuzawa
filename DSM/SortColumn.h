#ifndef __SORTCOLUMN_H
#define __SORTCOLUMN_H

#include<iostream>
#include<fstream>
#include<string>
#include<stdlib.h>

#include"CommonDataDef.h"
#include"BDBOpe.h"
#include"BareEncode.h"
#include"Encode.h"

class SortColumn{
	public:
		SortColumn(string fileName_, ATTRIBUTE_REC *attriRec_);
		~SortColumn();

		string exec();
	
	private:
		string fileName,sortFileName;
		ATTRIBUTE_REC *attriRec;
		BDBOpe *Db;
		string execStr;
		char buf[256];
		
		unsigned char buffer[DSM_BUFFER_SIZE];
		unsigned int bufSize;
		unsigned int key;
};
#endif

