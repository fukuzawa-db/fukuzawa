#include"ScanFromJI_Com.h"

ScanFromJI_Com::ScanFromJI_Com(Operator *preOperator_, JOIN_INDEX *joinIndex_){
	preOperator = preOperator_;
	joinIndex = joinIndex_;
}

ScanFromJI_Com::~ScanFromJI_Com(){}

void ScanFromJI_Com::init(DbEnv *env_){
	assert(preOperator != NULL);
	assert(joinIndex != NULL);
	env = env_;
	preOperator->init(env);

	attriNum = preOperator->getAttriNum();
	initAttriRec(attriNum);
	preOperator->getAttriRec(attriRec, attriNum);
	initPosVal();
	
	getFlag = 0;
}


int ScanFromJI_Com::getRow(PosVal **pv_, unsigned int pvNum_){
	int returnCode;
	
	if(getFlag == -1){
		return -1;
	}
	
	while(1){
		returnCode = preOperator->getRow(pv, attriNum);
		if(returnCode == -1){
			getFlag = -1;
			return (-1);
		}else if(returnCode == 0){
			getPos = pv[0]->position;
			joinIndex->ScanNode->setkey(getPos);
			
			if(joinIndex->ScanNode->getRow(NULL, 0) != -1){
				for(unsigned int i =0; i < pvNum_; i++){
					*pv_[i] = *pv[i];
				}
				return (0);
			}
		}else{
			cout << "Error : ScanFromJI_Com" << endl;
			exit(1);
		}
	}
}


unsigned int ScanFromJI_Com::getAttriNum(void){
	return attriNum;
}


void ScanFromJI_Com::getAttriRec(ATTRIBUTE_REC **attriRec_, unsigned int attriNum_){
	for(unsigned int i = 0; i < attriNum_; i++){
		memcpy(attriRec_[i], attriRec[i], sizeof(ATTRIBUTE_REC));
	}
}
