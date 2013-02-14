#include"BitFilter.h"

BitFilter::BitFilter(Operator *preOperator_, Operator *bitOpe_){
	preOperator = preOperator_;
	bitOpe = bitOpe_;
}

BitFilter::~BitFilter(){}

void BitFilter::init(DbEnv *env_){
	env = env_;
	assert(preOperator != NULL);
	assert(bitOpe != NULL);
	preOperator->init(env);
	bitOpe->init(env);
	attriNum = preOperator->getAttriNum();
	initAttriRec(attriNum);
	preOperator->getAttriRec(attriRec, attriNum);
	initPosVal();
}


int BitFilter::getRow(PosVal **pv_, unsigned int pvNum_){
	int returnCode;
	while(1){
		returnCode = preOperator->getRow(pv, attriNum);
		if(returnCode != 0){
			return (-1);
		}
		returnCode = bitOpe->getRow(NULL,0);
		if(returnCode == 0){
			continue;
		}else if(returnCode == 1){
			for(unsigned int i =0; i < pvNum_; i++){
				*pv_[i] = *pv[i];
			}
			return (0);
		}else{
			cout << "Error : SelectWithBit" << endl;
			exit(1);
		}
	}
}


unsigned int BitFilter::getAttriNum(void){
	return attriNum;
}


void BitFilter::getAttriRec(ATTRIBUTE_REC **attriRec_, unsigned int attriNum_){
	for(unsigned int i = 0; i < attriNum_; i++){
		memcpy(attriRec_[i], attriRec[i], sizeof(ATTRIBUTE_REC));
	}
}
