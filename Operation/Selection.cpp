#include"Selection.h"


Selection::Selection(Node *root_, unsigned int refNum_){
	root = root_;
	refNum = refNum_;
	refNode = new ColumnRefNode*[refNum];
	index = 0;
	setRefNode(root);
	assert(index == refNum);
}

Selection::~Selection(){

}

void Selection::init(DbEnv *env_){
	assert(preOperator != NULL);
	env = env_;
	preOperator->init(env);
	attriNum = preOperator->getAttriNum();
	initAttriRec(attriNum);
	preOperator->getAttriRec(attriRec, attriNum);
	initPosVal();
}

void Selection::setRefNode(Node *node){
	if(node->leftNode != NULL)setRefNode(node->leftNode);
	if(node->rightNode != NULL)setRefNode(node->rightNode);

	if(node->type == COLUMNREF_NODE){
		refNode[index] = (ColumnRefNode *)node;
		index++;
	}
}

int Selection::getRow(PosVal **pv_, unsigned int pvNum_){
	int returnCode;
	//int num=0; //add
	while(1){
		returnCode = preOperator->getRow(pv, attriNum);
		if(returnCode != 0){
			return (-1);
		}
		//num++; //add
		for(index = 0; index < refNum; index++){
			unsigned int i;
			for(i = 0; i < attriNum; i++){
				if((attriRec[i]->attributeID == refNode[index]->attriID) && (attriRec[i]->tableID == refNode[index]->tableID)){
					refNode[index]->setPosVal(pv[i]);
					break;
				}
			}
			if(i == attriNum){
				cout << "Error Selection not match node" << endl;
				exit(-1);
			}
		}
		if(*(int *)root->getValue()){
			
			for(unsigned int i =0; i < pvNum_; i++){
				//pv_[i] = pv[i]->clone();
				*pv_[i] = *pv[i];
			}
			return (0);
			
			//cout << num << endl;  //add 
			
		}
	}
}
unsigned int Selection::getAttriNum(){
	return attriNum;
}

void Selection::getAttriRec(ATTRIBUTE_REC **attriRec_, unsigned int attriNum_){
	for(unsigned int i = 0; i < attriNum_; i++){
		memcpy(attriRec_[i], attriRec[i], sizeof(ATTRIBUTE_REC));
	}
}
	
