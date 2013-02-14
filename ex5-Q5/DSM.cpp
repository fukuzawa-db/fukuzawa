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
	
	BDBOpe db_r_1(env->getEnv(), "1.1.DSM");
	BDBOpe db_r_2(env->getEnv(), "1.2.DSM");
	BDBOpe db_n_1(env->getEnv(), "2.1.DSM");
	BDBOpe db_n_2(env->getEnv(), "2.2.DSM");
	BDBOpe db_n_3(env->getEnv(), "2.3.DSM");
	BDBOpe db_s_1(env->getEnv(), "3.1.DSM");
	BDBOpe db_s_4(env->getEnv(), "3.4.DSM");
	BDBOpe db_c_1(env->getEnv(), "6.1.DSM");
	BDBOpe db_c_4(env->getEnv(), "6.4.DSM");
	BDBOpe db_o_1(env->getEnv(), "7.1.DSM");
	BDBOpe db_o_2(env->getEnv(), "7.2.DSM");
	BDBOpe db_o_5(env->getEnv(), "7.5.DSM");
	BDBOpe db_l_1(env->getEnv(), "8.1.DSM");
	BDBOpe db_l_3(env->getEnv(), "8.3.DSM");
	BDBOpe db_l_6(env->getEnv(), "8.6.DSM");
	BDBOpe db_l_7(env->getEnv(), "8.7.DSM");
	
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
	Operator *o31, *o32, *o33, *o34, *o35, *o36, *o37, *o38, *o39;



	TABLE_REC tableRec_r;
	TABLE_REC tableRec_n;
	TABLE_REC tableRec_c;
	TABLE_REC tableRec_o;
	TABLE_REC tableRec_l;
	TABLE_REC tableRec_s;

	
/* set table info */
	tableRec_r.tableID = 1;
	tableRec_r.attriNum = 3;
	
	tableRec_n.tableID = 2;
	tableRec_n.attriNum = 4;
	
	tableRec_s.tableID = 3;
	tableRec_s.attriNum = 7;
	
	tableRec_c.tableID = 6;
	tableRec_c.attriNum = 8;

	tableRec_o.tableID = 7;
	tableRec_o.attriNum = 9;
	
	tableRec_l.tableID = 8;
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
	cn1.tableID = 1;
	cn1.attriID = 2;
	AxprNode an1 = AxprNode(EQ, &cn1, &vn1);
	

/* selection2 */

	DatePosVal pv2(1,(unsigned char *)"1994-01-01");
	DatePosVal pv3(1,(unsigned char *)"1995-01-01");
	

	ValueNode vn2 = ValueNode(&pv2);
	ValueNode vn3 = ValueNode(&pv3);
	ColumnRefNode cn2;
	cn2.tableID = 7;
	cn2.attriID = 5;
	AxprNode an2 = AxprNode(GE, &cn2, &vn2);
	AxprNode an3 = AxprNode(LT, &cn2, &vn3);
	AxprNode an4 = AxprNode(AND, &an2, &an3);
	
	
/* GROUP */
	IntPosVal pv5(1, 1);
	ValueNode vn5 = ValueNode(&pv5);
	ColumnRefNode cn4[2];
	cn4[0].tableID = 8;
	cn4[0].attriID = 6;
	cn4[1].tableID = 8;
	cn4[1].attriID = 7;
	ArithmeticNode arith1(SUB, &vn5, &cn4[1]);
	ArithmeticNode arith2(MUL, &cn4[0], &arith1);
	
	Aggregation *aggre[1];
	aggre[0] = new Sum(&arith2, 2);
	
	
	OPERATION_NODE group[1];
	group[0].tableID = 2;
	group[0].attributeID = 2;
	
/* Sort 1 */
	OPERATION_NODE so1[1];
	so1[0].tableID = 0;
	so1[0].attributeID = 0;
	so1[0].position = 1;
	so1[0].option = 1;

/* Projection1 */

	OPERATION_NODE pro1[2];
	pro1[0].tableID = 2;
	pro1[0].attributeID = 1;
	pro1[1].tableID = 2;
	pro1[1].attributeID = 2;
	
/* Projection2 */

	OPERATION_NODE pro2[3];
	pro2[0].tableID = 3;
	pro2[0].attributeID = 1;
	pro2[1].tableID = 3;
	pro2[1].attributeID = 4;
	pro2[2].tableID = 2;
	pro2[2].attributeID = 2;
	
/* Projection3 */

	OPERATION_NODE pro3[3];
	pro3[0].tableID = 2;
	pro3[0].attributeID = 2;
	pro3[1].tableID = 8;
	pro3[1].attributeID = 6;
	pro3[2].tableID = 8;
	pro3[2].attributeID = 7;
	
	
	OPERATION_NODE op1;
	op1.tableID = 2;
	op1.attributeID = 3;
	
	OPERATION_NODE op2;
	op2.tableID = 3;
	op2.attributeID = 4;
	
	OPERATION_NODE op3;
	op3.tableID = 8;
	op3.attributeID = 3;
	
	OPERATION_NODE op4;
	op4.tableID = 7;
	op4.attributeID = 2;
	
	OPERATION_NODE op5;
	op5.tableID = 6;
	op5.attributeID = 4;
	
	
/* Join1 */
	OPERATION_NODE pn1[4];
	pn1[0].tableID = 6;
	pn1[0].attributeID = 1;
	pn1[1].tableID = 6;
	pn1[1].attributeID = 4;
	pn1[2].tableID = 7;
	pn1[2].attributeID = 2;
	pn1[3].tableID = 3;
	pn1[3].attributeID = 4;

	
	JOIN_OPERATION_NODE jpn1[2];
	jpn1[0].rightNode = pn1[0];
	jpn1[0].leftNode = pn1[2];
	jpn1[1].rightNode = pn1[1];
	jpn1[1].leftNode = pn1[3];
	
