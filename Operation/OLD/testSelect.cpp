#include<iostream>
#include<string>
#include<cstdlib>
#include<cassert>

#include"CommonDataDef.h"

#include"Select.h"
#include"AttributeManager.h"
#include"PosVal.h"
#include"IntPosVal.h"
#include"LongPosVal.h"
#include"FloatPosVal.h"
#include"DoublePosVal.h"
#include"FixStrPosVal.h"
#include"VarStrPosVal.h"
#include"DatePosVal.h"


int main(int argc, char *argv[]){
	chdir("../RunData");
	TABLE_REC tableRec;

	tableRec.tableID = 2;
	tableRec.attriNum = 4;

	ATTRIBUTE_REC attriRec[tableRec.attriNum];

	AttributeManager AM;
	AM.getForTableID(tableRec, attriRec);
	for(int i=0 ; i < (int)tableRec.attriNum ; i++){
		cout << attriRec[i].attributeName << endl;
	}

	int val = 6;
	PosVal *array[1];
	array[0] = new IntPosVal();
	array[0]->set(1,(unsigned char*)&val);

	cout << "\n\n======================== strat test ==================================\n\n" << endl;

	Select SC = Select(string("NATION.row"), attriRec, (unsigned int)(sizeof(attriRec)/sizeof(attriRec[0])), array, (unsigned int)(sizeof(array)/sizeof(array[0])), STD_OUT);
	SC.exec();

	cout << "\n\n======================== end test ==================================\n\n" << endl;
}

	

