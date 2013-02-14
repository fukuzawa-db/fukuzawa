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
#include"SecondDB.h"
#include"InMemDB.h"
#include"IndexExtract.h"

#include"Operator.h"
#include"Scan.h"
#include"ScanHash.h"
#include"IndexScan.h"
#include"Selection.h"
#include"Projection.h"
#include"Sort.h"
#include"HashJoin.h"
#include"HashJoin_old.h"
#include"NestedJoin_Index.h"
#include"OneSideHashJoin.h"
#include"OneSideHashJoin_old.h"
#include"Extract.h"
#include"OutPut.h"
#include"GroupBy.h"

#include"Node.h"
#include"ArithmeticNode.h"
#include"AxprNode.h"
#include"ValueNode.h"
#include"ColumnRefNode.h"

#include"ScanDSM.h"
#include"ScanRLE.h"
#include"SelectBitOut.h"
#include"BitFilter.h"
#include"BitSort.h"

#include"ScanJoinIndex.h"
#include"JoinIndex_OneHash.h"
#include"ScanFromJI.h"
#include"ScanFromJI_OneHash.h"

#include"Aggregation.h"
#include"Count.h"
#include"Min.h"
#include"Max.h"
#include"Sum.h"
#include"Avg.h"

#include"IntPosVal.h"
#include"LongPosVal.h"
#include"FloatPosVal.h"
#include"DoublePosVal.h"
#include"FixStrPosVal.h"
#include"VarStrPosVal.h"
#include"DatePosVal.h"

