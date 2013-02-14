#include<iostream>
#include<fstream>
#include<string>
#include<stdlib.h>

#include"Encode.h"
#include"RLEEncode.h"
#include"MakeDSM.h"
#include"CommonDataDef.h"
#include"PosVal.h"


#define DATAFILE ("a")
#define ATTRINAME ("a1")
#define DATATYPE (INT)
#define DATASIZE (sizeof(int))

using namespace std;

int main()
{
	ATTRIBUTE_REC ar;

	strcpy(ar.attributeName, ATTRINAME);
	ar.tableID = 1;
	ar.attributeID = 1;
	ar.dataType = DATATYPE;
	ar.dataLength = DATASIZE;
	ar.primary = false;
	ar.isCompress = true;
	ar.isSort = false;
	MakeDSM md = MakeDSM(DATAFILE, &ar);
	md.run();
}
