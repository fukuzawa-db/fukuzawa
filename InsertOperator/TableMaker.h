/* データ集合から行指向と列指向の各格納データを作成　*/

#ifndef __TABLEMAKER_H
#define __TABLEMAKER_H


#include<iostream>
#include<fstream>
#include<cassert>
#include<cstdlib>
#include<climits>
#include<unistd.h>


#include"CommonDataDef.h"
#include"BDBOpe.h"
#include"SecondDB.h"
#include"IndexExtract.h"
#include"TableManager.h"
#include"AttributeManager.h"
#include"MakeNSM.h"
#include"MakeDSM.h"

#define DEBUG	1

class TableMaker{
	public:
		TableMaker(string filaName_);
		TableMaker(string filaName_, Insert_Option option_);
		~TableMaker();

		int run();

	private:
		void setAttriInf(int i_, int typeNum_, char isPrimary_, char isCompress, char isSort_, char isIndex_);

		string fileName;
		string tableName;
		unsigned int tableID;
		unsigned int numAttribute;
		char isPrimary, isCompress, isSort, isIndex;

		TABLE_REC tableRec;
		ATTRIBUTE_REC *attriRecs;
		
		TableManager *TableFile;
		AttributeManager *AttriFile;
		
		Insert_Option option;
};

#endif