int main(){
	chdir(QUERY_DATA_PATH);
	EnvDB *env = new EnvDB();
	env->open();
	
	BDBOpe db_r_1(env->getEnv(), "1.1.DSM");
	BDBOpe db_r_2(env->getEnv(), "1.2.DSM");
	BDBOpe db_n(env->getEnv(), "NATION.row");
	BDBOpe db_s_1(env->getEnv(), "3.1.DSM");
	BDBOpe db_s_4(env->getEnv(), "3.4.DSM");
	BDBOpe db_c(env->getEnv(), "CUSTOMER.row");
	BDBOpe db_o(env->getEnv(), "ORDERS.row");
	BDBOpe db_l(env->getEnv(), "LINEITEM.row");
	
	SecondDB *sDB;
	int (*pf)(Db *sdbp, const Dbt*pkey, const Dbt *pdata, Dbt *skey);
	pf = L_1_secondary;
	sDB = new SecondDB(env->getEnv(), "8.1.secondary");
	sDB->setNumCmp();
	
	
	SecondDB *sDB3;
	int (*pf3)(Db *sdbp, const Dbt*pkey, const Dbt *pdata, Dbt *skey);
	pf3 = N_3_secondary;
	sDB3 = new SecondDB(env->getEnv(), "2.3.secondary");
	sDB3->setNumCmp();
	
	SecondDB *sDB4;
	int (*pf4)(Db *sdbp, const Dbt*pkey, const Dbt *pdata, Dbt *skey);
	pf4 = C_4_secondary;
	sDB4 = new SecondDB(env->getEnv(), "6.4.secondary");
	sDB4->setNumCmp();
	
	SecondDB *sDB5;
	int (*pf5)(Db *sdbp, const Dbt*pkey, const Dbt *pdata, Dbt *skey);
	pf5 = O_2_secondary;
	sDB5 = new SecondDB(env->getEnv(), "7.2.secondary");
	sDB5->setNumCmp();
	
	
	db_r_1.open();
	db_r_2.open();
	db_n.open();
	db_s_1.open();
	db_s_4.open();
	db_c.open();
	db_o.open();
	db_l.open();
	
	sDB->open(0);
	db_l.associate(sDB->getDb(), pf);
	sDB->openCursor();
	
	
	sDB3->open(0);
	db_n.associate(sDB3->getDb(), pf3);
	sDB3->openCursor();
	
	sDB4->open(0);
	db_c.associate(sDB4->getDb(), pf4);
	sDB4->openCursor();
	
	sDB5->open(0);
	db_o.associate(sDB5->getDb(), pf5);
	sDB5->openCursor();


	Operator *o1, *o2, *o3, *o4, *o5, *o6, *o7, *o8, *o9, *o10;
	Operator *o11, *o12, *o13, *o14, *o15, *o16, *o17, *o18, *o19, *o20;
	Operator *o21, *o22, *o23, *o24;


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
	
/* selection3 */

	ColumnRefNode cn3;
	cn3.tableID = 6;
	cn3.attriID = 4;
	ColumnRefNode cn5;
	cn5.tableID = 3;
	cn5.attriID = 4;
	AxprNode an5 = AxprNode(EQ, &cn3, &cn5);


	
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

/* Projection4 */

	OPERATION_NODE pro4[3];
	pro4[0].tableID = 2;
	pro4[0].attributeID = 2;
	pro4[1].tableID = 6;
	pro4[1].attributeID = 1;
	pro4[2].tableID =6;
	pro4[2].attributeID = 4;

/* Projection5 */

	OPERATION_NODE pro5[3];
	pro5[0].tableID = 2;
	pro5[0].attributeID = 2;
	pro5[1].tableID = 6;
	pro5[1].attributeID = 4;
	pro5[2].tableID = 7;
	pro5[2].attributeID = 1;

/* Projection6 */

	OPERATION_NODE pro6[5];
	pro6[0].tableID = 2;
	pro6[0].attributeID = 2;
	pro6[1].tableID = 6;
	pro6[1].attributeID = 4;
	pro6[2].tableID = 8;
	pro6[2].attributeID = 3;
	pro6[3].tableID = 8;
	pro6[3].attributeID = 6;
	pro6[4].tableID = 8;
	pro6[4].attributeID = 7;
	
	
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

/* index position */
	
	OPERATION_NODE pro10[1];
	pro10[0].tableID = 7;
	pro10[0].attributeID = 1;
	
	OPERATION_NODE pro11[1];
	pro11[0].tableID = 8;
	pro11[0].attributeID = 3;
	
	OPERATION_NODE pro12[1];
	pro12[0].tableID = 1;
	pro12[0].attributeID = 1;
	
	OPERATION_NODE pro13[1];
	pro13[0].tableID = 2;
	pro13[0].attributeID = 1;
	
	OPERATION_NODE pro14[1];
	pro14[0].tableID = 6;
	pro14[0].attributeID = 1;
/* Join1 */
	OPERATION_NODE pn1[2];
	pn1[0].tableID = 2;
	pn1[0].attributeID = 1;
	pn1[1].tableID = 6;
	pn1[1].attributeID = 4;

	
	JOIN_OPERATION_NODE jpn1[1];
	jpn1[0].rightNode = pn1[0];
	jpn1[0].leftNode = pn1[1];

/* Join2 */
	OPERATION_NODE pn2[2];
	pn2[0].tableID = 6;
	pn2[0].attributeID = 1;
	pn2[1].tableID = 7;
	pn2[1].attributeID = 2;

	
	JOIN_OPERATION_NODE jpn2[1];
	jpn2[0].rightNode = pn2[0];
	jpn2[0].leftNode = pn2[1];
	
/* Join3 */
	OPERATION_NODE pn3[2];
	pn3[0].tableID = 7;
	pn3[0].attributeID = 1;
	pn3[1].tableID = 8;
	pn3[1].attributeID = 1;

	
	JOIN_OPERATION_NODE jpn3[1];
	jpn3[0].rightNode = pn3[0];
	jpn3[0].leftNode = pn3[1];

/* Join4 */
	OPERATION_NODE pn4[4];
	pn4[0].tableID = 3;
	pn4[0].attributeID = 1;
	pn4[1].tableID = 3;
	pn4[1].attributeID = 4;
	pn4[2].tableID = 8;
	pn4[2].attributeID = 3;
	pn4[3].tableID = 6;
	pn4[3].attributeID = 4;

	
	JOIN_OPERATION_NODE jpn4[2];
	jpn4[0].rightNode = pn4[2];
	jpn4[0].leftNode = pn4[0];
	jpn4[1].rightNode = pn4[3];
	jpn4[1].leftNode = pn4[1];

	
/* exec */
	
	o1 = new ScanDSM(&db_r_2, &attriRec_r[1], 1);
	o2 = new SelectBitOut((Node *)&an1 ,(unsigned int)1);
	o2->setPreOperator(o1);
	o3 = new ScanDSM(&db_r_1, &attriRec_r[0], 1);
	o4 = new BitFilter(o3, o2);
	
	/* ======== Nested Loop Join with Index ============ */

	IndexScan *IS3 = new IndexScan((BDBOpe *)sDB3, attriRec_n, 4);
	o5 = new NestedJoin_Index(IS3, o4, pro12);
	
	/* ======================================================= */
	
	//n_name, n_natonkey
	o6 = new Projection(pro1, 2);
	o6->setPreOperator(o5);

	/* ======== Nested Loop Join with Index ============ */

	IndexScan *IS4 = new IndexScan((BDBOpe *)sDB4, attriRec_c, 8);
	o9 = new NestedJoin_Index(IS4, o6, pro13);
	
	/* ======================================================= */
	//n_name, c_custkey, c_nationkey
	o10 = new Projection(pro4, 3);
	o10->setPreOperator(o9);
	
	/* ======== Nested Loop Join with Index ============ */

	IndexScan *IS5 = new IndexScan((BDBOpe *)sDB5, attriRec_o, 9);
	o11 = new NestedJoin_Index(IS5, o10, pro14);
	
	/* ======================================================= */
	
	o12 = new Selection((Node *)&an4 ,(unsigned int)2);
	o12->setPreOperator(o11);

	o13 = new Projection(pro5, 3);
	o13->setPreOperator(o12);

	/* ======== Nested Loop Join with Index ============ */

	IndexScan *IS = new IndexScan((BDBOpe *)sDB, attriRec_l, 16);
	o14 = new NestedJoin_Index(IS, o13, pro10);
	o15 = new Projection(pro6, 5);
	o15->setPreOperator(o14);
	
	/* ======================================================= */
	
	//l_orderkey, l_extendedprice, l_discount, l_suppkey
	
	o16 = new ScanDSM(&db_s_4, &attriRec_s[3], 1);
	o17 = new ScanDSM(&db_s_1, &attriRec_s[0], 1);
	o18 = new ScanFromJI(o17, o16, &op2);

	o19 = new OneSideHashJoin(o15, o18 , jpn4, 2);


	o20 = new Projection(pro3, 3);
	o20->setPreOperator(o19);
	
	o21 = new GroupBy(group, 1, aggre, 1);
	o21->setPreOperator(o20);

	o22 = new Sort(so1, 1);
	o22->setPreOperator(o21);
	
	o23 = new OutPut(TIME_OUT);

	o23->setPreOperator(o22);
	o23->init(env->getEnv());
	cout << "TEST START Q5" << endl;
	
	cout << setprecision(4);
	cout << setiosflags(ios::fixed); 
	o23->exec();
}
