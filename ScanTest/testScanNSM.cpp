#include<iostream>
#include<string>
#include<cstdlib>
#include<cassert>
#include<db_cxx.h>
#include <iomanip>

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


#define DB		("LINEITEM20.row")
#define DB_tableID	(17)
#define DB_attriNum	(16)


int main(){
	chdir(QUERY_DATA_PATH);
	EnvDB *env = new EnvDB();
	env->open();
	
	BDBOpe db(env->getEnv(), DB);
	Operator *o1, *o2;
	
	db.open();
	TABLE_REC tableRec;
	
	tableRec.tableID = DB_tableID;
	tableRec.attriNum = DB_attriNum;
	
	ATTRIBUTE_REC attriRec[tableRec.attriNum];
	AttributeManager AM(env->getEnv());
	AM.getForTableID(tableRec, attriRec);
	
	o1 = new Scan(&db, attriRec, DB_attriNum);
	o2 = new OutPut(STD_OUT);

	o2->setPreOperator(o1);
	o2->init(env->getEnv());
	o2->exec();
}
