#include"SelectBitOut_U.h"


SelectBitOut_U::SelectBitOut_U(Node *root_, unsigned int refNum_){
	root = root_;
	refNum = refNum_;
	refNode = new ColumnRefNode*[refNum];
	index = 0;
	setRefNode(root);
	assert(index == refNum);
}

SelectBitOut_U::~SelectBitOut_U(){

}

void SelectBitOut_U::init(DbEnv *env_){
	assert(preOperator != NULL);
	env = env_;
	preOperator->init(env);
	
	
	getFlag=0;
}

void SelectBitOut_U::setRefNode(Node *node){
	if(node->leftNode != NULL)setRefNode(node->leftNode);
	if(node->rightNode != NULL)setRefNode(node->rightNode);

	if(node->type == COLUMNREF_NODE){
		refNode[index] = (ColumnRefNode *)node;
		index++;
	}
}

int SelectBitOut_U::getRow(PosVal **pv_, unsigned int pvNum_){
	int returnCode;
	if(getFlag == -1) return -1;
	
	if(p == current){
		getFlag = -1;
		return -1;
	}
	
	returnCode = buf[p];
	p++;
	return returnCode;
}

void SelectBitOut_U::storeData(void){
	attriNum = preOperator->getAttriNum();
	initAttriRec(attriNum);
	preOperator->getAttriRec(attriRec, attriNum);
	initPosVal();
	
	p = current = max = 0;
	int returnCode;
	while(1){
		returnCode = preOperator->getRow(pv, attriNum);
		if(returnCode != 0){
			return;
		}
		if(current == max){
			buf = (int *)realloc(buf, (max + BUF_NUM)*sizeof(int));
			max += BUF_NUM;
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
			buf[current] = 1;
		}else{
			buf[current] = 0;
		}
		current++;
	}
}

unsigned int SelectBitOut_U::getAttriNum(){
	return attriNum;
}

void SelectBitOut_U::getAttriRec(ATTRIBUTE_REC **attriRec_, unsigned int attriNum_){
	for(unsigned int i = 0; i < attriNum_; i++){
		memcpy(attriRec_[i], attriRec[i], sizeof(ATTRIBUTE_REC));
	}
}
	
