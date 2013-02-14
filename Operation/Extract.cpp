#include"Extract.h"

Extract::Extract(OPERATION_NODE *extractNode_, bool yBool_, bool mBool_, bool dBool_){
	extractNode = new OPERATION_NODE;
	yBool = yBool_;
	mBool = mBool_;
	dBool = dBool_;
	memcpy(extractNode, extractNode_, sizeof(OPERATION_NODE));
}

Extract::~Extract(){
}

void Extract::init(DbEnv *env_){
	assert(preOperator != NULL);
	env = env_;
	preOperator->init(env);
	attriNum = preOperator->getAttriNum();
	initAttriRec(attriNum);
	preOperator->getAttriRec(attriRec, attriNum);
	setPos();
	initPosVal();
}

int Extract::getRow(PosVal **pv_, unsigned int pvNum_){
	int returnCode;
	while(1){
		returnCode = preOperator->getRow(pv, attriNum);
		if(returnCode != 0){
			return (-1);
		}
		
		if(yBool == false){((DatePosVal *)pv[datePos])->filterYear();}
		if(mBool == false){((DatePosVal *)pv[datePos])->filterMonth();}
		if(dBool == false){((DatePosVal *)pv[datePos])->filterDay();}
		
		for(unsigned int i =0; i < pvNum_; i++){
			*pv_[i] = *pv[i];
		}
		return (0);
	}
}


void Extract::setPos(void){
	unsigned int i;
	for(i = 0;i < attriNum; i++){
		if(extractNode->attributeID == attriRec[i]->attributeID && extractNode->tableID == attriRec[i]->tableID){
			datePos = i;
			break;
		}
	}
	if(i == attriNum){
		cout << "ERROR position : Extract" << endl;
		exit(1);
	}
	if(attriRec[i]->dataType != DATE){
		cout << "ERROR position type not DATE : Extract" << endl;
		exit(1);
	}
}


unsigned int Extract::getAttriNum(void){
	return attriNum;
}

void Extract::getAttriRec(ATTRIBUTE_REC **attriRec_, unsigned int attriNum_){
	for(unsigned int i = 0; i < attriNum_; i++){
		memcpy(attriRec_[i], attriRec[i], sizeof(ATTRIBUTE_REC));
	}
}

