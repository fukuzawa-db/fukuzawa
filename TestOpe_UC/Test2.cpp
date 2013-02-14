#include<iostream>
#include<string>
#include<cstdlib>
#include<cassert>
#include<db_cxx.h>
#include <iomanip>

#include"CommonDataDef.h"
#include"PosVal.h"
#include"AttributeManager.h"
#include"Operator.h"
#include"OutPut.h"
#include"ScanDSM.h"
#include"ScanRLE.h"
#include"SelectBitOut.h"
#include"BitFilter.h"

#include"ScanJoinIndex.h"
#include"JoinIndex_OneHash.h"
#include"ScanFromJI.h"
/*
#include"JoinFromJoinIndex.h"
*/

int main(){
	chdir("../RunData");
	BDBOpe db_r_1("1.1.DSM");
	BDBOpe db_r_2("1.2.DSM");
	BDBOpe db_n_2("2.2.DSM");
	BDBOpe db_n_3("2.3.DSM");
	Operator *o1, *o2, *o3, *o4, *o5, *o6, *o7, *o8, *o9;
	db_r_1.open();
	db_r_2.open();
	db_n_2.open();
	db_n_3.open();
	
	
	TABLE_REC tableRec_r;
	TABLE_REC tableRec_n;

	tableRec_r.tableID = 1;
	tableRec_r.attriNum = 3;

	tableRec_n.tableID = 2;
	tableRec_n.attriNum = 4; 
	
	ATTRIBUTE_REC attriRec_r[tableRec_r.attriNum];
	ATTRIBUTE_REC attriRec_n[tableRec_n.attriNum];

	AttributeManager AM_r;
	AttributeManager AM_n;
	
	AM_r.getForTableID(tableRec_r, attriRec_r);
	for(int i=0 ; i < (int)tableRec_r.attriNum ; i++){
		cout << attriRec_r[i].attributeName << endl;
	}
	AM_n.getForTableID(tableRec_n, attriRec_n);
	for(int i=0 ; i < (int)tableRec_n.attriNum ; i++){
		cout << attriRec_n[i].attributeName << endl;
	}


/* selection1 */
	FixStrPosVal pv1(1,25);
	string str1("AMERICA");
	pv1.setStr(str1);

	ValueNode vn1 = ValueNode(&pv1);
	ColumnRefNode cn1;
	cn1.tableID = 1;
	cn1.attriID = 2;
	AxprNode an1 = AxprNode(EQ, &cn1, &vn1);
	

	
/*Join 
	OPERATION_NODE op1, op2;
	op1.tableID = 1;
	op1.attributeID = 2;
	op2.tableID = 2;
	op2.attributeID = 2;
	
	JOIN_OPERATION_NODE jon;
	jon.rightNode = op1;
	jon.leftNode = op2;
	
*/

	OPERATION_NODE op1;
	op1.tableID = 2;
	op1.attributeID = 3;



	o1 = new ScanDSM(&db_r_2, &attriRec_r[1], 1);
	cout << "OK new o1" << endl;
	
	o2 = new SelectBitOut((Node *)&an1 ,(unsigned int)1);
	cout << "OK new o2" << endl;
	o2->setPreOperator(o1);
	
	o3 = new ScanDSM(&db_r_1, attriRec_r, 1);
	cout << "OK new o3" << endl;
	
	o4 = new BitFilter(o3, o2);
	cout << "OK new o4" << endl;
	
	
	o5 = new ScanDSM(&db_n_3, &attriRec_n[2], 1);
	cout << "OK new o5" << endl;
	
	o6 = new JoinIndex_OneHash(o4, o5); 
	cout << "OK new o6" << endl;
	
	o7 = new ScanDSM(&db_n_2, &attriRec_n[1], 1);
	cout << "OK new o7" << endl;
	
	o8 = new ScanFromJI(o7, o6, &op1);
	cout << "OK new o8" << endl;
	/*
	o2 = new ScanDSM(&db4, attriRec_n + 2, 1);
	cout << "OK new o2" << endl;
	
	JoinIndex_OneHash *JI = new JoinIndex_OneHash(o1, o2); 
	JI->init();
	
	
	o3 = new ScanDSM(&db2, attriRec_r + 1, 1);
	cout << "OK new o3" << endl;
	o4 = new ScanDSM(&db3, attriRec_n + 1, 1);
	cout << "OK new o4" << endl;
	*/
	/*
	JOIN_INDEX *J = JI->createJoinIndex();

	J->ScanNode->setkey(1);
	cout << J->ScanNode->getRow(NULL, 0) << endl;
	


	
	o5 = new JoinFromJoinIndex(o3, o4, JI->createJoinIndex(), &jon);
	cout << "OK new o5" << endl;
	*/
	o9 = new OutPut(STD_OUT);
	cout << "OK new o9" << endl;
	o9->setPreOperator(o8);
	o9->init();
	cout << "TEST START" << endl;
	o9->exec();
	
	/*
	o7 = new OutPut(STD_OUT);
	cout << "OK new o7" << endl;
	o7->setPreOperator(o2);
	o7->init();
	cout << "TEST START" << endl;
	o7->exec();
	*/
}
	
