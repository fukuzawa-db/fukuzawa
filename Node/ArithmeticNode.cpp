#include"ArithmeticNode.h"

using namespace std;

ArithmeticNode::ArithmeticNode(ARITH_TYPE axpr_){
	type = ARITH_NODE;
	axpr = axpr_;
	leftNode = NULL;
	rightNode = NULL;
	typeFlag = 0;
	pv = NULL;
	leftVal = NULL;
	rightVal = NULL;
}

ArithmeticNode::ArithmeticNode(ARITH_TYPE axpr_, Node *leftNode_, Node *rightNode_){
	type = ARITH_NODE;
	axpr = axpr_;
	leftNode = leftNode_;
	rightNode = rightNode_;
	typeFlag = 0;
	pv = NULL;
	leftVal = NULL;
	rightVal = NULL;
}

ArithmeticNode::~ArithmeticNode(){}

void ArithmeticNode::setAxpr(ARITH_TYPE axpr_){
	axpr = axpr_;
}

void ArithmeticNode::setLeftNode(Node *leftNode_){
	leftNode = leftNode_;
}

void ArithmeticNode::setRightNode(Node *rightNode_){
	rightNode = rightNode_;
}

void ArithmeticNode::setNode(Node *leftNode_, Node *rightNode_){
	leftNode = leftNode_;
	rightNode = rightNode_;
}

ARITH_TYPE ArithmeticNode::getAxpr(void){
	return axpr;
}

Node *ArithmeticNode::getLeftNode(void){
	return leftNode;
}

Node *ArithmeticNode::getRightNode(void){
	return rightNode;
}

void *ArithmeticNode::getValue(void){
	assert(leftNode != NULL);
	assert(rightNode != NULL);
	
	assert(leftNode->type != AXPR_NODE);
	assert(rightNode->type != AXPR_NODE);
	
	//setValue(leftNode, leftVal);
	setLeftValue(leftNode);
	setRightValue(rightNode);
	
	if(pv != NULL) delete pv;
	
	switch(axpr){
		case(ADD):
			if(typeFlag == 1){
				pv = new LongPosVal(0, (long)(*(double *)leftVal + *(double *)rightVal));
				return pv;
			}
			if(typeFlag == 2){
				pv = new DoublePosVal(0, *(double *)leftVal + *(double *)rightVal);
				return pv;
			}
			cout << "ERROR ArithmeticNode" << endl;
			exit(-1);
				
		case(SUB):
			if(typeFlag == 1){
				pv = new LongPosVal(0, (long)(*(double *)leftVal - *(double *)rightVal));
				return pv;
			}
			if(typeFlag == 2){
				pv = new DoublePosVal(0, *(double *)leftVal - *(double *)rightVal);
				return pv;
			}
			cout << "ERROR ArithmeticNode" << endl;
			exit(-1);
			
		case(MUL):
			if(typeFlag == 1){
				pv = new LongPosVal(0, (long)(*(double *)leftVal * *(double *)rightVal));
				return pv;
			}
			if(typeFlag == 2){
				pv = new DoublePosVal(0, *(double *)leftVal * *(double *)rightVal);
				return pv;
			}
			cout << "ERROR ArithmeticNode" << endl;
			exit(-1);
			
		case(DIV):
			if(rightVal == 0){
				cout << "ERROR 0 DIV : ArithmetricNode" << endl;
				exit(-1);
			}
			if(typeFlag == 1 || typeFlag == 2){
				pv = new DoublePosVal(0, *(double *)leftVal / *(double *)rightVal);
				return pv;
			}
			
			cout << "ERROR ArithmetricNode" << endl;
			exit(-1);
			
		default:
			cout << "ERROR ArithmeticNode" << endl;
			exit(-1);
	}
}


void ArithmeticNode::setLeftValue(Node *node_){	
	PosVal *tmpPV;
	tmpPV = (PosVal *)node_->getValue();
	
	if(leftVal != NULL)delete (double* )leftVal;
	
	switch(tmpPV->type){
		case(INT):
			leftVal = new double(*(int *)tmpPV->value);
			if(typeFlag < 1)
				typeFlag = 1;
			return;
		case(LONG):
			leftVal = new double(*(long *)tmpPV->value);
			if(typeFlag < 1)
				typeFlag = 1;
			return;
		case(FLOAT):
			leftVal = new double(*(float *)tmpPV->value);
			typeFlag = 2;
			return;
		case(DOUBLE):
			leftVal = new double(*(double *)tmpPV->value);
			typeFlag = 2;
			return;
		
		case(FIXED_TEXT):
		case(VARIABLE_TEXT):
		case(DATE):
			cout << "Not define type" << endl;
			exit(-1);
		
		default:
			cout << "ERROR ArithmeticNode" << endl;
			exit(-1);
	}
}	
	
void ArithmeticNode::setRightValue(Node *node_){	
	PosVal *tmpPV;
	tmpPV = (PosVal *)node_->getValue();
	
	if(rightVal != NULL) delete (double* )rightVal;
	
	switch(tmpPV->type){
		case(INT):
			rightVal = new double(*(int *)tmpPV->value);
			if(typeFlag < 1)
				typeFlag = 1;
			return;
		case(LONG):
			rightVal = new double(*(long *)tmpPV->value);
			if(typeFlag < 1)
				typeFlag = 1;
			return;
		case(FLOAT):
			rightVal = new double(*(float *)tmpPV->value);
			typeFlag = 2;
			return;
		case(DOUBLE):
			rightVal = new double(*(double *)tmpPV->value);
			typeFlag = 2;
			return;
		
		case(FIXED_TEXT):
		case(VARIABLE_TEXT):
		case(DATE):
			cout << "Not define type" << endl;
			exit(-1);
		
		default:
			cout << "ERROR ArithmeticNode" << endl;
			exit(-1);
	}
}	

	
