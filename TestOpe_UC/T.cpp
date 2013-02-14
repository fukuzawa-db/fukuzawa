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
#include"OutPut.h"
#include"ScanDSM.h"
#include"Scan.h"
#include"SelectBitOut.h"
#include"BitFilter.h"
/*
#include"ScanJoinIndex.h"
#include"JoinIndex_OneHash.h"
#include"JoinFromJoinIndex.h"
*/

int main(){
	chdir("../RunData");
	BDBOpe db_l_1("15.1.DSM");
	BDBOpe db_l_2("15.2.DSM");
	BDBOpe db_l("LINEITEM20.row");
	BDBOpe db_l2("LINEITEM20.row");
	BDBOpe db_l3("LINEITEM20.row");
	Operator *o1, *o2, *o3, *o4, *o5, *o6, *o7;
	db_l_1.open();
	db_l_2.open();
	db_l.open();
	db_l2.open();
	db_l3.open();

	TABLE_REC tableRec_r;
	TABLE_REC tableRec_n;
	TABLE_REC tableRec_l;

	tableRec_r.tableID = 1;
	tableRec_r.attriNum = 3;

	tableRec_n.tableID = 2;
	tableRec_n.attriNum = 4; 
	
	tableRec_l.tableID = 8;
	tableRec_l.attriNum = 16;
	
	ATTRIBUTE_REC attriRec_r[tableRec_r.attriNum];
	ATTRIBUTE_REC attriRec_n[tableRec_n.attriNum];
	ATTRIBUTE_REC attriRec_l[tableRec_l.attriNum];

	AttributeManager AM_r;
	AttributeManager AM_n;
	AttributeManager AM_l;
	
	AM_r.getForTableID(tableRec_r, attriRec_r);
	for(int i=0 ; i < (int)tableRec_r.attriNum ; i++){
		cout << attriRec_r[i].attributeName << endl;
	}
	AM_n.getForTableID(tableRec_n, attriRec_n);
	for(int i=0 ; i < (int)tableRec_n.attriNum ; i++){
		cout << attriRec_n[i].attributeName << endl;
	}
	AM_l.getForTableID(tableRec_l, attriRec_l);
	for(int i=0 ; i < (int)tableRec_l.attriNum ; i++){
		cout << attriRec_l[i].attributeName << endl;
	}


/* selection1 */
	FixStrPosVal pv1(1,25);
	string str1("AMERICA");
	pv1.setStr(str1);

	ValueNode vn1 = ValueNode(&pv1);
	ColumnRefNode cn1;
	cn1.tableID = 1;
	cn1.attriID = 2;
	AxprNode an1 = AxprNode(EQ, &cn1, &vn1);
	

	
/*Join */
	OPERATION_NODE op1, op2;
	op1.tableID = 1;
	op1.attributeID = 2;
	op2.tableID = 2;
	op2.attributeID = 2;
	
	JOIN_OPERATION_NODE jon;
	jon.rightNode = op1;
	jon.leftNode = op2;
	
	sleep(10);
	
	o1 = new Scan(&db_l, attriRec_l, 16);
	cout << "OK new o1" << endl;

	o6 = new OutPut(STD_OUT);
	cout << "OK new o6" << endl;
	o6->setPreOperator(o1);
	o6->init();
	cout << "TEST START" << endl;
	o6->exec();

}
	
