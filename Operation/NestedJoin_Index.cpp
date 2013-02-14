#include"NestedJoin_Index.h"

NestedJoin_Index::NestedJoin_Index(IndexScan *innerOpeNode_, Operator *outerOpeNode_, OPERATION_NODE *op_){
	innerOpeNode = innerOpeNode_;
	outerOpeNode = outerOpeNode_;
	preOperator = NULL;
	op = op_;
}

NestedJoin_Index::~NestedJoin_Index(){
	//delete innerScanNode;
}


void NestedJoin_Index::init(DbEnv *env_){
	assert(innerOpeNode != NULL && outerOpeNode != NULL);
	env = env_;
	innerOpeNode->init(env);
	outerOpeNode->init(env);
	innerAttriNum = innerOpeNode->getAttriNum();
	outerAttriNum = outerOpeNode->getAttriNum();
	attriNum = innerAttriNum + outerAttriNum;
	initAttriRec(attriNum);

	innerOpeNode->getAttriRec(attriRec, innerAttriNum);
	outerOpeNode->getAttriRec(attriRec + innerAttriNum, outerAttriNum);
	initPosVal();
	
	setPos();

	getRowFlag = 0;
}

int NestedJoin_Index::getRow(PosVal **pv_, unsigned int pvNum_){
	int returnCode;

	if(getRowFlag == 0){
		returnCode = outerOpeNode->getRow(&pv[innerAttriNum], outerAttriNum);
		if(returnCode == 0){
			innerOpeNode->keySet(pv[outerPos]);
			getRowFlag = 1;
		}else{
			getRowFlag = -1;
		}
	}
	if(getRowFlag == -1){
		return(-1);
	}

	while(1){
		returnCode = innerOpeNode->getRow(pv, innerAttriNum);
		if(returnCode != 0){
			returnCode = outerOpeNode->getRow(&pv[innerAttriNum], outerAttriNum);
			if(returnCode != 0){
				getRowFlag = -1;
				cout << returnCode << endl;
				return(-1);
			}
			innerOpeNode->keySet(pv[outerPos]);
			continue;
		}

		for(unsigned int i = 0; i < attriNum; i++)
			*pv_[i] = *pv[i];
		return 0;
	}	
}

unsigned int NestedJoin_Index::getAttriNum(void){
	return attriNum;
}

void NestedJoin_Index::getAttriRec(ATTRIBUTE_REC **attriRec_, unsigned int attriNum_){
	for(unsigned int i = 0; i < attriNum_; i++){
		memcpy(attriRec_[i], attriRec[i], sizeof(ATTRIBUTE_REC));
	}
}

void NestedJoin_Index::setPos(void){
	unsigned int i;
	for(i = innerAttriNum; i < attriNum; i++){
		if(op[0].attributeID == attriRec[i]->attributeID && op[0].tableID == attriRec[i]->tableID){
				outerPos = i;
				break;
			}
	}
	assert(i != attriNum);
}
	
