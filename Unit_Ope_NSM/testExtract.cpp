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


#define DB		("LINEITEM20.row")
#define DB_tableID	(16)
#define DB_attriNum	(16)


int main(){
	chdir(QUERY_DATA_PATH);
	EnvDB *env = new EnvDB();
	env->open();
	
	BDBOpe db(env->getEnv(), DB);
	Operator *o1, *o2, *o3;
	
	db.open();
	TABLE_REC tableRec;
	
	tableRec.tableID = DB_tableID;
	tableRec.attriNum = DB_attriNum;
	
	ATTRIBUTE_REC attriRec[tableRec.attriNum];
	AttributeManager AM(env->getEnv());
	AM.getForTableID(tableRec, attriRec);
	
/* Extract target */
	OPERATION_NODE ex[1];
	ex[0].tableID = 16;
	ex[0].attributeID = 11;
/* ============ */	

	o1 = new Scan_U(&db, attriRec, DB_attriNum, 1000000, 50);
	((Scan_U *)o1)->storeData();
	o2 = new Extract(ex, true, false, false);
	o2->setPreOperator(o1);
	o3 = new OutPut(TIME_OUT);

	o3->setPreOperator(o2);
	o3->init(env->getEnv());
	o3->exec();
}
	
