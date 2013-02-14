#include"Projection.h"

Projection::Projection(OPERATION_NODE *projectionNode_, unsigned int projNum_){
	projectionNode = new OPERATION_NODE[projNum_];
	projNum = projNum_;
	memcpy(projectionNode, projectionNode_, sizeof(OPERATION_NODE) * projNum);
}

Projection::~Projection(){
}

void Projection::init(DbEnv *env_){
	assert(preOperator != NULL);
	env = env_;
	preOperator->init(env);
	attriNum = preOperator->getAttriNum();
	initAttriRec(attriNum);
	preOperator->getAttriRec(attriRec, attriNum);
	initPosVal();
}

int Projection::getRow(PosVal **pv_, unsigned int pvNum_){
	int returnCode;
	while(1){
		returnCode = preOperator->getRow(pv, attriNum);
		if(returnCode != 0){
			return (-1);
		}
		unsigned int j;
		for(unsigned int i = 0; i < projNum; i++){
			for(j = 0; j < attriNum; j++){
				if(projectionNode[i].attributeID == attriRec[j]->attributeID && projectionNode[i].tableID == attriRec[j]->tableID){
					//pv_[i] = pv[j]->clone();
					*pv_[i] = *pv[j];
					break;
				}
			}
			if(j == attriNum){
				cout << "Error NotFound Projection Attribute" << endl;
				exit(-1);
			}
		}

		return (0);
	}
}

unsigned int Projection::getAttriNum(void){
	return projNum;
}

void Projection::getAttriRec(ATTRIBUTE_REC **attriRec_, unsigned int attriNum_){
	unsigned int j;
	for(unsigned int i = 0; i < projNum; i++){
		for(j = 0; j < attriNum; j++){
			if(projectionNode[i].attributeID == attriRec[j]->attributeID && projectionNode[i].tableID == attriRec[j]->tableID){
				memcpy(attriRec_[i], attriRec[j], sizeof(ATTRIBUTE_REC));
				break;
			}
		}
		if(j == attriNum){
			cout << "Error NotFound Projectin Attribute" << endl;
			exit(-1);
		}
	}
}
