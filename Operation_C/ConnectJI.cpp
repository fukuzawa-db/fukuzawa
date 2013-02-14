#include"ConnectJI.h"

ConnectJI::ConnectJI(JOIN_INDEX *joinIndex1_, JOIN_INDEX *joinIndex2_){
	joinIndex1 = joinIndex1_;
	joinIndex2 = joinIndex2_;
}

ConnectJI::~ConnectJI(){}

void ConnectJI::init(DbEnv *env_){
	env = env_;
	assert(joinIndex1 != NULL && joinIndex2 != NULL);
	initAttriRec(1);
	attriRec[0]->dataType = INT;
	attriRec[0]->dataLength = sizeof(int);
	
	initJoinIndex();
}


void ConnectJI::initJoinIndex(void){
	joinIndex = new JOIN_INDEX;
	tmpnam(tmpFileName);
	joinIndex->dbName = tmpFileName;
	joinIndex->db = new BDBOpe(env, joinIndex->dbName, false);
	joinIndex->db->setDupCompare();
	joinIndex->db->open();
	joinIndex->ScanNode = new ScanJoinIndex(joinIndex->db, attriRec, 1);
}


JOIN_INDEX	*ConnectJI::createJoinIndex(void){
	unsigned int key1, data1;
	unsigned int key2, data2;
	int returnCode;
	
	joinIndex1->ScanNode->resetGetPos();
	while(1){
		returnCode = joinIndex1->ScanNode->getData(&key1, &data1);
		if(returnCode == -1)break;
		
		key2 = data1;
		joinIndex2->ScanNode->setkey(key2);
		while(1){
			data2 =  joinIndex2->ScanNode->getRow(NULL, 0);
			if(data2 == -1)break;
			
			joinIndex->db->writeRecord(&key1, sizeof(key1), &data2, sizeof(data2), true);
		}
	}
	return joinIndex;
}
			

unsigned int ConnectJI::getAttriNum(void){
	return attriNum;
}


void ConnectJI::getAttriRec(ATTRIBUTE_REC **attriRec_, unsigned int attriNum_){
	for(unsigned int i = 0; i < attriNum_; i++){
		memcpy(attriRec_[i], attriRec[i], sizeof(ATTRIBUTE_REC));
	}
}
