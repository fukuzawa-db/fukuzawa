#include<iostream>
#include<string>

#include "AttributeManager.h"

using namespace std;

int main()
{
	AttributeManager *AM;
	ATTRIBUTE_REC attri_rec;

	cout << "AM create" << endl;
	AM = new AttributeManager;


	strcpy(attri_rec.attributeName, "abcdefg");
	attri_rec.tableID = 10;
	attri_rec.attributeID = 1;
	attri_rec.dataType = INT;
	attri_rec.dataLength = sizeof(int);
	attri_rec.primary = true;

	AM->writeRecord(&attri_rec);
	AM->showAllRecord();

	cout << "AM delete" << endl;
	delete AM;
	return (1);
}
