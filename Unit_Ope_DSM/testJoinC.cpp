#include<iostream>
#include<string>
#include<cstdlib>
#include<cassert>
#include<db_cxx.h>
#include <iomanip>
#include<vector>

#include"CommonDataDef.h"
#include"PosVal.h"
#include"AttributeManager.h"
#include"EnvDB.h"


#include"Operator.h"
#include"OutPut.h"
#include"Projection.h"
#include"Selection.h"
#include"Extract.h"
#include"GroupBy.h"
#include"Sort.h"

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


#define DB1	("16.1.DSM")
#define DB2	("16.2.DSM")
#define DB3	("16.3.DSM")
#define DB4	("16.4.DSM")
#define DB5	("16.5.DSM")
#define DB6	("16.6.DSM")
#define DB7	("16.7.DSM")
#define DB8	("16.8.DSM")
#define DB9	("16.9.DSM")
#define DB10	("16.10.DSM")
#define DB11	("16.11.DSM")
#define DB12	("16.12.DSM")
#define DB13	("16.13.DSM")
#define DB14	("16.14.DSM")
#define DB15	("16.15.DSM")
#define DB16	("16.16.DSM")
#define DB_tableID	(16)
#define DB_attriNum	(16)


int main(){
	chdir(QUERY_DATA_PATH);
	EnvDB *env = new EnvDB();
	env->open();
	vector <Operator *> vo;
	
	BDBOpe db1(env->getEnv(), DB1);
	BDBOpe db2(env->getEnv(), DB2);
	BDBOpe db3(env->getEnv(), DB3);
	BDBOpe db4(env->getEnv(), DB4);
	BDBOpe db5(env->getEnv(), DB5);
	BDBOpe db6(env->getEnv(), DB6);
	BDBOpe db7(env->getEnv(), DB7);
	BDBOpe db8(env->getEnv(), DB8);
	BDBOpe db9(env->getEnv(), DB9);
	BDBOpe db10(env->getEnv(), DB10);
	BDBOpe db11(env->getEnv(), DB11);
	BDBOpe db12(env->getEnv(), DB12);
	BDBOpe db13(env->getEnv(), DB13);
	BDBOpe db14(env->getEnv(), DB14);
	BDBOpe db15(env->getEnv(), DB15);
	BDBOpe db16(env->getEnv(), DB16);
	Operator *o1, *o2, *o3, *o4, *o5, *o6, *o7, *o8, *o9, *o10;
	Operator *o11, *o12, *o13, *o14, *o15, *o16, *o17, *o18;
	
	db1.open();
	db2.open();
	db3.open();
	db4.open();
	db5.open();
	db6.open();
	db7.open();
	db8.open();
	db9.open();
	db10.open();
	db11.open();
	db12.open();
	db13.open();
	db14.open();
	db15.open();
	db16.open();
	TABLE_REC tableRec;
	
	tableRec.tableID = DB_tableID;
	tableRec.attriNum = DB_attriNum;
	
	ATTRIBUTE_REC attriRec[tableRec.attriNum];
	AttributeManager AM(env->getEnv());
	AM.getForTableID(tableRec, attriRec);
	
	OPERATION_NODE op1;
	op1.tableID = 16;
	op1.attributeID = 1;
	OPERATION_NODE op2;
	op2.tableID = 16;
	op2.attributeID = 4;
	
	o1 = new ScanDSM(&db1, &attriRec[0], 1);
	o2 = new ScanDSM(&db2, &attriRec[1], 1);
	o3 = new ScanDSM(&db3, &attriRec[2], 1);
	o4 = new ScanDSM(&db4, &attriRec[3], 1);
	o5 = new ScanDSM(&db5, &attriRec[4], 1);
	o6 = new ScanDSM(&db6, &attriRec[5], 1);
	o7 = new ScanDSM(&db7, &attriRec[6], 1);
	o8 = new ScanDSM(&db8, &attriRec[7], 1);
	o9 = new ScanDSM(&db9, &attriRec[8], 1);
	o10 = new ScanDSM(&db10, &attriRec[9], 1);
	o11 = new ScanDSM(&db11, &attriRec[10], 1);
	o12 = new ScanDSM(&db12, &attriRec[11], 1);
	o13 = new ScanDSM(&db13, &attriRec[12], 1);
	o14 = new ScanDSM(&db14, &attriRec[13], 1);
	o15 = new ScanDSM(&db15, &attriRec[14], 1);
	o16 = new ScanDSM(&db16, &attriRec[15], 1);
	
	
	vo.push_back(o2);
	vo.push_back(o3);
	vo.push_back(o4);
	vo.push_back(o5);
	vo.push_back(o6);
	vo.push_back(o7);
	vo.push_back(o8);
	vo.push_back(o9);
	vo.push_back(o10);
	vo.push_back(o11);
	vo.push_back(o12);
	vo.push_back(o13);
	vo.push_back(o14);
	//vo.push_back(o15);
	//vo.push_back(o16);

	o17 = new JoinC(o1, &op1, vo);
	
	
	o18 = new OutPut(TIME_OUT);

	o18->setPreOperator(o17);
	o18->init(env->getEnv());
	o18->exec();
}
	
