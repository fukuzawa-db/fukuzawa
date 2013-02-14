#include<iostream>
#include<cstdlib>
#include<cassert>
#include<string>
#include<iomanip>


#include"CommonDataDef.h"
#include"PosVal.h"
#include"AttributeManager.h"
#include"EnvDB.h"
#include"BDBOpe.h"

#include"Operator.h"
#include"Scan.h"
#include"KeyIndex.h"
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
#include"AggreOut.h"


#include"ScanDSM.h"
#include"ScanRLE.h"
#include"SelectBitOut.h"
#include"BitFilter.h"
#include"BitSort.h"

#include"ScanJoinIndex.h"
#include"JoinIndex_OneHash.h"
#include"ScanFromJI.h"
#include"ScanFromJI_OneHash.h"
#include"JoinC.h"

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
using namespace std;

int main(){
	chdir(QUERY_DATA_PATH);
	EnvDB *env = new EnvDB();
	env->open();	
	
	BDBOpe db_l(env->getEnv(), "LINEITEM20.row");
	BDBOpe db_index(env->getEnv(), "28.1.DSM");
	Operator *o1, *o2, *o3, *o4;
	
	db_l.open();
	db_index.open();
	
	TABLE_REC tableRec_l, tableRec_index;
	tableRec_l.tableID = 16;
	tableRec_l.attriNum = 16;
	tableRec_index.tableID = 28;
	tableRec_index.attriNum = 1;
	
	ATTRIBUTE_REC attriRec_l[tableRec_l.attriNum];
	ATTRIBUTE_REC attriRec_index[tableRec_index.attriNum];
	AttributeManager AM(env->getEnv());
	
	AM.getForTableID(tableRec_l, attriRec_l);
	AM.getForTableID(tableRec_index, attriRec_index);
	
	
/* selection1 */
/*
	DatePosVal pv1(1,(unsigned char *)"1994-01-01");

	ValueNode vn1 = ValueNode(&pv1);
	ColumnRefNode cn1;
	cn1.tableID = 16;
	cn1.attriID = 11;
	AxprNode an1 = AxprNode(GE, &cn1, &vn1);
*/
/* selection2 */
/*
	DatePosVal pv2(1,(unsigned char *)"1995-01-01");

	ValueNode vn2 = ValueNode(&pv2);
	ColumnRefNode cn2;
	cn2.tableID = 16;
	cn2.attriID = 11;
	AxprNode an2 = AxprNode(LT, &cn2, &vn2);
*/	
/* selection3 */
/*
	FloatPosVal pv3(1, 0.06-0.01);
	FloatPosVal pv4(1, 0.06+0.01);
	

	ValueNode vn3 = ValueNode(&pv3);
	ValueNode vn4 = ValueNode(&pv4);
	ColumnRefNode cn3;
	cn3.tableID = 16;
	cn3.attriID = 7;
	AxprNode an3 = AxprNode(GE, &cn3, &vn3);
	AxprNode an4 = AxprNode(LE, &cn3, &vn4);
	AxprNode an5 = AxprNode(AND, &an3, &an4);
*/	
/* selection4 */
/*
	FloatPosVal pv5(1, 24);

	ValueNode vn5 = ValueNode(&pv5);
	ColumnRefNode cn4;
	cn4.tableID =16;
	cn4.attriID = 5;
	AxprNode an6 = AxprNode(LT, &cn4, &vn5);
*/
/* selection */
/*
	AxprNode an7 = AxprNode(AND, &an1, &an2);
	AxprNode an8 = AxprNode(AND, &an5, &an6);
	AxprNode an9 = AxprNode(AND, &an7, &an8);
*/	
/* AGGREGATION */
	ColumnRefNode cn5[2];
	cn5[0].tableID = 16;
	cn5[0].attriID = 6;
	cn5[1].tableID = 16;
	cn5[1].attriID = 7;
	ArithmeticNode arith1(MUL, &cn5[0], &cn5[1]);
	
	Aggregation *aggre[1];
	aggre[0] = new Sum(&arith1, 2);
	



	

	o1 = new ScanDSM(&db_index, attriRec_index, 1);
	o2 = new KeyIndex(&db_l, o1, attriRec_l, 16);
	
	o3 = new AggreOut(aggre, 1);
	o3->setPreOperator(o2);
//	cout << "OK new o3" << endl;
	
	o4 = new OutPut(TIME_OUT);
//	cout << "OK new o4" << endl;

	o4->setPreOperator(o3);
	o4->init(env->getEnv());
	//cout << "TEST START Q6 NSM20" << endl;
	
	cout << setprecision(6);
	cout << setiosflags(ios::fixed); 
	o4->exec();
}
