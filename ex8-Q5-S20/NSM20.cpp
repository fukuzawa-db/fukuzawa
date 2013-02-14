#include<iostream>
#include<cstdlib>
#include<cassert>
#include<string>
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

#include"Node.h"
#include"ArithmeticNode.h"
#include"AxprNode.h"
#include"ValueNode.h"
#include"ColumnRefNode.h"

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
//using namespace std;

int main(){
	chdir(QUERY_DATA_PATH);
	EnvDB *env = new EnvDB();
	env->open();
	
	BDBOpe db_r(env->getEnv(), "REGION20.row");
	BDBOpe db_n(env->getEnv(), "NATION20.row");
	BDBOpe db_c(env->getEnv(), "CUSTOMER20.row");
	BDBOpe db_o(env->getEnv(), "ORDERS20.row");
	BDBOpe db_l(env->getEnv(), "LINEITEM20.row");
	BDBOpe db_s(env->getEnv(), "SUPPLIER20.row");

	Operator *o1, *o2, *o3, *o4, *o5, *o6, *o7, *o8, *o9, *o10;
	Operator *o11, *o12, *o13, *o14, *o15, *o16, *o17, *o18, *o19, *o20;
	Operator *o21, *o22, *o23, *o24;
	
	db_r.open();
	db_n.open();
	db_c.open();
	db_o.open();
	db_l.open();
	db_s.open();


	TABLE_REC tableRec_r;
	TABLE_REC tableRec_n;
	TABLE_REC tableRec_c;
	TABLE_REC tableRec_o;
	TABLE_REC tableRec_l;
	TABLE_REC tableRec_s;

	
/* set table info */
	tableRec_r.tableID = 10;
	tableRec_r.attriNum = 3;
	
	tableRec_n.tableID = 11;
	tableRec_n.attriNum = 4;
	
	tableRec_c.tableID = 15;
	tableRec_c.attriNum = 8;

	tableRec_o.tableID = 16;
	tableRec_o.attriNum = 9;
	
	tableRec_l.tableID = 17;
	tableRec_l.attriNum = 16;
	
	tableRec_s.tableID = 12;
	tableRec_s.attriNum = 7;

/* aet attriRec */
	ATTRIBUTE_REC attriRec_r[tableRec_r.attriNum];
	ATTRIBUTE_REC attriRec_n[tableRec_n.attriNum];
	ATTRIBUTE_REC attriRec_c[tableRec_c.attriNum];
	ATTRIBUTE_REC attriRec_o[tableRec_o.attriNum];
	ATTRIBUTE_REC attriRec_l[tableRec_l.attriNum];
	ATTRIBUTE_REC attriRec_s[tableRec_s.attriNum];

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
	cn1.tableID = 10;
	cn1.attriID = 2;
	AxprNode an1 = AxprNode(EQ, &cn1, &vn1);
	

/* selection2 */

	DatePosVal pv2(1,(unsigned char *)"1994-01-01");
	DatePosVal pv3(1,(unsigned char *)"1995-01-01");
	

	ValueNode vn2 = ValueNode(&pv2);
	ValueNode vn3 = ValueNode(&pv3);
	ColumnRefNode cn2;
	cn2.tableID = 16;
	cn2.attriID = 5;
	AxprNode an2 = AxprNode(GE, &cn2, &vn2);
	AxprNode an3 = AxprNode(LT, &cn2, &vn3);
	AxprNode an4 = AxprNode(AND, &an2, &an3);
	
	
/* GROUP */
	IntPosVal pv5(1, 1);
	ValueNode vn5 = ValueNode(&pv5);
	ColumnRefNode cn4[2];
	cn4[0].tableID = 17;
	cn4[0].attriID = 6;
	cn4[1].tableID = 17;
	cn4[1].attriID = 7;
	ArithmeticNode arith1(SUB, &vn5, &cn4[1]);
	ArithmeticNode arith2(MUL, &cn4[0], &arith1);
	
	Aggregation *aggre[1];
	aggre[0] = new Sum(&arith2, 2);
	
	
	OPERATION_NODE group[1];
	group[0].tableID = 11;
	group[0].attributeID = 2;




/* Join1 */

	OPERATION_NODE pn1[2];
	pn1[0].tableID = 10;
	pn1[0].attributeID = 1;
	pn1[1].tableID = 11;
	pn1[1].attributeID = 3;
	

	JOIN_OPERATION_NODE jpn1[1];
	jpn1[0].rightNode = pn1[0];
	jpn1[0].leftNode = pn1[1];
	
/* Join2 */
	OPERATION_NODE pn2[2];
	pn2[0].tableID = 11;
	pn2[0].attributeID = 1;
	pn2[1].tableID = 15;
	pn2[1].attributeID = 4;


	
	JOIN_OPERATION_NODE jpn2[1];
	jpn2[0].rightNode = pn2[0];
	jpn2[0].leftNode = pn2[1];


/* Join3 */
	OPERATION_NODE pn3[2];
	pn3[0].tableID = 15;
	pn3[0].attributeID = 1;
	pn3[1].tableID = 16;
	pn3[1].attributeID = 2;

	
	JOIN_OPERATION_NODE jpn3[1];
	jpn3[0].rightNode = pn3[0];
	jpn3[0].leftNode = pn3[1];

/* Join4 */
	OPERATION_NODE pn4[2];
	pn4[0].tableID = 16;
	pn4[0].attributeID = 1;
	pn4[1].tableID = 17;
	pn4[1].attributeID = 1;

	
	JOIN_OPERATION_NODE jpn4[1];
	jpn4[0].rightNode = pn4[0];
	jpn4[0].leftNode = pn4[1];

/* Join5 */
	OPERATION_NODE pn5[4];
	pn5[0].tableID = 12;
	pn5[0].attributeID = 1;
	pn5[1].tableID = 12;
	pn5[1].attributeID = 4;
	pn5[2].tableID = 17;
	pn5[2].attributeID = 3;
	pn5[3].tableID = 15;
	pn5[3].attributeID = 4;

	
	JOIN_OPERATION_NODE jpn5[2];
	jpn5[0].rightNode = pn5[0];
	jpn5[0].leftNode = pn5[2];
	jpn5[1].rightNode = pn5[1];
	jpn5[1].leftNode = pn5[3];




/* Projection1 */

	OPERATION_NODE pro1[1];
	pro1[0].tableID = 10;
	pro1[0].attributeID = 1;

/* Projection2 */

	OPERATION_NODE pro2[2];
	pro2[0].tableID = 11;
	pro2[0].attributeID = 1;
	pro2[1].tableID = 11;
	pro2[1].attributeID = 2;

/* Projection3 */

	OPERATION_NODE pro3[3];
	pro3[0].tableID = 12;
	pro3[0].attributeID = 1;
	pro3[1].tableID = 12;
	pro3[1].attributeID = 4;
	pro3[2].tableID = 11;
	pro3[2].attributeID = 2;
	
/* Projection4 */

	OPERATION_NODE pro4[5];
	pro4[0].tableID = 17;
	pro4[0].attributeID = 1;
	pro4[1].tableID = 17;
	pro4[1].attributeID = 6;
	pro4[2].tableID = 17;
	pro4[2].attributeID = 7;
	pro4[3].tableID = 12;
	pro4[3].attributeID = 4;
	pro4[4].tableID = 11;
	pro4[4].attributeID = 2;

/* Projection5 */
	
	OPERATION_NODE pro5[2];
	pro5[0].tableID = 16;
	pro5[0].attributeID = 1;
	pro5[1].tableID = 16;
	pro5[1].attributeID = 2;

/* Projection6 */
	
	OPERATION_NODE pro6[2];
	pro6[0].tableID = 15;
	pro6[0].attributeID = 1;
	pro6[1].tableID = 15;
	pro6[1].attributeID = 4;

/* Projection7 */
	
	OPERATION_NODE pro7[3];
	pro7[0].tableID = 11;
	pro7[0].attributeID = 2;
	pro7[1].tableID = 17;
	pro7[1].attributeID = 6;
	pro7[2].tableID = 17;
	pro7[2].attributeID = 7;

/* Projection8 */
	
	OPERATION_NODE pro8[4];
	pro8[0].tableID = 17;
	pro8[0].attributeID = 1;
	pro8[1].tableID = 17;
	pro8[1].attributeID = 3;
	pro8[2].tableID = 17;
	pro8[2].attributeID = 6;
	pro8[3].tableID = 17;
	pro8[3].attributeID = 7;

/* Projection9 */
	
	OPERATION_NODE pro9[2];
	pro9[0].tableID = 12;
	pro9[0].attributeID = 1;
	pro9[1].tableID = 12;
	pro9[1].attributeID = 4;


/* Sort 1 */
	OPERATION_NODE so1[1];
	so1[0].tableID = 0;
	so1[0].attributeID = 0;
	so1[0].position = 1;
	so1[0].option = 1;


	o1 = new Scan(&db_r, attriRec_r, 3);
	o2 = new Selection((Node *)&an1 ,(unsigned int)1);
	o2->setPreOperator(o1);
	o3 = new Projection(pro1, 1);
	o3->setPreOperator(o2);
	
	o4 = new Scan(&db_n, attriRec_n, 4);
	o5 = new OneSideHashJoin(o3, o4 , jpn1, 1);
	//n_nationkey, n_name
	o6 = new Projection(pro2, 2);
	o6->setPreOperator(o5);
	
	o7 = new Scan(&db_c, attriRec_c, 8);
	//c_custkey, c_nationkey 
	o8 = new Projection(pro6, 2);
	o8->setPreOperator(o7);
	//n_nationkey, n_name
	//n_nationkey, n_name, c_custkey, c_nationkey 
	o9 = new OneSideHashJoin(o6, o8 , jpn2, 1);
	
	o10 = new Scan(&db_o, attriRec_o, 9);
	
	o11 = new Selection((Node *)&an4 ,(unsigned int)2);
	o11->setPreOperator(o10);
	//o_orderkey, o_custkey
	o12 = new Projection(pro5, 2);
	o12->setPreOperator(o11);
	
	//n_nationkey, n_name, c_custkey, c_nationkey, o_orderkey, o_custkey
	o13 = new OneSideHashJoin(o9, o12 , jpn3, 1);
	
	
	o14 = new Scan(&db_l, attriRec_l, 16);
	o15 = new Projection(pro8, 4);
	o15->setPreOperator(o14);
	
	
	o16 = new OneSideHashJoin(o13, o15 , jpn4, 1);
	
	
	o17 = new Scan(&db_s, attriRec_s, 7);
	o18 = new Projection(pro9, 2);
	o18->setPreOperator(o17);

	o19 = new OneSideHashJoin(o18, o16 , jpn5, 2);

	
	//n_name, l_extendedprice, l_discount
	o20 = new Projection(pro7, 3);
	o20->setPreOperator(o19);
	

	o21 = new GroupBy(group, 1, aggre, 1);
	o21->setPreOperator(o20);

	o22 = new Sort(so1, 1);
	o22->setPreOperator(o21);


	o23 = new OutPut(TIME_OUT);

	o23->setPreOperator(o22);
	o23->init(env->getEnv());
	cout << "TEST START Q5 NSM20_2" << endl;
	
	cout << setprecision(2);
	cout << setiosflags(ios::fixed); 
	o23->exec();
}
	
