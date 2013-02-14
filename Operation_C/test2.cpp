#include<iostream>
#include<cstdlib>

#include"CommonDataDef.h"
#include"PosVal.h"
#include"AttributeManager.h"
#include"Operator.h"
#include"ScanDSM.h"
#include"ScanRLE.h"
#include"OutPut.h"


int main(){
	chdir("../RunData");
	BDBOpe db("4.7.DSM");
	Operator *o1, *o2;
	db.open();

	TABLE_REC tableRec;

	tableRec.tableID = 4;
	tableRec.attriNum = 9;

	ATTRIBUTE_REC attriRec[tableRec.attriNum];

	AttributeManager AM;
	AM.getForTableID(tableRec, attriRec);
	for(int i=0 ; i < (int)tableRec.attriNum ; i++){
		cout << attriRec[i].attributeName << endl;
	}

	o1 = new ScanRLE(&db, &attriRec[6], 1);
	cout << "OK new o1" << endl;
	o2 = new OutPut(STD_OUT);
	cout << "OK new o2" << endl;
	o2->setPreOperator(o1);
	o2->init();
	o2->exec();
}
	
