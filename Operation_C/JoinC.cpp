#include"JoinC.h"

JoinC::JoinC(Operator *innerOpeNode_, OPERATION_NODE *on_, vector <Operator *> outerOpeNode_){
	innerOpeNode = innerOpeNode_;
	on = on_;
	opNum = outerOpeNode_.size();
	outerOpeNode = new Operator *[opNum];
	
	for(int i = 0; i < opNum; ++i) {
        outerOpeNode[i] = outerOpeNode_[i];
    }

	preOperator = NULL;
}


JoinC::~JoinC(){
	delete[] outerOpeNode;
}

void JoinC::init(DbEnv *env_){
	env = env_;
	assert(innerOpeNode != NULL);
	innerOpeNode->init(env);
	innerAttriNum = innerOpeNode->getAttriNum();
	outerAttriNum = 0;
	for (int i = 0; i < opNum; i++) {
		outerOpeNode[i]->init(env);
		outerAttriNum += outerOpeNode[i]->getAttriNum();
	}
	attriNum = innerAttriNum + outerAttriNum;
	initAttriRec(attriNum);

	innerOpeNode->getAttriRec(attriRec, innerAttriNum);
	for(int i = 0; i < opNum; i++) {
		outerOpeNode[i]->getAttriRec(attriRec + innerAttriNum + i, 1);
	}
	initPosVal();		
	setJoinPos();

	getFlag = 0;
	currentPos = 0;
}



int JoinC::getRow(PosVal **pv_, unsigned int pvNum_)
{
	int returnCode;

	if(getFlag == -1){
		return (-1);
	}
	returnCode = innerOpeNode->getRow(pv_, innerAttriNum);
	if(returnCode != 0){
		getFlag = -1;
		return (-1);
	}
	
	targetPos = pv_[innerPos]->position;
	//cout << targetPos << endl;
	while(1){
		for (int i = 0; i < opNum; i++) {
			outerOpeNode[i]->getRow(&pv_[innerAttriNum+i], 1);
		}
		currentPos++;
		if(targetPos == currentPos)return 0;
	}
	/*
	for (int i = 0; i < attriNum; ++i) {
		*pv_[i] = *pv[i];
	}
	*/
}	
		

void JoinC::setJoinPos(void){
	unsigned int i;
	
	if(on->attributeID == 0 && on->tableID == 0){
		innerPos = on->position;
	}else{
		for(i = 0;i < innerAttriNum; i++){
			if(on->attributeID == attriRec[i]->attributeID && on->tableID == attriRec[i]->tableID){
				innerPos = i;
				break;
			}
		}
		assert(i != innerAttriNum);
	}
}


unsigned int JoinC::getAttriNum(void){
	return attriNum;
}

void JoinC::getAttriRec(ATTRIBUTE_REC **attriRec_, unsigned int attriNum_){
	for(unsigned int i = 0; i < attriNum_; i++){
		memcpy(attriRec_[i], attriRec[i], sizeof(ATTRIBUTE_REC));
	}
}
