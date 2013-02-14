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
#include"OneSideHashJoin.h"
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
	BDBOpe db_r("REGION.row");
	BDBOpe db_n1("NATION.row");
	BDBOpe db_c("CUSTOMER.row");
	BDBOpe db_o("ORDERS.row");
	Operator *o1, *o2, *o3, *o4, *o5, *o6, *o7, *o8, *o9;
	
	db_r.open();
	db_n1.open();
	db_c.open();
	db_o.open();

	TABLE_REC tableRec_r;
	TABLE_REC tableRec_n1;
	TABLE_REC tableRec_c;
	TABLE_REC tableRec_o;
	
/* set table info */
	tableRec_r.tableID = 1;
	tableRec_r.attriNum = 3;
	
	tableRec_n1.tableID = 2;
	tableRec_n1.attriNum = 4;
	
	tableRec_c.tableID = 6;
	tableRec_c.attriNum = 8;

	tableRec_o.tableID = 7;
	tableRec_o.attriNum = 9;

/* aet attriRec */
	ATTRIBUTE_REC attriRec_r[tableRec_r.attriNum];
	ATTRIBUTE_REC attriRec_n1[tableRec_n1.attriNum];
	ATTRIBUTE_REC attriRec_c[tableRec_c.attriNum];
	ATTRIBUTE_REC attriRec_o[tableRec_o.attriNum];

	AttributeManager AM_r;
	AttributeManager AM_n1;
	AttributeManager AM_c;
	AttributeManager AM_o;
	

	AM_r.getForTableID(tableRec_r, attriRec_r);
	for(int i=0 ; i < (int)tableRec_r.attriNum ; i++){
		cout << attriRec_r[i].attributeName << endl;
	}
	AM_n1.getForTableID(tableRec_n1, attriRec_n1);
	for(int i=0 ; i < (int)tableRec_n1.attriNum ; i++){
		cout << attriRec_n1[i].attributeName << endl;
	}
	AM_c.getForTableID(tableRec_c, attriRec_c);
	for(int i=0 ; i < (int)tableRec_c.attriNum ; i++){
		cout << attriRec_c[i].attributeName << endl;
	}
	AM_o.getForTableID(tableRec_o, attriRec_o);
	for(int i=0 ; i < (int)tableRec_o.attriNum ; i++){
		cout << attriRec_o[i].attributeName << endl;
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
	

/* selection2 */

	DatePosVal pv2(1,(unsigned char *)"1995-01-01");
	DatePosVal pv3(1,(unsigned char *)"1996-12-31");
	

	ValueNode vn2 = ValueNode(&pv2);
	ValueNode vn3 = ValueNode(&pv3);
	ColumnRefNode cn2;
	cn2.tableID = 7;
	cn2.attriID = 5;
	AxprNode an2 = AxprNode(GE, &cn2, &vn2);
	AxprNode an3 = AxprNode(LE, &cn2, &vn3);
	AxprNode an4 = AxprNode(AND, &an2, &an3);
	

/* Join */

	OPERATION_NODE pn1[2];
	pn1[0].tableID = 1;
	pn1[0].attributeID = 1;
	pn1[1].tableID = 2;
	pn1[1].attributeID = 3;
	
	OPERATION_NODE pn2[2];
	pn2[0].tableID = 2;
	pn2[0].attributeID = 1;
	pn2[1].tableID = 6;
	pn2[1].attributeID = 4;


	JOIN_OPERATION_NODE jpn1[1];
	jpn1[0].rightNode = pn1[0];
	jpn1[0].leftNode = pn1[1];
	
	JOIN_OPERATION_NODE jpn2[1];
	jpn2[0].rightNode = pn2[0];
	jpn2[0].leftNode = pn2[1];


/*
	o1 = new Scan(&db_r, attriRec_r, 3);
	cout << "OK new o1" << endl;
	o2 = new Selection((Node *)&an1 ,(unsigned int)1);
	cout << "OK new o2" << endl;
	o2->setPreOperator(o1);
	o3 = new Scan(&db_n1, attriRec_n1, 4);
	cout << "OK new o3" << endl;
	o4 = new HashJoin(o2, o3 , jpn1, 1);
	cout << "OK new o4" << endl;
	o5 = new Scan(&db_c, attriRec_c, 8);
	cout << "OK new o5" << endl;
	o6 = new HashJoin(o4, o5 , jpn2, 1);
	cout << "OK new o6" << endl;
*/
	o7 = new Scan(&db_o, attriRec_o, 9);
	cout << "OK new o7" << endl;
	o8 = new Selection((Node *)&an4 ,(unsigned int)2);
	cout << "OK new o8" << endl;
	o8->setPreOperator(o7);

	o9 = new OutPut(STD_OUT);
	cout << "OK new o9" << endl;

	o9->setPreOperator(o8);
	o9->init();
	cout << "TEST START" << endl;
	o9->exec();
}
	
