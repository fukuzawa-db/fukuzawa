#include"AggreOut.h"

using namespace std;

AggreOut::AggreOut(Aggregation **aggreSet_, unsigned int aggreNum_){
	aggreSet = aggreSet_;
	aggreNum = aggreNum_;
}


AggreOut::~AggreOut(){}


void AggreOut::init(DbEnv *env_){
	assert(preOperator != NULL);
	env = env_;
	preOperator->init(env);
	attriNum = preOperator->getAttriNum();
	initAttriRec(attriNum);
	preOperator->getAttriRec(attriRec, attriNum);
	initPosVal();
	
	for(unsigned int i = 0; i < aggreNum ; i++){
		aggreSet[i]->init(attriRec, attriNum);
	}
	

	getRowFlag = 0;
}


int AggreOut::getRow(PosVal **pv_, unsigned int pvNum_){
	int returnCode;
	
	if(getRowFlag == -1)return -1;
	
	while(1){
		returnCode = preOperator->getRow(pv, attriNum);
		if(returnCode == -1)break;

		for(unsigned int i = 0; i < aggreNum; i++){
			aggreSet[i]->inputData(pv, attriNum);
		}
	}
	
	setRow(pv_);
	getRowFlag = -1;
	return 0;
	
}

void AggreOut::setRow(PosVal **pv_){
	unsigned int i;
	for(i=0;i < aggreNum; i++){
		*pv_[i] = *(aggreSet[i]->getValue());
	}
}


unsigned int AggreOut::getAttriNum(void){
	return aggreNum;
}


void AggreOut::getAttriRec(ATTRIBUTE_REC **attriRec_, unsigned int attriNum_){
	unsigned int i;
	ATTRIBUTE_REC tmpAttriRec;
	for(i = 0; i < aggreNum; i++){
		tmpAttriRec = aggreSet[i]->getAttriRec();
		memcpy(attriRec_[i], &tmpAttriRec, sizeof(ATTRIBUTE_REC));
	}
	assert(i == attriNum_);
}

