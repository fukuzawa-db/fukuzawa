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
#include"ScanHash.h"
#include"Selection.h"
#include"Projection.h"
#include"HashJoin.h"
#include"HashJoin_old.h"
#include"OneSideHashJoin.h"
#include"OneSideHashJoin_old.h"
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
	BDBOpe db_l("LINEITEM.row");
	BDBOpe db_p("PART.row");
	BDBOpe db_s("SUPPLIER.row");
	BDBOpe db_n2("NATION.row");
	Operator *o1, *o2, *o3, *o4, *o5, *o6, *o7, *o8, *o9, *o10;
	Operator *o11, *o12, *o13, *o14, *o15, *o16, *o17, *o18, *o19, *o20;
	Operator *o21, *o22, *o23, *o24, *o25, *o26;
	
	db_r.open();
	db_n1.open();
	db_c.open();
	db_o.open();
	db_l.open();
	db_p.open();
	db_s.open();
	db_n2.open();

	TABLE_REC tableRec_r;
	TABLE_REC tableRec_n1;
	TABLE_REC tableRec_c;
	TABLE_REC tableRec_o;
	TABLE_REC tableRec_l;
	TABLE_REC tableRec_p;
	TABLE_REC tableRec_s;
	TABLE_REC tableRec_n2;
	
/* set table info */
	tableRec_r.tableID = 1;
	tableRec_r.attriNum = 3;
	
	tableRec_n1.tableID = 2;
	tableRec_n1.attriNum = 4;
	
	tableRec_c.tableID = 6;
	tableRec_c.attriNum = 8;

	tableRec_o.tableID = 7;
	tableRec_o.attriNum = 9;
	
	tableRec_l.tableID = 8;
	tableRec_l.attriNum = 16;

	tableRec_p.tableID = 4;
	tableRec_p.attriNum = 9;
	
	tableRec_s.tableID = 3;
	tableRec_s.attriNum = 7;
	
	tableRec_n2.tableID = 2;
	tableRec_n2.attriNum = 4;

