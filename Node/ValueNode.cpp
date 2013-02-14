#include"ValueNode.h"

ValueNode::ValueNode(){
	type = VALUE_NODE;
	leftNode = NULL;
	rightNode = NULL;
}

ValueNode::ValueNode(PosVal *pv_){
	type = VALUE_NODE;
	pv = pv_;
	leftNode = NULL;
	rightNode = NULL;
}

ValueNode::~ValueNode(){}

void ValueNode::setPosVal(PosVal *pv_){
	pv = pv_;
}

void *ValueNode::getValue(void){
	return pv;
}
