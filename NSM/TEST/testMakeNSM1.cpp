#include<iostream>
#include<fstream>
#include<cstdlib>

#include"MakeNSM.h"
#include"CommonDataDef.h"

#define file	("data.txt")

int main(){

	string fileName = file;
	TABLE_REC tableRec;
	ATTRIBUTE_REC at1,at2,*atArray[2];

	tableRec.tableID = 13;
	strcpy(tableRec.tableName, "sample.tb");

	strcpy(at1.attributeName, "at1_Name");
	at1.tableID = 13;
	at1.attributeID = 1;
	at1.dataType = INT;
	at1.dataLength = sizeof(int);
	at1.primary = false;

	strcpy(at2.attributeName, "at2_Name");
	at2.tableID = 13;
	at2.attributeID = 2;
	at2.dataType = INT;
	at2.dataLength = sizeof(long);
	at2.primary = false;

	atArray[0] = &at1;
	atArray[1] = &at2;

	MakeNSM nsm = MakeNSM(fileName, &tableRec, atArray, 2);
	nsm.run();
	return 0;
}
