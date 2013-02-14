#include<iostream>
#include<string>
#include<fstream>

#include"CommonDataDef.h"
#include"SortColumn.h"

using namespace std;
int main(){
	string str = "a";
	ATTRIBUTE_REC attriRec;

	strcpy(attriRec.attributeName,"Attribute1");
	attriRec.tableID = 12;
	attriRec.attributeID = 5;
	attriRec.dataType = INT;
	attriRec.dataLength = sizeof(int);
	attriRec.primary = false;
	attriRec.isCompress = true;
	attriRec.isSort = false;



	cout << "AttriRec DATA:" << endl;
	cout << attriRec.attributeName << " : " << attriRec.tableID << " : " << attriRec.attributeID << endl;

	SortColumn *SC = new SortColumn(str, &attriRec);
	SC->exec();
}
