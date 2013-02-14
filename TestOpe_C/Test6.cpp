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
#include"ScanRLE.h"
#include"SelectBitOut.h"
#include"BitFilter.h"
#include"BitSort.h"

#include"ScanJoinIndex.h"
#include"JoinIndex_OneHash.h"
#include"ScanFromJI.h"
#include"ConnectJI.h"
/*
#include"JoinFromJoinIndex.h"
*/

int main(){
	chdir("../RunData");
	BDBOpe db_r_1("1.1.DSM");
	BDBOpe db_r_2("1.2.DSM");
	BDBOpe db_n_1("2.1.DSM");
	BDBOpe db_n2_1("2.1.DSM");
	BDBOpe db_n_2("2.2.DSM");
	BDBOpe db_n_3("2.3.DSM");
	BDBOpe db_s_1("3.1.DSM");
	BDBOpe db_s_4("3.4.DSM");
	BDBOpe db_p_1("4.1.DSM");
	BDBOpe db_p_5("4.5.DSM");
	BDBOpe db_c_1("6.1.DSM");
	BDBOpe db_c_4("6.4.DSM");
	BDBOpe db_o_1("7.1.DSM");
	BDBOpe db_o_2("7.2.DSM");
	BDBOpe db_o_5("7.5.DSM");
	BDBOpe db_l_1("8.1.DSM");
	BDBOpe db_l_2("8.2.DSM");
	BDBOpe db_l_3("8.3.DSM");
	BDBOpe db_l_6("8.6.DSM");
	BDBOpe db_l_16("8.16.DSM");
	
	Operator *o1, *o2, *o3, *o4, *o5, *o6, *o7, *o8, *o9, *o10;
	Operator *o11, *o12, *o13, *o14, *o15, *o16, *o17, *o18, *o19, *o20;
	Operator *o21, *o22, *o23, *o24, *o25, *o26, *o27, *o28, *o29, *o30;
	Operator *o31, *o32, *o33, *o34, *o35, *o36, *o37, *o38, *o39, *o40;
	db_r_1.open();
	db_r_2.open();
	db_n_1.open();
	db_n2_1.open();
	db_n_2.open();
	db_n_3.open();
	db_s_1.open();
	db_s_4.open();
	db_p_1.open();
	db_p_5.open();
	db_c_1.open();
	db_c_4.open();
	db_o_1.open();
	db_o_2.open();
	db_o_5.open();
	db_l_1.open();
	db_l_2.open();
	db_l_3.open();
	db_l_6.open();
	db_l_16.open();
	
	
	TABLE_REC tableRec_r;
	TABLE_REC tableRec_n;
	TABLE_REC tableRec_s;
	TABLE_REC tableRec_p;
	TABLE_REC tableRec_c;
	TABLE_REC tableRec_o;
	TABLE_REC tableRec_l;

	tableRec_r.tableID = 1;
	tableRec_r.attriNum = 3;

	tableRec_n.tableID = 2;
	tableRec_n.attriNum = 4;
	
	tableRec_s.tableID = 3;
	tableRec_s.attriNum = 7;
	
	tableRec_p.tableID = 4;
	tableRec_p.attriNum = 9;
	
	tableRec_c.tableID = 6;
	tableRec_c.attriNum = 8;
	
	tableRec_o.tableID = 7;
	tableRec_o.attriNum = 9;
	
	tableRec_l.tableID = 8;
	tableRec_l.attriNum = 16;
	
	
	ATTRIBUTE_REC attriRec_r[tableRec_r.attriNum];
	ATTRIBUTE_REC attriRec_n[tableRec_n.attriNum];
	ATTRIBUTE_REC attriRec_s[tableRec_s.attriNum];
	ATTRIBUTE_REC attriRec_p[tableRec_p.attriNum];
	ATTRIBUTE_REC attriRec_c[tableRec_c.attriNum];
	ATTRIBUTE_REC attriRec_o[tableRec_o.attriNum];
	ATTRIBUTE_REC attriRec_l[tableRec_l.attriNum];

	AttributeManager AM_r;
	AttributeManager AM_n;
	AttributeManager AM_s;
	AttributeManager AM_p;
	AttributeManager AM_c;
	AttributeManager AM_o;
	AttributeManager AM_l;
	
	AM_r.getForTableID(tableRec_r, attriRec_r);
	for(int i=0 ; i < (int)tableRec_r.attriNum ; i++){
		cout << attriRec_r[i].attributeName << endl;
	}
	AM_n.getForTableID(tableRec_n, attriRec_n);
	for(int i=0 ; i < (int)tableRec_n.attriNum ; i++){
		cout << attriRec_n[i].attributeName << endl;
	}
	AM_s.getForTableID(tableRec_s, attriRec_s);
	for(int i=0 ; i < (int)tableRec_s.attriNum ; i++){
		cout << attriRec_s[i].attributeName << endl;
	}
	AM_p.getForTableID(tableRec_p, attriRec_p);
	for(int i=0 ; i < (int)tableRec_p.attriNum ; i++){
		cout << attriRec_p[i].attributeName << endl;
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

/*

Join 
	OPERATION_NODE op1, op2;
	op1.tableID = 1;
	op1.attributeID = 2;
	op2.tableID = 2;
	op2.attributeID = 2;
	
	JOIN_OPERATION_NODE jon;
	jon.rightNode = op1;
	jon.leftNode = op2;
*/	
/*
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
	
	JoinIndex_OneHash *J1 = new JoinIndex_OneHash(o4, o5); 
	J1->init();
	
	o6 = new ScanDSM(&db_n_1, &attriRec_n[0], 1);
	cout << "OK new o6" << endl;
	
	o7 = new ScanFromJI(o6, J1->createJoinIndex());
	cout << "OK new o7" << endl;

	o8 = new ScanRLE(&db_c_4, &attriRec_c[3], 1);
	cout << "OK new o8" << endl;

	JoinIndex_OneHash *J2 = new JoinIndex_OneHash(o7, o8); 
	J2->init();

	
	o9 = new ScanDSM(&db_c_1, &attriRec_c[0], 1);
	cout << "OK new o9" << endl;
	
	
	o10 = new ScanFromJI(o9, J2->createJoinIndex());
	cout << "OK new o10" << endl;




	o11 = new ScanRLE(&db_o_5, &attriRec_o[4], 1);
	cout << "OK new o11" << endl;

	o12 = new SelectBitOut((Node *)&an4 ,2);
	cout << "OK new o12" << endl;
	o12->setPreOperator(o11);

	o13 = new BitSort();
	o13->setPreOperator(o12);
	cout << "OK new o13" << endl;

	o14 = new ScanDSM(&db_o_1, &attriRec_o[0], 1);
	cout << "OK new o14" << endl;

	o15 = new BitFilter(o14, o13);
	cout << "OK new o15" << endl;
	o15->init();

	
	o16 = new ScanRLE(&db_o_2, &attriRec_o[1], 1);
	cout << "OK new o16" << endl;
	
	
	JoinIndex_OneHash *J3 = new JoinIndex_OneHash(o10, o16); 
	J3->init();
	
	o17 = new ScanFromJI(o15, J3->createJoinIndex());
	cout << "OK new o17" << endl;
	
	
	


	o18 = new ScanRLE(&db_l_1, &attriRec_l[0], 1);
	cout << "OK new o18" << endl;
	
	JoinIndex_OneHash *J4 = new JoinIndex_OneHash(o17, o18); 
	J4->init();

	
	o19 = new ScanDSM(&db_l_16, &attriRec_l[15], 1);
	cout << "OK new o19" << endl;

	o20 = new ScanFromJI(o19, J5->createJoinIndex());
	cout << "OK new o20" << endl;
*/	
	


	/*
	o21 = new ScanDSM(&db_p_5, &attriRec_p[4], 1);
	cout << "OK new o21" << endl;

	o22 = new SelectBitOut((Node *)&an5 ,1);
	cout << "OK new o22" << endl;
	o22->setPreOperator(o21);
	
	o23 = new ScanDSM(&db_p_1, &attriRec_p[0], 1);
	cout << "OK new o23" << endl;

	o24 = new BitFilter(o23, o22);
	cout << "OK new o24" << endl;
	o24->init();

	o25 = new ScanRLE(&db_l_2, &attriRec_l[1], 1);
	cout << "OK new o25" << endl;
	
	JoinIndex_OneHash *J5 = new JoinIndex_OneHash(o24, o25); 
	J5->init();
	*/
	
	o26 = new ScanDSM(&db_s_1, &attriRec_s[0], 1);
	cout << "OK new o26" << endl;
	
	o27 = new ScanRLE(&db_l_3, &attriRec_l[2], 1);
	cout << "OK new o27" << endl;
	
	JoinIndex_OneHash *J6 = new JoinIndex_OneHash(o26, o27); 
	J6->init();
	
	
	
	o28 = new ScanDSM(&db_n2_1, &attriRec_n[0], 1);
	cout << "OK new o28" << endl;
	
	o29 = new ScanRLE(&db_s_4, &attriRec_s[3], 1);
	cout << "OK new o29" << endl;
	
	JoinIndex_OneHash *J7 = new JoinIndex_OneHash(o28, o29); 
	J7->init();
	
	ConnectJI *cj1 = new ConnectJI(J6->createJoinIndex(), J7->createJoinIndex());
	cj1->init();
	
	cj1->createJoinIndex();
	
	
	/*
	o14 = new BitFilter(o13, o12);
	cout << "OK new o14" << endl;
	*/
/*	
	
	
	o15 = new ScanDSM(&db_o_1, &attriRec_o[0], 1);
	cout << "OK new o15" << endl;
	
	
	o16 = new ScanFromJI(o15, J3->createJoinIndex());
	cout << "OK new o16" << endl;
	
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
	
	/*
	o30 = new OutPut(STD_OUT);
	cout << "OK new o30" << endl;
	o30->setPreOperator(o20);
	o30->init();
	cout << "TEST START" << endl;
	o30->exec();
	
	/*
	o7 = new OutPut(STD_OUT);
	cout << "OK new o7" << endl;
	o7->setPreOperator(o2);
	o7->init();
	cout << "TEST START" << endl;
	o7->exec();
	*/
}
	
