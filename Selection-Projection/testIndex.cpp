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
#include"SecondDB.h"
#include"InMemDB.h"

#include"Operator.h"
#include"Scan.h"
#include"ScanHash.h"
#include"IndexScan.h"
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


#define DB		("test.row")
#define DB_tableID	(9)
#define DB_attriNum	(5)

#define DB_Index	("9.1.secondary")

int main(){
	chdir(QUERY_DATA_PATH);
	EnvDB *env = new EnvDB();
	env->open();
	
	BDBOpe db(env->getEnv(), DB);
	SecondDB *sDB;
	int (*pf)(Db *sdbp, const Dbt*pkey, const Dbt *pdata, Dbt *skey);
	pf = T_1_secondary;
	sDB = new SecondDB(env->getEnv(), DB_Index);
	sDB->setNumCmp();

	db.open();
	sDB->open(0);
	db.associate(sDB->getDb(), pf);
	sDB->openCursor();
	
	
	Operator *o1, *o2;
	TABLE_REC tableRec;
	
	tableRec.tableID = DB_tableID;
	tableRec.attriNum = DB_attriNum;
	
	ATTRIBUTE_REC attriRec[tableRec.attriNum];
	AttributeManager AM(env->getEnv());
	AM.getForTableID(tableRec, attriRec);
	
/* Selection Status */
	IntPosVal pv1(1,0);

//	ValueNode vn1 = ValueNode(&pv1);
//	ColumnRefNode cn1;
//	cn1.tableID = 21;
//	cn1.attriID = 1;
//	AxprNode an1 = AxprNode(EQ, &cn1, &vn1);
/* ===================== */
	
	OPERATION_NODE pro1[2];
	pro1[0].tableID = 9;
	pro1[0].attributeID = 1;
	pro1[1].tableID = 9;
	pro1[1].attributeID = 2;
	pro1[2].tableID = 9;
	pro1[2].attributeID = 3;


	IndexScan *IS = new IndexScan((BDBOpe *)sDB, attriRec, DB_attriNum);
	IS->keySet(&pv1);
	o1 = new Projection(pro1, 3);
	o1->setPreOperator((Operator *)IS);
	o2 = new OutPut(TIME_OUT);
	

	o2->setPreOperator(o1);
	o2->init(env->getEnv());
	o2->exec();
}
	
