#include<iostream>
#include<string>
#include<cstdlib>

#include"CommonDataDef.h"
#include"Node.h"
#include"AxprNode.h"
#include"ColumnRefNode.h"
#include"ValueNode.h"
#include"ArithmeticNode.h"

#include"IntPosVal.h"
#include"LongPosVal.h"
#include"FloatPosVal.h"
#include"DoublePosVal.h"

int main(int argc, char *argv[]){
	
	PosVal *pv1 = new IntPosVal(2, 2126);
	PosVal *pv2 = new IntPosVal(3, 2126);
	PosVal *pv3 = new FloatPosVal(1, 4.4);
	PosVal *pv4 = new FloatPosVal(2, 3.4);

	ValueNode *vn1 = new ValueNode(pv1);
	ValueNode *vn2 = new ValueNode(pv2);
	ValueNode *vn3 = new ValueNode(pv3);
	ValueNode *vn4 = new ValueNode(pv4);
/*
	AxprNode av1 = AxprNode(EQ);
	av1.setNode(&vn1, &vn2);
	AxprNode av2 = AxprNode(EQ);
	av2.setNode(&vn3, &vn4);
	AxprNode av3 = AxprNode(OR);
	av3.setNode(&av1, &av2);
*/

	ArithmeticNode ariNode1 = ArithmeticNode(ADD);
	ariNode1.setNode(vn1, vn3);
	ArithmeticNode ariNode2 = ArithmeticNode(SUB);
	ariNode2.setNode(vn1, vn2);
	ArithmeticNode ariNode3 = ArithmeticNode(MUL);
	ariNode3.setNode(vn3, vn4);
	ArithmeticNode ariNode4 = ArithmeticNode(DIV);
	ariNode4.setNode(&ariNode1, &ariNode3);
	
	
	cout << *(double*)(((PosVal *)ariNode1.getValue())->value) << endl;
	cout << *(double*)(((PosVal *)ariNode2.getValue())->value) << endl;
	cout << *(double*)(((PosVal *)ariNode3.getValue())->value) << endl;
	cout << *(double*)(((PosVal *)ariNode4.getValue())->value) << endl;
	
	
/*		
	if(*(int *)av1.getValue()){
		cout << "Equal" << endl;
	}else{
		cout << "Not equal" << endl;
	}

	if(*(int *)av2.getValue()){
		cout << "Equal" << endl;
	}else{
		cout << "Not equal" << endl;
	}

	if(*(int *)av3.getValue()){
		cout << "OK" << endl;
	}else{
		cout << "NG" << endl;

	}
*/
}