/* aet attriRec */
	ATTRIBUTE_REC attriRec_r[tableRec_r.attriNum];
	ATTRIBUTE_REC attriRec_n1[tableRec_n1.attriNum];
	ATTRIBUTE_REC attriRec_c[tableRec_c.attriNum];
	ATTRIBUTE_REC attriRec_o[tableRec_o.attriNum];
	ATTRIBUTE_REC attriRec_l[tableRec_l.attriNum];
	ATTRIBUTE_REC attriRec_p[tableRec_p.attriNum];
	ATTRIBUTE_REC attriRec_s[tableRec_s.attriNum];
	ATTRIBUTE_REC attriRec_n2[tableRec_n2.attriNum];

	AttributeManager AM_r;
	AttributeManager AM_n1;
	AttributeManager AM_c;
	AttributeManager AM_o;
	AttributeManager AM_l;
	AttributeManager AM_p;
	AttributeManager AM_s;
	AttributeManager AM_n2;

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
	AM_l.getForTableID(tableRec_l, attriRec_l);
	for(int i=0 ; i < (int)tableRec_l.attriNum ; i++){
		cout << attriRec_l[i].attributeName << endl;
	}
	AM_p.getForTableID(tableRec_p, attriRec_p);
	for(int i=0 ; i < (int)tableRec_p.attriNum ; i++){
		cout << attriRec_p[i].attributeName << endl;
	}
	AM_s.getForTableID(tableRec_s, attriRec_s);
	for(int i=0 ; i < (int)tableRec_s.attriNum ; i++){
		cout << attriRec_s[i].attributeName << endl;
	}
	AM_n2.getForTableID(tableRec_n2, attriRec_n2);
	for(int i=0 ; i < (int)tableRec_n2.attriNum ; i++){
		cout << attriRec_n2[i].attributeName << endl;
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

/* selection3 */
	VarStrPosVal pv4(1,25);
	string str2("ECONOMY ANODIZED STEEL");
	pv4.set((unsigned char*)str2.c_str());

	ValueNode vn4 = ValueNode(&pv4);
	ColumnRefNode cn3;
	cn3.tableID = 4;
	cn3.attriID = 5;
	AxprNode an5 = AxprNode(EQ, &cn3, &vn4);
	

/* Join1 */

	OPERATION_NODE pn1[2];
	pn1[0].tableID = 1;
	pn1[0].attributeID = 1;
	pn1[1].tableID = 2;
	pn1[1].attributeID = 3;
	

	JOIN_OPERATION_NODE jpn1[1];
	jpn1[0].rightNode = pn1[0];
	jpn1[0].leftNode = pn1[1];
	
	
/* Join2 */
	OPERATION_NODE pn2[2];
	pn2[0].tableID = 2;
	pn2[0].attributeID = 1;
	pn2[1].tableID = 6;
	pn2[1].attributeID = 4;

	
	JOIN_OPERATION_NODE jpn2[1];
	jpn2[0].rightNode = pn2[0];
	jpn2[0].leftNode = pn2[1];

/* Join3 */
	OPERATION_NODE pn3[2];
	pn3[0].tableID = 6;
	pn3[0].attributeID = 1;
	pn3[1].tableID = 7;
	pn3[1].attributeID = 2;

	
	JOIN_OPERATION_NODE jpn3[1];
	jpn3[0].rightNode = pn3[0];
	jpn3[0].leftNode = pn3[1];
	
/* Join4 */
	OPERATION_NODE pn4[2];
	pn4[0].tableID = 7;
	pn4[0].attributeID = 1;
	pn4[1].tableID = 8;
	pn4[1].attributeID = 1;

	
	JOIN_OPERATION_NODE jpn4[1];
	jpn4[0].rightNode = pn4[0];
	jpn4[0].leftNode = pn4[1];

/* Join5 */
	OPERATION_NODE pn5[2];
	pn5[0].tableID = 4;
	pn5[0].attributeID = 1;
	pn5[1].tableID = 8;
	pn5[1].attributeID = 2;

	
	JOIN_OPERATION_NODE jpn5[1];
	jpn5[0].rightNode = pn5[0];
	jpn5[0].leftNode = pn5[1];
	
/* Join6 */
	OPERATION_NODE pn6[2];
	pn6[0].tableID = 3;
	pn6[0].attributeID = 1;
	pn6[1].tableID = 8;
	pn6[1].attributeID = 3;

	
	JOIN_OPERATION_NODE jpn6[1];
	jpn6[0].rightNode = pn6[0];
	jpn6[0].leftNode = pn6[1];

/* Join7 */
	OPERATION_NODE pn7[2];
	pn7[0].tableID = 2;
	pn7[0].attributeID = 1;
	pn7[1].tableID = 3;
	pn7[1].attributeID = 4;

	
	JOIN_OPERATION_NODE jpn7[1];
	jpn7[0].rightNode = pn7[0];
	jpn7[0].leftNode = pn7[1];



/* Projection1 */

	OPERATION_NODE pro1[1];
	pro1[0].tableID = 1;
	pro1[0].attributeID = 1;

/* Projection2 */

	OPERATION_NODE pro2[2];
	pro2[0].tableID = 2;
	pro2[0].attributeID = 1;
	pro2[1].tableID = 2;
	pro2[1].attributeID = 3;

/* Projection3 */

	OPERATION_NODE pro3[1];
	pro3[0].tableID = 6;
	pro3[0].attributeID = 1;
	
/* Projection4 */

	OPERATION_NODE pro4[2];
	pro4[0].tableID = 7;
	pro4[0].attributeID = 1;
	pro4[1].tableID = 7;
	pro4[1].attributeID = 5;

/* Projection5 */
	
	OPERATION_NODE pro5[1];
	pro5[0].tableID = 4;
	pro5[0].attributeID = 1;

/* Projection6 */
	
	OPERATION_NODE pro6[2];
	pro6[0].tableID = 3;
	pro6[0].attributeID = 1;
	pro6[1].tableID = 3;
	pro6[1].attributeID = 4;

/* Projection7 */
	
	OPERATION_NODE pro7[1];
	pro7[0].tableID = 2;
	pro7[0].attributeID = 1;



	o1 = new Scan(&db_r, attriRec_r, 3);
	cout << "OK new o1" << endl;
	o2 = new Selection((Node *)&an1 ,(unsigned int)1);
	cout << "OK new o2" << endl;
	o2->setPreOperator(o1);
	o3 = new Projection(pro1, 1);
	o3->setPreOperator(o2);
	cout << "OK new o3" << endl;
	
	o4 = new Scan(&db_n1, attriRec_n1, 4);
	cout << "OK new o4" << endl;
	o5 = new OneSideHashJoin(o3, o4 , jpn1, 1);
	cout << "OK new o5" << endl;
	o6 = new Projection(pro2, 1);
	o6->setPreOperator(o5);
	cout << "OK new o6" << endl;
	
	
	o7 = new Scan(&db_c, attriRec_c, 8);
	cout << "OK new o7" << endl;
	o8 = new OneSideHashJoin(o6, o7 , jpn2, 1);
	cout << "OK new o8" << endl;
	o9 = new Projection(pro3, 1);
	o9->setPreOperator(o8);
	cout << "OK new o9" << endl;
	

	o10 = new Scan(&db_o, attriRec_o, 9);
	cout << "OK new o10" << endl;
	o11 = new Selection((Node *)&an4 ,(unsigned int)2);
	cout << "OK new o11" << endl;
	o11->setPreOperator(o10);
	
	o12 = new OneSideHashJoin(o9, o11 , jpn3, 1);
	cout << "OK new o12" << endl;


	o13 = new Projection(pro4, 1);
	o13->setPreOperator(o12);
	cout << "OK new o13" << endl;
	
	o14 = new Scan(&db_l, attriRec_l, 16);
	cout << "OK new o14" << endl;
	o15 = new OneSideHashJoin(o13, o14 , jpn4, 2);
	cout << "OK new o15" << endl;

	o16 = new Scan(&db_p, attriRec_p, 9);
	cout << "OK new o16" << endl;
	o17 = new Selection((Node *)&an5 ,(unsigned int)1);
	cout << "OK new o17" << endl;
	o17->setPreOperator(o16);
	o18 = new Projection(pro5, 1);
	o18->setPreOperator(o17);
	cout << "OK new o18" << endl;
	o19 = new OneSideHashJoin(o18, o15 , jpn5, 1);
	cout << "OK new o19" << endl;
	
	
	o20 = new Scan(&db_s, attriRec_s, 7);
	cout << "OK new o20" << endl;
	o21 = new Projection(pro6, 2);
	o21->setPreOperator(o20);
	cout << "OK new o21" << endl;
	o22 = new OneSideHashJoin(o21, o19 , jpn6, 1);
	cout << "OK new o22" << endl;
	
	o23 = new Scan(&db_n2, attriRec_n2, 4);
	cout << "OK new o23" << endl;
	o24 = new Projection(pro7, 1);
	o24->setPreOperator(o23);
	cout << "OK new o24" << endl;
	o25 = new OneSideHashJoin(o24, o22 , jpn7, 1);
	cout << "OK new o25" << endl;


	o26 = new OutPut(STD_OUT);
	cout << "OK new o26" << endl;

	o26->setPreOperator(o25);
	o26->init();
	cout << "TEST START" << endl;
	o26->exec();
}
	
