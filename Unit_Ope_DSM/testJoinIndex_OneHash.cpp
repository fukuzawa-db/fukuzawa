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

#include"ScanDSM.h"
#include"ScanRLE.h"
#include"SelectBitOut.h"
#include"BitFilter.h"
#include"BitSort.h"

#include"ScanJoinIndex.h"
#include"JoinIndex_OneHash.h"
#include"ScanFromJI.h"
#include"ScanFromJI_OneHash.h"

#include"ScanDSM_U.h"
#include"SelectBitOut_U.h"


#define DB1	("15.1.DSM")
#define DB2	("16.1.DSM")
#define DB1_tableID	(15)
#define DB1_attriNum	(9)
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
	
/* Selection Status */
	OPERATION_NODE jop1, jop2;
	jop1.tableID = 15;
	jop1.attributeID = 1;
	jop2.tableID = 16;
	jop2.attributeID = 1;
	
	JOIN_OPERATION_NODE jon1;
	jon1.rightNode = jop1;
	jon1.leftNode = jop2;
/* ===================== */

	o1 = new ScanDSM_U(&db1, &attriRec1[0], 1);
	((ScanDSM_U *)o1)->storeData();
	o2 = new ScanDSM_U(&db2, &attriRec2[0], 1);
	((ScanDSM_U *)o2)->storeData();
	
	o3 = new  JoinIndex_OneHash(o1, o2, &jon1);	
	
	o4 = new OutPut(TIME_OUT);

	o4->setPreOperator(o3);
	o4->init(env->getEnv());
	
	o4->exec();
}
	
