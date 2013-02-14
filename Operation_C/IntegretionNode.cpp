#include"IntegretionNode.h"

IntegretionNode::IntegretionNode(Operator **inOpe_, OPERATION_NODE** posNode_, Operator **addOpe_, OPERATION_NODE** outNode_){
	inOpe = inOpe_;
	posNode = posNode_;
	addNOde = addNode_;
	outNode = outNode_;
	preOperator = NULL;
}

IntegretionNode::~IntegretionNode(){
}

void IntegretionNode::init(){
	Operator *p;
	attriNum=0;
	int i,num;
	for(p=*inOpe; *p != NULL; p++){
		p->init();
		num = p->getAttriNum();
		attriVec.push_back(num);
		attriNum += num;
	}
	inAttriNum = attriNum;
	for(p=*addOpe; *p != NULL; p++){
		p->init();
		num = p->getAttriNum();
		attriVec.push_back(num);
		attriNum += num;
	}
	addAttriNum = attriNum - inAttriNum;
	
	initAttriRec(attriNum);
	i=0;
	num=0;
	for(p=*inOpe; *p != NULL; p++){
		p->getAttriRec(attriRec+num,attriVec[i]);
		num += attriVec[i];
		i++;
	}
	for(p=*addOpe; *p != NULL; p++){
		p->getAttriRec(attriRec+num,attriVec[i]);
		num += attriVec[i];
		i++;
	}
	
	initPosVal();
	setPosIndex();
	setOutIndex();
}


void IntegretionNode::setPosIndex(void)
