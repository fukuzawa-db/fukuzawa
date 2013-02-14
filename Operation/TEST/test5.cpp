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
#include"Sort.h"
#include"NestedJoin.h"
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
	BDBOpe outerDB("NATION.row");
	BDBOpe innerDB("REGION.row");
	Operator *o1, *o2, *o3, *o4;
	outerDB.open();
	innerDB.open();

	TABLE_REC innerTableRec,outerTableRec;

	innerTableRec.tableID = 1;
	innerTableRec.attriNum = 3;
	outerTableRec.tableID = 2;
	outerTableRec.attriNum = 4;

	ATTRIBUTE_REC innerAttriRec[innerTableRec.attriNum];
	ATTRIBUTE_REC outerAttriRec[outerTableRec.attriNum];

	AttributeManager innerAM, outerAM;
	innerAM.getForTableID(innerTableRec, innerAttriRec);
	outerAM.getForTableID(outerTableRec, outerAttriRec);
	

	for(int i=0 ; i < (int)innerTableRec.attriNum ; i++){
		cout << innerAttriRec[i].attributeName << endl;
	}
	for(int i=0 ; i < (int)outerTableRec.attriNum ; i++){
		cout << outerAttriRec[i].attributeName << endl;
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
	pn[0].tableID = 1;
	pn[0].attributeID = 1;
	pn[1].tableID = 2;
	pn[1].attributeID = 3;

	JOIN_OPERATION_NODE jpn[1];
	jpn[0].rightNode = pn[0];
	jpn[0].leftNode = pn[1];
	

	o1 = new Scan(&innerDB, innerAttriRec, 3);
	cout << "OK new o1" << endl;
	o2 = new Scan(&outerDB, outerAttriRec, 4);
	cout << "OK new o2" << endl;
	o3 = new NestedJoin(o1, o2 , jpn, 1);
	cout << "OK new o3" << endl;
	o4 = new OutPut(STD_OUT);
	cout << "OK new o4" << endl;

	o4->setPreOperator(o3);
	o4->init();
	cout << "TEST START" << endl;
	o4->exec();

	return 0;
}
	
