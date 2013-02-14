/* group by test */



#include<iostream>
#include<cstdlib>
#include<cassert>
#include<string>

#include"CommonDataDef.h"
#include"PosVal.h"
#include"AttributeManager.h"
#include"BDBOpe.h"
#include"Operator.h"
#include"Scan.h"
#include"Selection.h"
#include"Projection.h"
#include"Hash.h"
#include"HashJoin.h"
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


int 
main()
{
	chdir("../RunData");
	BDBOpe db("NATION.row");
	Operator *o1, *o2, *o3;
	db.open();

	TABLE_REC tableRec;

	tableRec.tableID = 2;
	tableRec.attriNum = 4;

	ATTRIBUTE_REC attriRec[tableRec.attriNum];

	AttributeManager AM;
	AM.getForTableID(tableRec, attriRec);
	for(int i=0 ; i < (int)tableRec.attriNum ; i++){
		cout << attriRec[i].attributeName << endl;
	}


	ColumnRefNode cn;
	cn.tableID = 2;
	cn.attriID = 1;

	
	OPERATION_NODE pn[1];
	pn[0].tableID = 2;
	pn[0].attributeID = 3;


	Aggregation *ap[5];
	ap[0] = new Count(&cn, 1);
	ap[1] = new Avg(&cn, 1);
	ap[2] = new Sum(&cn, 1 , LONG);
	ap[3] = new Max(&cn, 1, INT);
	ap[4] = new Min(&cn, 1, INT);

	o1 = new Scan(&db, attriRec, 4);
	cout << "OK new o1" << endl;
	o2 = new OutPut(STD_OUT);
	cout << "OK new o2" << endl;
	o3 = new GroupBy(pn, 1, ap, 5);
	cout << "OK new o3" << endl;

	o2->setPreOperator(o3);
	o3->setPreOperator(o1);
	o2->init();
	cout << "TEST START" << endl;
	o2->exec();

}
