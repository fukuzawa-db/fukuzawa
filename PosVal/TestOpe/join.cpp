#include<iostream>
#include<cstdlib>
#include<cassert>
#include<string>

#include"CommonDataDef.h"
#include"PosVal.h"
#include"AttributeManager.h"
#include"BDBOpe.h"
#include"Operator.h"
#include"Scan.h"
#include"Selection.h"
#include"Projection.h"
#include"HashJoin.h"
#include"OutPut.h"
#include"Node.h"
#include"AxprNode.h"
#include"ValueNode.h"
#include"ColumnRefNode.h"
#include"IntPosVal.h"
#include"LongPosVal.h"
#include"FloatPosVal.h"
#include"DoublePosVal.h"
#include"FixStrPosVal.h"
#include"VarStrPosVal.h"
#include"DatePosVal.h"


int main(){
	chdir("../RunData");
	BDBOpe db_r("CUSTOMER.row");
	BDBOpe db_n1("ORDERS.row");
	Operator *o1, *o2, *o3, *o4;
	
	db_r.open();
	db_n1.open();

	TABLE_REC tableRec_r, tableRec_n1;
	
/* set table info */
	tableRec_r.tableID = 6;
	tableRec_r.attriNum = 8;
	
	tableRec_n1.tableID = 7;
	tableRec_n1.attriNum = 9;


/* aet attriRec */
	ATTRIBUTE_REC attriRec_r[tableRec_r.attriNum];
	ATTRIBUTE_REC attriRec_n1[tableRec_n1.attriNum];

	AttributeManager AM_r;
	AttributeManager AM_n1;
	

	AM_r.getForTableID(tableRec_r, attriRec_r);
	for(int i=0 ; i < (int)tableRec_r.attriNum ; i++){
		cout << attriRec_r[i].attributeName << endl;
	}
	AM_n1.getForTableID(tableRec_n1, attriRec_n1);
	for(int i=0 ; i < (int)tableRec_n1.attriNum ; i++){
		cout << attriRec_n1[i].attributeName << endl;
	}
	
	
	

	OPERATION_NODE pn1[2];
	pn1[0].tableID = 6;
	pn1[0].attributeID = 1;
	pn1[1].tableID = 7;
	pn1[1].attributeID = 2;

	JOIN_OPERATION_NODE jpn1[1];
	jpn1[0].rightNode = pn1[0];
	jpn1[0].leftNode = pn1[1];



	o1 = new Scan(&db_r, attriRec_r, 8);
	cout << "OK new o1" << endl;
	o2 = new Scan(&db_n1, attriRec_n1, 9);
	cout << "OK new o2" << endl;
	o3 = new HashJoin(o1, o2 , jpn1, 1);
	cout << "OK new o3" << endl;
	o4 = new OutPut(STD_OUT);
	cout << "OK new o4" << endl;

	o4->setPreOperator(o3);
	o4->init();
	cout << "TEST START" << endl;
	o4->exec();
}
	
