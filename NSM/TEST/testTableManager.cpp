#include<iostream>
#include<string>

#include "TableManager.h"

using namespace std;

int main()
{
	TableManager *TM;
	TABLE_REC tbl_rec;

	cout << "TM create" << endl;
	TM = new TableManager;

	cout << "Next NO = " << TM->getNextID() << endl;
	cout << "Next NO = " << TM->getNextID() << endl;

	strcpy(tbl_rec.tableName, "fghijk");
	tbl_rec.tableID = TM->getNextID();

	TM->writeRecord(&tbl_rec);
	TM->showAllRecord();

	cout << "TM delete" << endl;
	delete TM;
	return (1);
}
