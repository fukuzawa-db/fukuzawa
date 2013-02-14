#include"SelectBitOut.h"


SelectBitOut::SelectBitOut(Node *root_, unsigned int refNum_){
	root = root_;
	refNum = refNum_;
	refNode = new ColumnRefNode*[refNum];
	index = 0;
	setRefNode(root);
	assert(index == refNum);
}

SelectBitOut::~SelectBitOut(){

}

void SelectBitOut::init(DbEnv *env_){
	assert(preOperator != NULL);
	env = env_;
	preOperator->init(env);
	attriNum = preOperator->getAttriNum();
	initAttriRec(attriNum);
	preOperator->getAttriRec(attriRec, attriNum);
	initPosVal();
	
	getFlag=0;
}

void SelectBitOut::setRefNode(Node *node){
	if(node->leftNode != NULL)setRefNode(node->leftNode);
	if(node->rightNode != NULL)setRefNode(node->rightNode);

	if(node->type == COLUMNREF_NODE){
		refNode[index] = (ColumnRefNode *)node;
		index++;
	}
}

int SelectBitOut::getRow(PosVal **pv_, unsigned int pvNum_){
	int returnCode;
	if(getFlag == -1) return -1;
	
	while(1){
		returnCode = preOperator->getRow(pv, attriNum);
		if(returnCode != 0){
			getFlag  = -1;
			return (-1);
		}
		for(index = 0; index < refNum; index++){
			unsigned int i;
			for(i = 0; i < attriNum; i++){
				if((attriRec[i]->attributeID == refNode[index]->attriID) && (attriRec[i]->tableID == refNode[index]->tableID)){
					refNode[index]->setPosVal(pv[i]);
					break;
				}
			}
			if(i == attriNum){
				cout << "Error SelectBitOut not match node" << endl;
				exit(-1);
			}
		}
		if(*(int *)root->getValue()){
			return 1;
		}else{
			return 0;
		}
	}
}

unsigned int SelectBitOut::getAttriNum(){
	return attriNum;
}

void SelectBitOut::getAttriRec(ATTRIBUTE_REC **attriRec_, unsigned int attriNum_){
	for(unsigned int i = 0; i < attriNum_; i++){
		memcpy(attriRec_[i], attriRec[i], sizeof(ATTRIBUTE_REC));
	}
}
	
