#include"AxprNode.h"

using namespace std;

AxprNode::AxprNode(AXPR_TYPE axpr_){
	type = AXPR_NODE;
	axpr = axpr_;
	leftNode = NULL;
	rightNode = NULL;
}

AxprNode::AxprNode(AXPR_TYPE axpr_, Node *leftNode_, Node *rightNode_){
	type = AXPR_NODE;
	axpr = axpr_;
	leftNode = leftNode_;
	rightNode = rightNode_;
}

AxprNode::~AxprNode(){}

void AxprNode::setAxpr(AXPR_TYPE axpr_){
	axpr = axpr_;
}

void AxprNode::setLeftNode(Node *leftNode_){
	leftNode = leftNode_;
}

void AxprNode::setRightNode(Node *rightNode_){
	rightNode = rightNode_;
}

void AxprNode::setNode(Node *leftNode_, Node *rightNode_){
	leftNode = leftNode_;
	rightNode = rightNode_;
}

AXPR_TYPE AxprNode::getAxpr(void){
	return axpr;
}

Node *AxprNode::getLeftNode(void){
	return leftNode;
}

Node *AxprNode::getRightNode(void){
	return rightNode;
}

void *AxprNode::getValue(void){
	assert(leftNode != NULL);
	assert(rightNode != NULL);
	
	switch(axpr){
		case(EQ):
			if(leftNode->type != AXPR_NODE)
				returnCode =  (*(PosVal *)leftNode->getValue() == (PosVal *)rightNode->getValue());
			else
				returnCode = (*(int *)leftNode->getValue() == *(int *)rightNode->getValue());
			break;

		case(NE):
			if(leftNode->type != AXPR_NODE)
				returnCode = (*(PosVal *)leftNode->getValue() != (PosVal *)rightNode->getValue());
			else
				returnCode = (*(int *)leftNode->getValue() != *(int *)rightNode->getValue());
			break;
		
		case(LT):
			if(leftNode->type != AXPR_NODE)
				returnCode = (*(PosVal *)leftNode->getValue() < (PosVal *)rightNode->getValue());
			else
				returnCode = (*(int *)leftNode->getValue() < *(int *)rightNode->getValue());
			break;
		
		case(GT):
			if(leftNode->type != AXPR_NODE)
				returnCode = (*(PosVal *)leftNode->getValue() > (PosVal *)rightNode->getValue());
			else
				returnCode = (*(int *)leftNode->getValue() > *(int *)rightNode->getValue());
			break;
		
		case(LE):
			if(leftNode->type != AXPR_NODE)
				returnCode = (*(PosVal *)leftNode->getValue() <= (PosVal *)rightNode->getValue());
			else
				returnCode = (*(int *)leftNode->getValue() <= *(int *)rightNode->getValue());
			break;
		
		case(GE):
			if(leftNode->type != AXPR_NODE)
				returnCode = (*(PosVal *)leftNode->getValue() >= (PosVal *)rightNode->getValue());
			else
				returnCode = (*(int *)leftNode->getValue() >= *(int *)rightNode->getValue());
			break;
		
		case(AND):
			if(leftNode->type != AXPR_NODE){
				//returnCode = (*(PosVal *)leftNode->getValue() && (PosVal *)rightNode->getValue());
			}else
				returnCode = (*(int *)leftNode->getValue() && *(int *)rightNode->getValue());
			break;

		case(OR):
			if(leftNode->type != AXPR_NODE){
				//returnCode = (*(PosVal *)leftNode->getValue() || (PosVal *)rightNode->getValue());
			}else
				returnCode = (*(int *)leftNode->getValue() || *(int *)rightNode->getValue());
			break;

			
		default:
			cout << "ERROR 	AxprNode" << endl;
			exit(-1);
		
	}
	return &returnCode;
}

