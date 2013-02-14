#include<iostream>
#include<cstdlib>
#include<cassert>
#include<string>
#include<iomanip>
#include<db_cxx.h>
#include<vector>



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


#include"ScanDSM.h"
#include"ScanRLE.h"
#include"SelectBitOut.h"
#include"BitFilter.h"
#include"BitSort.h"

#include"ScanJoinIndex.h"
#include"JoinIndex_OneHash.h"
#include"ScanFromJI.h"
#include"ScanFromPos.h"
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


#define DB1		("9.1.DSM")
#define DB2		("9.2.DSM")
#define DB3		("9.3.DSM")
#define DB_tableID	(9)
#define DB_attriNum	(5)


int main(){
	chdir(QUERY_DATA_PATH);
	EnvDB *env = new EnvDB();
	env->open();
	
	BDBOpe db1(env->getEnv(), DB1);
	BDBOpe db2(env->getEnv(), DB2);
	BDBOpe db3(env->getEnv(), DB3);
	Operator *o1, *o2, *o3, *o4, *o5, *o6;
	
	db1.open();
	db2.open();
	db3.open();
	TABLE_REC tableRec;
	
	tableRec.tableID = DB_tableID;
	tableRec.attriNum = DB_attriNum;
	
	ATTRIBUTE_REC attriRec[tableRec.attriNum];
	AttributeManager AM(env->getEnv());
	AM.getForTableID(tableRec, attriRec);

/*    JoinC     */
	vector <Operator *> vo;
	
	OPERATION_NODE op1;
	op1.tableID = 9;
	op1.attributeID = 1;
/* ===================== */
/* Selection Status */
	IntPosVal pv1(1,0);

	ValueNode vn1 = ValueNode(&pv1);
	ColumnRefNode cn1;
	cn1.tableID = 9;
	cn1.attriID = 1;
	AxprNode an1 = AxprNode(EQ, &cn1, &vn1);
/* ===================== */

	o1 = new ScanDSM(&db1, &attriRec[0], 1);
	
	o2 = new Selection((Node *)&an1 ,(unsigned int)1);
	o2->setPreOperator(o1);
	o3 = new ScanDSM(&db2, &attriRec[1], 1);
	o4 = new ScanDSM(&db3, &attriRec[2], 1);
	vo.push_back(o3);
	vo.push_back(o4);
	
	o5 = new JoinC(o2, &op1, vo);
	
	o6 = new OutPut(TIME_OUT);

	o6->setPreOperator(o5);
	o6->init(env->getEnv());
	o6->exec();
}
	
