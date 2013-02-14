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
#include"Projection.h"

#include"ScanDSM.h"
#include"ScanRLE.h"
#include"SelectBitOut.h"
#include"BitFilter.h"

#include"ScanJoinIndex.h"
#include"JoinIndex_OneHash.h"
#include"ScanFromJI.h"
#include"ScanFromJI_OneHash.h"
/*
#include"JoinFromJoinIndex.h"
*/

int main(){
	chdir("../RunData");
	BDBOpe db_r_1("1.1.DSM");
	BDBOpe db_r_2("1.2.DSM");
	BDBOpe db_n_1("2.1.DSM");
	BDBOpe db_n_2("2.2.DSM");
	BDBOpe db_n_3("2.3.DSM");
	BDBOpe db_c_1("6.1.DSM");
	BDBOpe db_c_4("6.4.DSM_C");
	BDBOpe db_o_1("7.1.DSM");
	BDBOpe db_o_2("7.2.DSM_C");
	BDBOpe db_o_5("7.5.DSM");
	Operator *o1, *o2, *o3, *o4, *o5, *o6, *o7, *o8, *o9, *o10;
	Operator *o11, *o12, *o13, *o14, *o15, *o16, *o17, *o18, *o19, *o20;
	db_r_1.open();
	db_r_2.open();
	db_n_1.open();
	db_n_2.open();
	db_n_3.open();
	db_c_1.open();
	db_c_4.open();
	db_o_1.open();
	db_o_2.open();
	db_o_5.open();
	
	
	TABLE_REC tableRec_r;
	TABLE_REC tableRec_n;
	TABLE_REC tableRec_c;
	TABLE_REC tableRec_o;


	tableRec_r.tableID = 1;
	tableRec_r.attriNum = 3;

	tableRec_n.tableID = 2;
	tableRec_n.attriNum = 4;
	
	tableRec_c.tableID = 6;
	tableRec_c.attriNum = 8; 
	
	tableRec_o.tableID = 7;
	tableRec_o.attriNum = 9;
	
	ATTRIBUTE_REC attriRec_r[tableRec_r.attriNum];
	ATTRIBUTE_REC attriRec_n[tableRec_n.attriNum];
	ATTRIBUTE_REC attriRec_c[tableRec_c.attriNum];
	ATTRIBUTE_REC attriRec_o[tableRec_o.attriNum];

	AttributeManager AM_r;
	AttributeManager AM_n;
	AttributeManager AM_c;
	AttributeManager AM_o;
	
	AM_r.getForTableID(tableRec_r, attriRec_r);
	for(int i=0 ; i < (int)tableRec_r.attriNum ; i++){
		cout << attriRec_r[i].attributeName << endl;
	}
	AM_n.getForTableID(tableRec_n, attriRec_n);
	for(int i=0 ; i < (int)tableRec_n.attriNum ; i++){
		cout << attriRec_n[i].attributeName << endl;
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
	

	
/*Join1*/
	OPERATION_NODE jop1, jop2;
	jop1.tableID = 6;
	jop1.attributeID = 4;
	jop2.tableID = 6;
	jop2.attributeID = 1;
	
	JOIN_OPERATION_NODE jon1;
	jon1.rightNode = jop1;
	jon1.leftNode = jop2;

/* Projection */

	OPERATION_NODE pro1[1];
	pro1[0].tableID = 6;
	pro1[0].attributeID = 1;


	OPERATION_NODE op1;
	op1.tableID = 2;
	op1.attributeID = 3;
	
	OPERATION_NODE op2;
	op2.tableID = 6;
	op2.attributeID = 4;


	o1 = new ScanDSM(&db_r_2, &attriRec_r[1], 1);
	cout << "OK new o1" << endl;
	
	o2 = new SelectBitOut((Node *)&an1 ,(unsigned int)1);
	cout << "OK new o2" << endl;
	o2->setPreOperator(o1);
	
	o3 = new ScanDSM(&db_r_1, attriRec_r, 1);
	cout << "OK new o3" << endl;
	
	o4 = new BitFilter(o3, o2);
	cout << "OK new o4" << endl;
	
	
	o5 = new ScanDSM(&db_n_3, &attriRec_n[2], 1);
	cout << "OK new o5" << endl;
	
	o6 = new JoinIndex_OneHash(o4, o5); 
	cout << "OK new o6" << endl;
	
	o7 = new ScanDSM(&db_n_1, &attriRec_n[0], 1);
	cout << "OK new o7" << endl;
	
	o8 = new ScanFromJI(o7, o6, &op1);
	cout << "OK new o8" << endl;

	o9 = new ScanRLE(&db_c_4, &attriRec_c[3], 1);
	cout << "OK new o9" << endl;

	o10 = new JoinIndex_OneHash(o8, o9); 
	cout << "OK new o10" << endl;
	
	o11 = new ScanDSM(&db_c_1, &attriRec_c[0], 1);
	cout << "OK new o11" << endl;
	
	o12 = new ScanFromJI_OneHash(o10, o11, &jon1);
	cout << "OK new o8" << endl;
	
	o13 = new Projection(pro1, 1);
	o13->setPreOperator(o12);
	

	//o14 = new ScanRLE(&db_o_2, &attriRec_o[1], 1);
	//cout << "OK new o9" << endl;
	
	/*
	o13 = new ScanRLE(&db_o_5, &attriRec_o[4], 1);
	cout << "OK new o13" << endl;

	o14 = new SelectBitOut((Node *)&an4 ,(unsigned int)2);
	cout << "OK new o14" << endl;
	o14->setPreOperator(o13);
/*
	o15 = new BitSort();
	o15->setPreOperator(o14);
	
	o16 = new ScanDSM(&db_o_1, &attriRec_o[0], 1);
	cout << "OK new o16" << endl;

	o17 = new BitFilter(o16, o15);
	cout << "OK new o17" << endl;
	o17->init();
	/*
	o2 = new ScanDSM(&db4, attriRec_n + 2, 1);
	cout << "OK new o2" << endl;
	
	JoinIndex_OneHash *JI = new JoinIndex_OneHash(o1, o2); 
	JI->init();
	
	
	o3 = new ScanDSM(&db2, attriRec_r + 1, 1);
	cout << "OK new o3" << endl;
	o4 = new ScanDSM(&db3, attriRec_n + 1, 1);
	cout << "OK new o4" << endl;
	*/
	/*
	JOIN_INDEX *J = JI->createJoinIndex();

	J->ScanNode->setkey(1);
	cout << J->ScanNode->getRow(NULL, 0) << endl;
	


	
	o5 = new JoinFromJoinIndex(o3, o4, JI->createJoinIndex(), &jon);
	cout << "OK new o5" << endl;
	*/
	o20 = new OutPut(STD_OUT);
	cout << "OK new o20" << endl;
	o20->setPreOperator(o13);
	o20->init();
	cout << "TEST START" << endl;
	o20->exec();
	
	/*
	o7 = new OutPut(STD_OUT);
	cout << "OK new o7" << endl;
	o7->setPreOperator(o2);
	o7->init();
	cout << "TEST START" << endl;
	o7->exec();
	*/
}
	
