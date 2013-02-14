#include<iostream>
#include<fstream>
#include<cstdlib>

#include"MakeNSM.h"
#include"CommonDataDef.h"

#define file	("data3.txt")

int main(){

	string fileName = file;
	TABLE_REC tableRec;
	ATTRIBUTE_REC at1,at2,*atArray[2];

	tableRec.tableID = 13;
	strcpy(tableRec.tableName, "sample.tb");

	strcpy(at1.attributeName, "at1_Name");
	at1.tableID = 13;
	at1.attributeID = 1;
	at1.dataType = FIXED_TEXT;
	at1.dataLength = 5;
	at1.primary = false;

	strcpy(at2.attributeName, "at2_Name");
	at2.tableID = 13;
	at2.attributeID = 2;
	at2.dataType = VARIABLE_TEXT;
	at2.dataLength = 100;
	at2.primary = false;

	atArray[0] = &at1;
	atArray[1] = &at2;

	MakeNSM nsm = MakeNSM(fileName, &tableRec, atArray, 2);
	nsm.run();
	return 0;
}
