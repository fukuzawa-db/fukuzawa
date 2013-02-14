#include"ColumnRefNode.h"

ColumnRefNode::ColumnRefNode(){
	type = COLUMNREF_NODE;
	leftNode = NULL;
	rightNode = NULL;
	pv = NULL;
}

ColumnRefNode::~ColumnRefNode(){}


void *ColumnRefNode::getValue(void){
	return pv;
}

void ColumnRefNode::setPosVal(PosVal *pv_){
	if(pv != NULL)delete pv;
	pv = pv_->clone();
}


