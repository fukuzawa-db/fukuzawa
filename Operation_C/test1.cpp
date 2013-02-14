#include<iostream>
#include<string>
#include<cstdlib>
#include<cassert>
#include<db_cxx.h>
#include <iomanip>

#include"CommonDataDef.h"
#include"PosVal.h"
#include"AttributeManager.h"
#include"Operator.h"
#include"ScanDSM.h"
#include"OutPut.h"


int main(){
	chdir("../RunData");
	BDBOpe db("1.1.DSM");
	Operator *o1, *o2;
	db.open();

	TABLE_REC tableRec;

	tableRec.tableID = 1;
	tableRec.attriNum = 3; 

	ATTRIBUTE_REC attriRec[tableRec.attriNum];

	AttributeManager AM;
	AM.getForTableID(tableRec, attriRec);
	for(int i=0 ; i < (int)tableRec.attriNum ; i++){
		cout << attriRec[i].attributeName << endl;
	}

	o1 = new ScanDSM(&db, attriRec, 1);
	cout << "OK new o1" << endl;
	o2 = new OutPut(STD_OUT);
	cout << "OK new o2" << endl;
	o2->setPreOperator(o1);
	o2->init();
	cout << "EXEC" << endl;
	cout << setprecision(3);
	cout << setiosflags(ios::fixed); 
	o2->exec();
}
	
