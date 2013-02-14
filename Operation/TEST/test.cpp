#include<iostream>
#include<cstdlib>

#include"CommonDataDef.h"
#include"PosVal.h"
#include"AttributeManager.h"
#include"Operator.h"
#include"Scan.h"
#include"OutPut.h"


int main(){
	chdir("../RunData");
	BDBOpe db("NATION.row");
	Operator *o1, *o2;
	db.open();

	TABLE_REC tableRec;

	tableRec.tableID = 2;
	tableRec.attriNum = 4;

	ATTRIBUTE_REC attriRec[tableRec.attriNum];

	AttributeManager AM;
	AM.getForTableID(tableRec, attriRec);
	for(int i=0 ; i < (int)tableRec.attriNum ; i++){
		cout << attriRec[i].attributeName << endl;
	}

	o1 = new Scan(&db, attriRec, 4);
	cout << "OK new o1" << endl;
	o2 = new OutPut(STD_OUT);
	cout << "OK new o2" << endl;
	o2->setPreOperator(o1);
	o2->init();
	o2->exec();
}
	
