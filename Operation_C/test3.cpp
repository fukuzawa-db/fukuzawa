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
#include"ScanJoinIndex.h"
#include"JoinIndex_OneHash.h"
#include"JoinFromJoinIndex.h"


int main(){
	chdir("../RunData");
	BDBOpe db1("1.1.DSM");
	BDBOpe db2("1.2.DSM");
	BDBOpe db3("2.2.DSM");
	BDBOpe db4("2.3.DSM");
	Operator *o1, *o2, *o3, *o4, *o5, *o6, *o7;
	db1.open();
	db2.open();
	db3.open();
	db4.open();
	
	
	TABLE_REC tableRec_r;
	TABLE_REC tableRec_n;

	tableRec_r.tableID = 1;
	tableRec_r.attriNum = 3;

	tableRec_n.tableID = 2;
	tableRec_n.attriNum = 4; 
	
	ATTRIBUTE_REC attriRec_r[tableRec_r.attriNum];
	ATTRIBUTE_REC attriRec_n[tableRec_n.attriNum];

	AttributeManager AM_r;
	AttributeManager AM_n;
	
	AM_r.getForTableID(tableRec_r, attriRec_r);
	for(int i=0 ; i < (int)tableRec_r.attriNum ; i++){
		cout << attriRec_r[i].attributeName << endl;
	}
	AM_n.getForTableID(tableRec_n, attriRec_n);
	for(int i=0 ; i < (int)tableRec_n.attriNum ; i++){
		cout << attriRec_n[i].attributeName << endl;
	}
	
/*Join */
	OPERATION_NODE op1, op2;
	op1.tableID = 1;
	op1.attributeID = 2;
	op2.tableID = 2;
	op2.attributeID = 2;
	
	JOIN_OPERATION_NODE jon;
	jon.rightNode = op1;
	jon.leftNode = op2;
	
	


	o1 = new ScanDSM(&db1, attriRec_r, 1);
	cout << "OK new o1" << endl;
	
	o2 = new ScanDSM(&db4, attriRec_n + 2, 1);
	cout << "OK new o2" << endl;
	
	JoinIndex_OneHash *JI = new JoinIndex_OneHash(o1, o2); 
	JI->init();
	
	
	o3 = new ScanDSM(&db2, attriRec_r + 1, 1);
	cout << "OK new o3" << endl;
	o4 = new ScanDSM(&db3, attriRec_n + 1, 1);
	cout << "OK new o4" << endl;
	/*
	JOIN_INDEX *J = JI->createJoinIndex();

	J->ScanNode->setkey(1);
	cout << J->ScanNode->getRow(NULL, 0) << endl;
	*/


	
	o5 = new JoinFromJoinIndex(o3, o4, JI->createJoinIndex(), &jon);
	cout << "OK new o5" << endl;
	
	o6 = new OutPut(STD_OUT);
	cout << "OK new o6" << endl;
	o6->setPreOperator(o5);
	o6->init();
	cout << "TEST START" << endl;
	o6->exec();
	
	/*
	o7 = new OutPut(STD_OUT);
	cout << "OK new o7" << endl;
	o7->setPreOperator(o2);
	o7->init();
	cout << "TEST START" << endl;
	o7->exec();
	*/
}
	
