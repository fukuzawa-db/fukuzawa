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
	Operator *o1, *o2, *o3, *o4, *o5;
	
	db1.open();
	db2.open();
	TABLE_REC tableRec;
	
	tableRec.tableID = DB_tableID;
	tableRec.attriNum = DB_attriNum;
	
	ATTRIBUTE_REC attriRec[tableRec.attriNum];
	AttributeManager AM(env->getEnv());
	AM.getForTableID(tableRec, attriRec);
	
/* Selection Status */
	IntPosVal pv1(1,39);

	ValueNode vn1 = ValueNode(&pv1);
	ColumnRefNode cn1;
	cn1.tableID = 16;
	cn1.attriID = 1;
	AxprNode an1 = AxprNode(EQ, &cn1, &vn1);
/* ===================== */

	o1 = new ScanDSM_U(&db1, &attriRec[0], 1, 10000000, 100);
	((ScanDSM_U *)o1)->storeData();
	o2 = new SelectBitOut_U((Node *)&an1 ,(unsigned int)1);
	o2->setPreOperator(o1);
	((SelectBitOut_U *)o2)->storeData();
	o3 = new ScanDSM_U(&db2, &attriRec[1], 1, 10000000, 100);
	((ScanDSM_U *)o3)->storeData();
	o4 = new BitFilter(o3, o2);
	
	
	o5 = new OutPut(TIME_OUT);

	o5->setPreOperator(o4);
	o5->init(env->getEnv());
	
	o5->exec();
}
	
