#include<iostream>
#include<cstdlib>
#include<cassert>
#include<string>

#include"CommonDataDef.h"
#include"PosVal.h"
#include"AttributeManager.h"
#include"Operator.h"
#include"Scan.h"
#include"Selection.h"
#include"Projection.h"
#include"Sort.h"
#include"OutPut.h"
#include"Node.h"
#include"AxprNode.h"
#include"ValueNode.h"
#include"ColumnRefNode.h"
#include"IntPosVal.h"
#include"LongPosVal.h"
#include"FloatPosVal.h"
#include"DoublePosVal.h"
#include"FixStrPosVal.h"
#include"VarStrPosVal.h"
#include"DatePosVal.h"


int main(){
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
/*
	IntPosVal pv1;
	int i = 5;
	pv1.set(1, (unsigned char*)&i);

	ValueNode vn = ValueNode(&pv1);
	ColumnRefNode cn;
	cn.tableID = 2;
	cn.attriID = 1;
	AxprNode an = AxprNode(EQ, &cn, &vn);
*/
	OPERATION_NODE pn[2];
	pn[0].tableID = 2;
	pn[0].attributeID = 3;
	pn[0].option = 1;
	pn[1].tableID = 2;
	pn[1].attributeID = 1;
	pn[1].option = 0;
	

	o1 = new Scan(&db, attriRec, 4);
	cout << "OK new o1" << endl;
	o2 = new OutPut(STD_OUT);
	cout << "OK new o2" << endl;
	//o3 = new Sort(pn ,(unsigned int )sizeof(pn)/sizeof(pn[0]));
	o3 = new Sort(pn ,2);
	cout << "OK new o3" << endl;

	o2->setPreOperator(o3);
	o3->setPreOperator(o1);
	o2->init();
	cout << "TEST START" << endl;
	o2->exec();

}
	
