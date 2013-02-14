#include"ScanFromJI.h"

ScanFromJI::ScanFromJI(Operator *innerOpe_, Operator *outerOpe_, OPERATION_NODE *opNode_){
	innerOpe = innerOpe_;
	outerOpe = outerOpe_;
	opNode = opNode_;
}

ScanFromJI::~ScanFromJI(){}

void ScanFromJI::init(DbEnv *env_){
	assert(innerOpe != NULL && outerOpe != NULL && opNode != NULL);
	env = env_;
	innerOpe->init(env);
	outerOpe->init(env);

	innerAttriNum = innerOpe->getAttriNum();
	outerAttriNum = outerOpe->getAttriNum();
	attriNum = innerAttriNum + outerAttriNum;
	initAttriRec(attriNum);
	innerOpe->getAttriRec(attriRec, innerAttriNum);
	outerOpe->getAttriRec(attriRec + innerAttriNum, outerAttriNum);
	initPosVal();
	setPos();
	
	getRowFlag = 0;
}


int ScanFromJI::getRow(PosVal **pv_, unsigned int pvNum_){
	int returnCode;
	
	if(getRowFlag == -1){
		return -1;
	}
	returnCode = outerOpe->getRow(&pv[innerAttriNum], outerAttriNum);
	if(returnCode == -1){
		getRowFlag = -1;
		return -1;
	}
	getPos = pv[pos]->position;

	while(1){
		returnCode = innerOpe->getRow(pv, innerAttriNum);
		
		if(returnCode == -1){
			getRowFlag = -1;
			return -1;
		}
		
		if((unsigned int)getPos == pv[0]->position){
			for(unsigned int i =0; i < pvNum_; i++){
				*pv_[i] = *pv[i];
			}
			return (0);
		}else if((unsigned int)getPos < pv[0]->position){
			while((unsigned int)getPos < pv[0]->position){
				returnCode = outerOpe->getRow(&pv[innerAttriNum], outerAttriNum);
				if(returnCode == -1){
					getRowFlag = -1;
					return -1;
				}
				getPos = pv[pos]->position;
			}
			if((unsigned int)getPos == pv[0]->position){
				for(unsigned int i =0; i < pvNum_; i++){
					*pv_[i] = *pv[i];
				}
				return (0);
			}
		}
	}
		
		
}

void ScanFromJI::setPos(void){
	unsigned int i;
	
	if((opNode[0].attributeID == 0) && (opNode[0].tableID ==0)){
		pos = opNode[0].position;
	}else{
		for(i = 0;i < attriNum; i++){
			if(opNode[0].attributeID == attriRec[i]->attributeID && opNode[0].tableID == attriRec[i]->tableID){
				pos = i;
				break;
			}
		}
		assert(i != attriNum);
	}
}


unsigned int ScanFromJI::getAttriNum(void){
	return attriNum;
}


void ScanFromJI::getAttriRec(ATTRIBUTE_REC **attriRec_, unsigned int attriNum_){
	for(unsigned int i = 0; i < attriNum_; i++){
		memcpy(attriRec_[i], attriRec[i], sizeof(ATTRIBUTE_REC));
	}
}
