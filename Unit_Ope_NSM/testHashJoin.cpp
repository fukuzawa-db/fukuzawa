#include<iostream>
#include<cstdlib>
#include<cassert>
#include<string>
#include<iomanip>
#include<db_cxx.h>


#include"CommonDataDef.h"
#include"PosVal.h"
#include"AttributeManager.h"
#include"EnvDB.h"
#include"BDBOpe.h"
#include"InMemDB.h"

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

#include"Scan_U.h"


#define DB1	("ORDERS20.row")
#define DB1_tableID	(15)
#define DB1_attriNum	(9)

#define DB2	("LINEITEM20.row")
#define DB2_tableID	(16)
#define DB2_attriNum	(16)


int main(){
	chdir(QUERY_DATA_PATH);
	EnvDB *env = new EnvDB();
	env->open();
	
	BDBOpe db1(env->getEnv(), DB1);
	BDBOpe db2(env->getEnv(), DB2);
	Operator *o1, *o2, *o3, *o4;
	
	db1.open();
	db2.open();
	TABLE_REC tableRec1, tableRec2;
	
	tableRec1.tableID = DB1_tableID;
	tableRec1.attriNum = DB1_attriNum;
	tableRec2.tableID = DB2_tableID;
	tableRec2.attriNum = DB2_attriNum;
	
	ATTRIBUTE_REC attriRec1[tableRec1.attriNum];
	ATTRIBUTE_REC attriRec2[tableRec2.attriNum];
	AttributeManager AM(env->getEnv());
	
	AM.getForTableID(tableRec1, attriRec1);
	AM.getForTableID(tableRec2, attriRec2);
	
/* JOin target */
	OPERATION_NODE pn[2];
	pn[0].tableID = 15;
	pn[0].attributeID = 1;
	pn[1].tableID = 16;
	pn[1].attributeID = 1;

	
	JOIN_OPERATION_NODE jpn[1];
	jpn[0].rightNode = pn[0];
	jpn[0].leftNode = pn[1];
/* ============ */	

	o1 = new Scan_U(&db1, attriRec1, DB1_attriNum);
	((Scan_U *)o1)->storeData();
	o2 = new Scan_U(&db2, attriRec2, DB2_attriNum);
	((Scan_U *)o2)->storeData();
	
	o3 = new HashJoin(o1, o2 , jpn, 1);
	o4 = new OutPut(TIME_OUT);

	o4->setPreOperator(o3);
	o4->init(env->getEnv());
	o4->exec();
}
	
