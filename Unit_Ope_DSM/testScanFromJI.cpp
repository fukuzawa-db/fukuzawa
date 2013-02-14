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


#define DB1	("16.1.DSM")
#define DB2	("16.2.DSM")
#define DB_tableID	(16)
#define DB_attriNum	(16)


int main(){
	chdir(QUERY_DATA_PATH);
	EnvDB *env = new EnvDB();
	env->open();
	
	BDBOpe db1(env->getEnv(), DB1);
	BDBOpe db2(env->getEnv(), DB2);
	Operator *o1, *o2, *o3, *o4;
	
	db1.open();
	db2.open();
	TABLE_REC tableRec;
	
	tableRec.tableID = DB_tableID;
	tableRec.attriNum = DB_attriNum;
	
	ATTRIBUTE_REC attriRec[tableRec.attriNum];
	AttributeManager AM(env->getEnv());
	AM.getForTableID(tableRec, attriRec);
	
/* Selection Status */

	OPERATION_NODE op1;
	op1.tableID = 16;
	op1.attributeID = 2;
	
/* ===================== */

	o1 = new ScanDSM_U(&db1, &attriRec[0], 1, 10000000, 50);
	((ScanDSM_U *)o1)->storeData();
	o2 = new ScanDSM_U(&db2, &attriRec[1], 1, 10000000, 50);
	((ScanDSM_U *)o2)->storeData();
	
	o3 = new  ScanFromJI(o1, o2, &op1);	
	
	o4 = new OutPut(TIME_OUT);

	o4->setPreOperator(o3);
	o4->init(env->getEnv());
	
	o4->exec();
}
	
