#ifndef __TABLEMAKER_H
#define __TABLEMAKER_H

#include<iostream>
#include<fstream>
#include<cassert>
#include<cstdlib>
#include<climits>

#include"CommonDataDef.h"
#include"TableManager.h"
#include"AttributeManager.h"

#define MAX_ATTRIBUTE_NUM	(256)

class TableMaker
{
	public:
		TableMaker();
		~TableMaker();
		int run(string FileName_);
	
	private:
		string tName;
		unsigned int tID;
		int numAttribute;
		void **attriDatas;
		string FileName;
		
		TABLE_REC tableRec;
		ATTRIBUTE_REC *attriRecs;

		TableManager TableFile;
		AttributeManager AttriFile;
		
		void setAttriInf(int i_, int typeNum_, char isPrimary_);
		void insertTable(string FileName_);
		unsigned int getKeyBufSize();
		unsigned int getDataBufSize();
		
		unsigned int getKey(char *keyBuffer_, unsigned int keyBufSize_);
		unsigned int getData(char *dataBuffer_, unsigned int dataBufSize_);

		int insertVoidData(int i_, string str_);

};

#endif
