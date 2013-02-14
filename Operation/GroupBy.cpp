#include"GroupBy.h"

using namespace std;

GroupBy::GroupBy(OPERATION_NODE *groupNode_, unsigned int nodeNum_, Aggregation **aggreSet_, unsigned int aggreNum_){
	groupNode = groupNode_;
	nodeNum = nodeNum_;
	aggreSet = aggreSet_;
	aggreNum = aggreNum_;
	setAttriNum = nodeNum + aggreNum;
}


GroupBy::~GroupBy(){}


void GroupBy::init(DbEnv *env_){
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
	
	setPos();
	initHashTable();
	storeHashTable();
	
	searchIndex = 0;
	searchNode = NULL;
	getRowFlag = 0;
	

}

void GroupBy::initHashTable(void){
	memset(hashTable, 0, sizeof(GROUP_HASH_NODE *) * HASH_SIZE);
}

void GroupBy::storeHashTable(void){
	unsigned int hashkey;
	GROUP_HASH_NODE *setNode;
	int returnCode;
	//unsigned int dataSize;
	//int buffSize = getDataBuffSize();
	//char DataBuffer[buffSize];
	
	while(1){
		returnCode = preOperator->getRow(pv, attriNum);
		if(returnCode == -1)break;
		hashkey = 0;
		for(unsigned int i = 0; i < nodeNum; i++)
			hashkey += hashFunc(pv[position[i]]);
		hashkey %= HASH_SIZE;

		setNode = findSetHashTable(hashkey);
		for(unsigned int i = 0; i < aggreNum; i++){
			setNode->aggreSet[i]->inputData(pv, attriNum);
		}
			
		//dataSize = getDataBuffer(DataBuffer, buffSize);
		/*
		setNode->db->writeRecord(&key, sizeof(key), innerDataBuffer, dataSize, false);
		key++;
		*/
	}
	
}

GROUP_HASH_NODE *GroupBy::findSetHashTable(unsigned int hashkey_){
	GROUP_HASH_NODE *ghnp;

	for(ghnp = hashTable[hashkey_]; ghnp != NULL; ghnp = ghnp->next){
		if(cmpHashNode(ghnp) ==  0)return ghnp;
	}

	ghnp = initHashNode();
	ghnp->next = hashTable[hashkey_];
	hashTable[hashkey_] = ghnp;
	for(unsigned int i = 0; i < nodeNum; i++){
		ghnp->pv[i] = pv[position[i]]->clone();
	}
	for(unsigned int i = 0; i < aggreNum; i++){
		ghnp->aggreSet[i] = aggreSet[i]->clone();
	}
	return ghnp;
}


int GroupBy::getRow(PosVal **pv_, unsigned int pvNum_){
	if(getRowFlag == -1)return -1;
	
	if(searchNode != NULL){
		searchNode = searchNode->next;
		if(searchNode != NULL){
			setRow(pv_, searchNode);
			return 0;
		}
	}		
			
	while(1){
		if(searchIndex == HASH_SIZE){
			getRowFlag = -1;
			return -1;
		}
		searchNode = hashTable[searchIndex];
		searchIndex++;
		if(searchNode != NULL){
			setRow(pv_, searchNode);
			return 0;
		}
	}

}

void GroupBy::setRow(PosVal **pv_, GROUP_HASH_NODE *np){
	unsigned int i;
	for(i= 0; i < nodeNum; i++){
		*pv_[i] = *(np->pv[i]);
	}
	for(;i < setAttriNum; i++){
		*pv_[i] = *(np->aggreSet[i - nodeNum]->getValue());
	}
}


unsigned int GroupBy::getAttriNum(void){
	return setAttriNum;
}


void GroupBy::getAttriRec(ATTRIBUTE_REC **attriRec_, unsigned int attriNum_){
	unsigned int i;
	unsigned int j;
	ATTRIBUTE_REC tmpAttriRec;
	for(i = 0; i < nodeNum; i++){
		memcpy(attriRec_[i], attriRec[position[i]], sizeof(ATTRIBUTE_REC));
	}
	for(j = 0; j < aggreNum; i++, j++){
		tmpAttriRec = aggreSet[j]->getAttriRec();
		memcpy(attriRec_[i], &tmpAttriRec, sizeof(ATTRIBUTE_REC));
	}
	assert(i == attriNum_);
}


void GroupBy::setPos(void){
	position = new unsigned int[nodeNum];
	unsigned int i;
	
	for(unsigned int j = 0; j < nodeNum; j++){
		if((groupNode[j].attributeID == 0) && (groupNode[j].tableID ==0)){
			position[j] = groupNode[j].position;
		}else{
			for(i = 0;i < attriNum; i++){
				if(groupNode[j].attributeID == attriRec[i]->attributeID && groupNode[j].tableID == attriRec[i]->tableID){
					position[j] = i;
					break;
				}
			}
			assert(i != attriNum);
		}
	}
}


GROUP_HASH_NODE *GroupBy::initHashNode(void){
	GROUP_HASH_NODE *ghnp;

	ghnp = new GROUP_HASH_NODE;
	ghnp->next = NULL;
	ghnp->pv = new PosVal*[nodeNum];
	ghnp->aggreSet = new Aggregation*[aggreNum];
	return ghnp;
}



int GroupBy::cmpHashNode(GROUP_HASH_NODE *hnp_){
	unsigned int i;
	for(i = 0; i < nodeNum; i++)
		if(!(*pv[position[i]] == hnp_->pv[i]))break;	
	
	if(i == nodeNum)return 0;
	return 1;
}


