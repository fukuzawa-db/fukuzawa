#ifndef __MAKENSM_H
#define __MANENSM_H

#include<iostream>
#include<sstream>
#include<fstream>
#include<string>
#include<cstdlib>
#include<cassert>
#include<db_cxx.h>
#include<vector>

#include"CommonDataDef.h"
#include"BDBOpe.h"
#include"SecondDB.h"
#include"IndexExtract.h"


//#define DEBUG 1

class MakeNSM{
	public:
		MakeNSM(string fileName_,TABLE_REC *tableRec_, ATTRIBUTE_REC *attriREC_, unsigned int attriNum_, Insert_Option option_);
		~MakeNSM();

		void run();

	private:
		void initAttriDatas();
		unsigned int getDataBufSize();
		int insertVoidData(int i_, string str_);
		unsigned int getData(char *dataBuffer_, unsigned int dataBufSize_);
	

		string fileName;
		TABLE_REC *tableRec;
		ATTRIBUTE_REC *attriRec;
		Insert_Option option;
		SecondDB **sDB;
		int secondNum;
		int (**pf)(Db *sdbp, const Dbt*pkey, const Dbt *pdata, Dbt *skey);
		
		vector <int> indexPos;
		unsigned int attriNum;
		void **attriDatas;

		string buffer;
		int returnCode;
		int end_pos;
};

#endif