/* exec */
	
	o1 = new ScanDSM(&db_r_2, &attriRec_r[1], 1);
//	cout << "OK new o1" << endl;
	
	o2 = new SelectBitOut((Node *)&an1 ,(unsigned int)1);
//	cout << "OK new o2" << endl;
	o2->setPreOperator(o1);
	
	o3 = new ScanDSM(&db_r_1, &attriRec_r[0], 1);
//	cout << "OK new o3" << endl;
	
	o4 = new BitFilter(o3, o2);
//	cout << "OK new o4" << endl;

	o5 = new ScanDSM(&db_n_3, &attriRec_n[2], 1);
//	cout << "OK new o5" << endl;
	
	o6 = new JoinIndex_OneHash(o4, o5); 
//	cout << "OK new o6" << endl;

	
	o7 = new ScanDSM(&db_n_1, &attriRec_n[0], 1);
//	cout << "OK new o7" << endl;
	
	o8 = new ScanFromJI(o7, o6, &op1);
//	cout << "OK new o8" << endl;
	
	o9 = new ScanDSM(&db_n_2, &attriRec_n[1], 1);
//	cout << "OK new o9" << endl;
	
	//n_name, n_natonkey, r_regionkey, n_nationkey
	o10 = new ScanFromJI(o9, o8, &op1);
//	cout << "OK new o10" << endl;
	
	//n_name, n_natonkey
	o11 = new Projection(pro1, 2);
	o11->setPreOperator(o10);
//	cout << "OK new o11" << endl;
	
	o12 = new ScanDSM(&db_s_4, &attriRec_s[3], 1);
//	cout << "OK new o12" << endl;
	
	o13 = new JoinIndex_OneHash(o11, o12); 
//	cout << "OK new o13" << endl;
	
	o14 = new ScanDSM(&db_s_1, &attriRec_s[0], 1);
//	cout << "OK new o14" << endl;
	
	o15 = new ScanFromJI(o14, o13, &op2);
//	cout << "OK new o15" << endl;
	
	//s_suppkey s_nationkey n_name
	o16 = new Projection(pro2, 3);
	o16->setPreOperator(o15);
//	cout << "OK new o16" << endl;
	
	o17 = new ScanDSM(&db_l_3, &attriRec_l[2], 1);
//	cout << "OK new o17" << endl;
	
	o18 = new JoinIndex_OneHash(o16, o17); 
//	cout << "OK new o18" << endl;
	
	o19 = new ScanDSM(&db_l_6, &attriRec_l[5], 1);
//	cout << "OK new o19" << endl;
	
	o20 = new ScanFromJI(o19, o18, &op3);
//	cout << "OK new o20" << endl;
	
	o21 = new ScanDSM(&db_l_7, &attriRec_l[6], 1);
//	cout << "OK new o21" << endl;
	
	o22 = new ScanFromJI(o21, o20, &op3);
//	cout << "OK new o22" << endl;
	
	o23 = new ScanDSM(&db_l_1, &attriRec_l[0], 1);
//	cout << "OK new o23" << endl;
	
	//l_orderkey, l_extendedprice, l_discount, s_suppkey, s_nationkey, n_name, l_suppkey
	o24 = new ScanFromJI(o23, o22, &op3);
//	cout << "OK new o24" << endl;
	
	
	
	o25 = new ScanDSM(&db_o_5, &attriRec_o[4], 1);
//	cout << "OK new o25" << endl;
	
	o26 = new SelectBitOut((Node *)&an4 ,(unsigned int)2);
//	cout << "OK new o26" << endl;
	o26->setPreOperator(o25);
	
	o27 = new ScanDSM(&db_o_2, &attriRec_o[1], 1);
//	cout << "OK new o27" << endl;
	
	o28 = new BitFilter(o27, o26);
//	cout << "OK new o28" << endl;
	
	o29 = new ScanDSM(&db_o_1, &attriRec_o[0], 1);
//	cout << "OK new o29" << endl;
	
	//o_order, o_custkey
	o30 = new ScanFromJI(o29, o28, &op4);
//	cout << "OK new o30" << endl;
	
	//o_custkey, o_orderkey, l_orderkey, l_extendedprice, l_discount, s_suppkey, s_nationkey, n_name, l_suppkey
	o31 = new JoinIndex_OneHash(o30, o24); 
//	cout << "OK new o31" << endl;

	o32 = new ScanDSM(&db_c_4, &attriRec_c[3], 1);
//	cout << "OK new o32" << endl;
	
	o33 = new ScanDSM(&db_c_1, &attriRec_c[0], 1);
//	cout << "OK new o33" << endl;
	
	o34 = new ScanFromJI(o33, o32, &op5);
//	cout << "OK new o34" << endl;
	
	o35 = new OneSideHashJoin(o34, o31 , jpn1, 2);
//	cout << "OK new o31" << endl;
	
	
	o36 = new Projection(pro3, 3);
	o36->setPreOperator(o35);
//	cout << "OK new o36" << endl;
	
	o37 = new GroupBy(group, 1, aggre, 1);
	o37->setPreOperator(o36);
//	cout << "OK new o37" << endl;

	o38 = new Sort(so1, 1);
	o38->setPreOperator(o37);
//	cout << "OK new o38" << endl;
	
	o39 = new OutPut(TIME_OUT);
//	cout << "OK new o39" << endl;

	o39->setPreOperator(o38);
	o39->init(env->getEnv());
	cout << "TEST START" << endl;
	
	cout << setprecision(4);
	cout << setiosflags(ios::fixed); 
	o39->exec();
}
