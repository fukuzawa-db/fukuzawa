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
	
/* Projection Status */
	int pNum = 12;
	OPERATION_NODE pro[pNum];
	pro[0].tableID = 16;
	pro[0].attributeID = 1;
	pro[1].tableID = 16;
	pro[1].attributeID = 2;

	pro[2].tableID = 16;
	pro[2].attributeID = 3;
	pro[3].tableID = 16;
	pro[3].attributeID = 4;
	
	pro[4].tableID = 16;
	pro[4].attributeID = 5;
	pro[5].tableID = 16;
	pro[5].attributeID = 6;
	
	pro[6].tableID = 16;
	pro[6].attributeID = 7;
	pro[7].tableID = 16;
	pro[7].attributeID = 8;
	
	pro[8].tableID = 16;
	pro[8].attributeID = 9;
	pro[9].tableID = 16;
	pro[9].attributeID = 10;
	pro[10].tableID = 16;
	pro[10].attributeID = 11;
	pro[11].tableID = 16;
	pro[11].attributeID = 12;
	/*
	pro[12].tableID = 16;
	pro[12].attributeID = 13;
	pro[13].tableID = 16;
	pro[13].attributeID = 14;
	pro[14].tableID = 16;
	pro[14].attributeID = 15;
	pro[15].tableID = 16;
	pro[15].attributeID = 16;
*/
/* ===================== */

	o1 = new Scan_U(&db, attriRec, DB_attriNum, 1000000, 20);
	((Scan_U *)o1)->storeData();
	o2 = new Projection(pro, pNum);
	o2->setPreOperator(o1);
	o3 = new OutPut(TIME_OUT);

	o3->setPreOperator(o2);
	o3->init(env->getEnv());
	o3->exec();
}
	
