#include<iostream>
#include<string>
#include<cstdlib>
#include<cassert>
#include<db_cxx.h>
#include <iomanip>

#include"CommonDataDef.h"
#include"PosVal.h"
#include"AttributeManager.h"
#include"EnvDB.h"
#include"BDBOpe.h"

#include"Operator.h"
#include"Scan.h"
#include"ScanHash.h"
#include"Selection.h"
#include"Projection.h"
#include"Sort.h"
#include"HashJoin.h"
#include"HashJoin_old.h"
#include"OneSideHashJoin.h"
#include"OneSideHashJoin_old.h"
#include"Extract.h"
#include"OutPut.h"
#include"GroupBy.h"


#include"ScanDSM.h"
#include"ScanRLE.h"
#include"SelectBitOut.h"
#include"BitFilter.h"
#include"BitSort.h"

#include"ScanJoinIndex.h"
#include"JoinIndex_OneHash.h"
#include"ScanFromJI.h"
#include"ScanFromJI_OneHash.h"

int main(){
	chdir(QUERY_DATA_PATH);
	EnvDB *env = new EnvDB();
	env->open();
	
	BDBOpe db_r_1(env->getEnv(), "9.1.DSM");
	BDBOpe db_r_2(env->getEnv(), "9.2.DSM");
	BDBOpe db_n_1(env->getEnv(), "10.1.DSM");
	BDBOpe db_n_2(env->getEnv(), "10.2.DSM");
	BDBOpe db_n_3(env->getEnv(), "10.3.DSM");
	BDBOpe db_s_1(env->getEnv(), "11.1.DSM");
	BDBOpe db_s_4(env->getEnv(), "11.4.DSM");
	BDBOpe db_c_1(env->getEnv(), "14.1.DSM");
	BDBOpe db_c_4(env->getEnv(), "14.4.DSM");
	BDBOpe db_o_1(env->getEnv(), "15.1.DSM");
	BDBOpe db_o_2(env->getEnv(), "15.2.DSM");
	BDBOpe db_o_5(env->getEnv(), "15.5.DSM");
	BDBOpe db_l_1(env->getEnv(), "16.1.DSM");
	BDBOpe db_l_3(env->getEnv(), "16.3.DSM");
	BDBOpe db_l_6(env->getEnv(), "16.6.DSM");
	BDBOpe db_l_7(env->getEnv(), "16.7.DSM");
	
	db_r_1.open();
	db_r_2.open();
	db_n_1.open();
	db_n_2.open();
	db_n_3.open();
	db_s_1.open();
	db_s_4.open();
	db_c_1.open();
	db_c_4.open();
	db_o_1.open();
	db_o_2.open();
	db_o_5.open();
	db_l_1.open();
	db_l_3.open();
	db_l_6.open();
	db_l_7.open();


	Operator *o1, *o2, *o3, *o4, *o5, *o6, *o7, *o8, *o9, *o10;
	Operator *o11, *o12, *o13, *o14, *o15, *o16, *o17, *o18, *o19, *o20;
	Operator *o21, *o22, *o23, *o24, *o25, *o26, *o27, *o28, *o29, *o30;
	Operator *o31, *o32, *o33, *o34, *o35, *o36, *o37, *o38, *o39, *o40;



	TABLE_REC tableRec_r;
	TABLE_REC tableRec_n;
	TABLE_REC tableRec_c;
	TABLE_REC tableRec_o;
	TABLE_REC tableRec_l;
	TABLE_REC tableRec_s;

	
/* set table info */
	tableRec_r.tableID = 9;
	tableRec_r.attriNum = 3;
	
	tableRec_n.tableID = 10;
	tableRec_n.attriNum = 4;
	
	tableRec_s.tableID = 11;
	tableRec_s.attriNum = 7;
	
	tableRec_c.tableID = 14;
	tableRec_c.attriNum = 8;

	tableRec_o.tableID = 15;
	tableRec_o.attriNum = 9;
	
	tableRec_l.tableID = 16;
	tableRec_l.attriNum = 16;
	


/* aet attriRec */
	ATTRIBUTE_REC attriRec_r[tableRec_r.attriNum];
	ATTRIBUTE_REC attriRec_n[tableRec_n.attriNum];
	ATTRIBUTE_REC attriRec_s[tableRec_s.attriNum];
	ATTRIBUTE_REC attriRec_c[tableRec_c.attriNum];
	ATTRIBUTE_REC attriRec_o[tableRec_o.attriNum];
	ATTRIBUTE_REC attriRec_l[tableRec_l.attriNum];
	

	AttributeManager AM(env->getEnv());
	

	AM.getForTableID(tableRec_r, attriRec_r);
	AM.getForTableID(tableRec_n, attriRec_n);
	AM.getForTableID(tableRec_c, attriRec_c);
	AM.getForTableID(tableRec_o, attriRec_o);
	AM.getForTableID(tableRec_l, attriRec_l);
	AM.getForTableID(tableRec_s, attriRec_s);

/* selection1 */
	FixStrPosVal pv1(1,25);
	string str1("ASIA");
	pv1.setStr(str1);

	ValueNode vn1 = ValueNode(&pv1);
	ColumnRefNode cn1;
	cn1.tableID = 9;
	cn1.attriID = 2;
	AxprNode an1 = AxprNode(EQ, &cn1, &vn1);
	

/* selection2 */

	DatePosVal pv2(1,(unsigned char *)"1994-01-01");
	DatePosVal pv3(1,(unsigned char *)"1995-01-01");
	

	ValueNode vn2 = ValueNode(&pv2);
	ValueNode vn3 = ValueNode(&pv3);
	ColumnRefNode cn2;
	cn2.tableID = 15;
	cn2.attriID = 5;
	AxprNode an2 = AxprNode(GE, &cn2, &vn2);
	AxprNode an3 = AxprNode(LT, &cn2, &vn3);
	AxprNode an4 = AxprNode(AND, &an2, &an3);
	
	
/* GROUP */
	IntPosVal pv5(1, 1);
	ValueNode vn5 = ValueNode(&pv5);
	ColumnRefNode cn4[2];
	cn4[0].tableID = 16;
	cn4[0].attriID = 6;
	cn4[1].tableID = 16;
	cn4[1].attriID = 7;
	ArithmeticNode arith1(SUB, &vn5, &cn4[1]);
	ArithmeticNode arith2(MUL, &cn4[0], &arith1);
	
	Aggregation *aggre[1];
	aggre[0] = new Sum(&arith2, 2);
	
	
	OPERATION_NODE group[1];
	group[0].tableID = 10;
	group[0].attributeID = 2;
	
/* Sort 1 */
	OPERATION_NODE so1[1];
	so1[0].tableID = 0;
	so1[0].attributeID = 0;
	so1[0].position = 1;
	so1[0].option = 1;

/* Projection1 */

	OPERATION_NODE pro1[2];
	pro1[0].tableID = 10;
	pro1[0].attributeID = 1;
	pro1[1].tableID = 10;
	pro1[1].attributeID = 2;
	
/* Projection2 */

	OPERATION_NODE pro2[3];
	pro2[0].tableID = 11;
	pro2[0].attributeID = 1;
	pro2[1].tableID = 11;
	pro2[1].attributeID = 4;
	pro2[2].tableID = 10;
	pro2[2].attributeID = 2;
	
/* Projection3 */

	OPERATION_NODE pro3[3];
	pro3[0].tableID = 10;
	pro3[0].attributeID = 2;
	pro3[1].tableID = 16;
	pro3[1].attributeID = 6;
	pro3[2].tableID = 16;
	pro3[2].attributeID = 7;

/* Projection4 */

	OPERATION_NODE pro4[3];
	pro4[0].tableID = 10;
	pro4[0].attributeID = 2;
	pro4[1].tableID = 14;
	pro4[1].attributeID = 1;
	pro4[2].tableID = 14;
	pro4[2].attributeID = 4;

/* Projection5 */

	OPERATION_NODE pro5[3];
	pro5[0].tableID = 10;
	pro5[0].attributeID = 2;
	pro5[1].tableID = 14;
	pro5[1].attributeID = 4;
	pro5[2].tableID = 15;
	pro5[2].attributeID = 1;
	
	
	OPERATION_NODE op1;
	op1.tableID = 10;
	op1.attributeID = 3;
	
	OPERATION_NODE op2;
	op2.tableID = 11;
	op2.attributeID = 4;
	
	OPERATION_NODE op3;
	op3.tableID = 16;
	op3.attributeID = 3;
	
	OPERATION_NODE op4;
	op4.tableID = 15;
	op4.attributeID = 2;
	
	OPERATION_NODE op5;
	op5.tableID = 14;
	op5.attributeID = 4;
	
	
/* Join1 */
	OPERATION_NODE pn1[2];
	pn1[0].tableID = 10;
	pn1[0].attributeID = 1;
	pn1[1].tableID = 14;
	pn1[1].attributeID = 4;

	
	JOIN_OPERATION_NODE jpn1[1];
	jpn1[0].rightNode = pn1[0];
	jpn1[0].leftNode = pn1[1];

/* Join2 */
	OPERATION_NODE pn2[2];
	pn2[0].tableID = 14;
	pn2[0].attributeID = 1;
	pn2[1].tableID = 15;
	pn2[1].attributeID = 2;

	
	JOIN_OPERATION_NODE jpn2[1];
	jpn2[0].rightNode = pn2[0];
	jpn2[0].leftNode = pn2[1];
	
/* Join3 */
	OPERATION_NODE pn3[2];
	pn3[0].tableID = 15;
	pn3[0].attributeID = 1;
	pn3[1].tableID = 16;
	pn3[1].attributeID = 1;

	
	JOIN_OPERATION_NODE jpn3[1];
	jpn3[0].rightNode = pn3[0];
	jpn3[0].leftNode = pn3[1];

/* Join4 */
	OPERATION_NODE pn4[4];
	pn4[0].tableID = 11;
	pn4[0].attributeID = 1;
	pn4[1].tableID = 11;
	pn4[1].attributeID = 4;
	pn4[2].tableID = 16;
	pn4[2].attributeID = 3;
	pn4[3].tableID = 14;
	pn4[3].attributeID = 4;

	
	JOIN_OPERATION_NODE jpn4[2];
	jpn4[0].rightNode = pn4[0];
	jpn4[0].leftNode = pn4[2];
	jpn4[1].rightNode = pn4[1];
	jpn4[1].leftNode = pn4[3];

	
/* exec */
	
	o1 = new ScanDSM(&db_r_2, &attriRec_r[1], 1);
	o2 = new SelectBitOut((Node *)&an1 ,(unsigned int)1);
	o2->setPreOperator(o1);
	o3 = new ScanDSM(&db_r_1, &attriRec_r[0], 1);
	o4 = new BitFilter(o3, o2);

	o5 = new ScanDSM(&db_n_3, &attriRec_n[2], 1);
	o6 = new JoinIndex_OneHash(o4, o5); 

	
	o7 = new ScanDSM(&db_n_1, &attriRec_n[0], 1);
	o8 = new ScanFromJI(o7, o6, &op1);
	o9 = new ScanDSM(&db_n_2, &attriRec_n[1], 1);
	//n_name, n_natonkey, r_regionkey, n_nationkey
	o10 = new ScanFromJI(o9, o8, &op1);
	
	//n_name, n_natonkey
	o11 = new Projection(pro1, 2);
	o11->setPreOperator(o10);

	o12 = new ScanDSM(&db_c_4, &attriRec_c[3], 1);
	o13 = new ScanDSM(&db_c_1, &attriRec_c[0], 1);
	o14 = new ScanFromJI(o13, o12, &op5);
	
	o15 = new OneSideHashJoin(o10, o14 , jpn1, 1);
	//n_name, c_custkey, c_nationkey
	o16 = new Projection(pro4, 3);
	o16->setPreOperator(o15);


	o17 = new ScanDSM(&db_o_5, &attriRec_o[4], 1);
	o18 = new SelectBitOut((Node *)&an4 ,(unsigned int)2);
	o18->setPreOperator(o17);
	o19 = new ScanDSM(&db_o_2, &attriRec_o[1], 1);
	o20 = new BitFilter(o19, o18);
	
	o21 = new ScanDSM(&db_o_1, &attriRec_o[0], 1);
	//o_order, o_custkey
	o22 = new ScanFromJI(o21, o20, &op4);
	
	//n_name, c_custkey, c_nationkey, o_order, o_custkey
	o23 = new OneSideHashJoin(o16, o22 , jpn2, 1);
	
	//n_name, c_nationkey, o_order
	o24 = new Projection(pro5, 3);
	o24->setPreOperator(o23);
	

	
	o25 = new ScanDSM(&db_l_3, &attriRec_l[2], 1);
	o26 = new ScanDSM(&db_l_6, &attriRec_l[5], 1);
	o27 = new ScanFromJI(o26, o25, &op3);
	
	o28 = new ScanDSM(&db_l_7, &attriRec_l[6], 1);
	o29 = new ScanFromJI(o28, o27, &op3);
	
	o30 = new ScanDSM(&db_l_1, &attriRec_l[0], 1);
	//l_orderkey, l_extendedprice, l_discount, l_suppkey
	o31 = new ScanFromJI(o30, o29, &op3);
	
	o32 = new OneSideHashJoin(o24, o31 , jpn3, 1);

	o33 = new ScanDSM(&db_s_4, &attriRec_s[3], 1);
	o34 = new ScanDSM(&db_s_1, &attriRec_s[0], 1);
	o35 = new ScanFromJI(o34, o33, &op2);

	o36 = new OneSideHashJoin(o35, o32 , jpn4, 2);



	o37 = new Projection(pro3, 3);
	o37->setPreOperator(o36);
	
	o38 = new GroupBy(group, 1, aggre, 1);
	o38->setPreOperator(o37);

	o39 = new Sort(so1, 1);
	o39->setPreOperator(o38);
	
	o40 = new OutPut(TIME_OUT);

	o40->setPreOperator(o39);
	o40->init(env->getEnv());
	cout << "TEST START Q5 DSM20" << endl;
	
	cout << setprecision(4);
	cout << setiosflags(ios::fixed); 
	o40->exec();
}
