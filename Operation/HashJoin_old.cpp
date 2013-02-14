#include"HashJoin_old.h"

HashJoin_old::HashJoin_old(Operator *innerOpeNode_, Operator *outerOpeNode_, JOIN_OPERATION_NODE *joinOpeNode_, unsigned int nodeNum_){
	innerOpeNode = innerOpeNode_;
	outerOpeNode = outerOpeNode_;
	preOperator = NULL;
	joinOpeNode = joinOpeNode_;
	nodeNum = nodeNum_;
}

HashJoin_old::~HashJoin_old(){
/*
	for(int i=0; i < HASH_SIZE; i++){
		if(innerHashTable[i] != NULL)
			deleteNode(innerHashTable[i]);
	}
*/
}

void HashJoin_old::del(void){
	for(int i=0; i < HASH_SIZE; i++){
		if(innerHashTable[i] != NULL)
			deleteNode(innerHashTable[i]);
		if(outerHashTable[i] != NULL)
			deleteNode(outerHashTable[i]);
	}
}

void HashJoin_old::deleteNode(HASH_NODE_OLD *hnp_){
	hnp_->db->close();
	hnp_->db->remove();
	delete hnp_->db;
	delete hnp_;
}

void HashJoin_old::init(DbEnv *env_){
	assert(innerOpeNode != NULL &&  outerOpeNode != NULL);
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

	setJoinPos();
	initHashTable();
	storeInnerNode();
	storeOuterNode();
	getRowFlag = 0;
	outerHashkey = 0;
	outerHnp = NULL;

}

/*
int HashJoin_old::getRow(PosVal **pv_, unsigned int pvNum_){
	int returnCode;
	HASH_NODE_OLD *hnp;
	unsigned int hashkey;
	
	if(getRowFlag == 0){
		while(1){
			returnCode = outerOpeNode->getRow(&pv[innerAttriNum], outerAttriNum);
			if(returnCode != 0){
				getRowFlag = -1;
				return -1;
			}else{
				hashkey = 0;
				for(unsigned int i = 0; i < nodeNum; i++)
					hashkey += hashFunc(pv[outerPos[i]]);
				hashkey = hashkey%HASH_SIZE;
				hnp = findGetHashTable(hashkey);
				if(hnp != NULL){
					innerScanNode = new Scan(hnp->db, attriRec, innerAttriNum);
					getRowFlag = 1;
					break;
				}
			}
		}
	}			

	if(getRowFlag == -1){
		return -1;
	}

	while(1){
		returnCode = innerScanNode->getRow(pv, innerAttriNum);
		if(returnCode == 0){
			for(unsigned int i = 0; i < attriNum; i++)
				*pv_[i] = *pv[i];
			return 0;
		}

		while(1){
			returnCode = outerOpeNode->getRow(&pv[innerAttriNum], outerAttriNum);
			if(returnCode != 0){
				getRowFlag = -1;
				return -1;
			}else{
				delete innerScanNode;
				hashkey = 0;
				for(unsigned int i = 0; i < nodeNum; i++)
					hashkey += hashFunc(pv[outerPos[i]]);
				hashkey %= HASH_SIZE;
				hnp = findGetHashTable(hashkey);
				if(hnp != NULL){
					innerScanNode = new Scan(hnp->db, attriRec, innerAttriNum);
					break;
				}
			}
		}
	}	
}
*/

int HashJoin_old::getRow(PosVal **pv_, unsigned int pvNum_){
	int returnCode;

	if(getRowFlag == 0){
		while(1){
			if(outerHnp == NULL){
				if(outerHashkey == HASH_SIZE){
					getRowFlag = -1;
					del();
					return -1;
				}
				outerHnp = outerHashTable[outerHashkey];
				outerHashkey++;
				if(outerHnp == NULL)continue;
			}
			assert(outerHnp != NULL);

			innerHnp = findGetHashTable(outerHnp, outerHashkey-1);
			if(innerHnp != NULL){
				innerScanNode = new Scan(innerHnp->db, attriRec, innerAttriNum);
				outerScanNode = new Scan(outerHnp->db, &attriRec[innerAttriNum], outerAttriNum);
				getRowFlag = 1;
				break;
			}
			outerHnp = outerHashTable[outerHashkey];
			outerHashkey++;
		}
	}

	if(getRowFlag == -1){
		return -1;
	}

	while(1){
		if(getRowFlag == 1){
			//returnCode = innerScanNode->getRow(pv, innerAttriNum);
			returnCode = outerScanNode->getRow(&pv[innerAttriNum], outerAttriNum);
			if(returnCode != 0)	getRowFlag = -2;
			else				getRowFlag = 2;
		}
		if(getRowFlag == -2){
			if(outerHashkey == HASH_SIZE){
				getRowFlag = -1;
				del();
				return -1;
			}
			outerHnp = outerHashTable[outerHashkey];
			outerHashkey++;
			while(1){
				if(outerHnp == NULL){
					if(outerHashkey == HASH_SIZE){
						getRowFlag = -1;
						del();
						return -1;
					}
					outerHnp = outerHashTable[outerHashkey];
					outerHashkey++;
					if(outerHnp == NULL)continue;
				}

				assert(outerHnp != NULL);
				innerHnp = findGetHashTable(outerHnp, outerHashkey-1);
				if(innerHnp != NULL){
					delete innerScanNode;
					delete outerScanNode;
					innerScanNode = new Scan(innerHnp->db, attriRec, innerAttriNum);
					outerScanNode = new Scan(outerHnp->db, &attriRec[innerAttriNum], outerAttriNum);
					getRowFlag = 1;
					break;
				}
				
				outerHnp = outerHashTable[outerHashkey];
				outerHashkey++;
			}
			continue;
		}
		
		while(1){
			returnCode = innerScanNode->getRow(pv, innerAttriNum);
			//returnCode = outerScanNode->getRow(&pv[innerAttriNum], outerAttriNum);
			if(returnCode == 0){
				unsigned int posIndex;
				for(posIndex = 0; posIndex < nodeNum; posIndex++){
					if(!(*pv[innerPos[posIndex]] == pv[outerPos[posIndex]]))
						break;
				}
				if(posIndex == nodeNum){
					for(unsigned int i = 0; i < attriNum; i++) *pv_[i] = *pv[i];
					return 0;
				}
			}else{
				getRowFlag = 1;
				innerScanNode->resetGetPos();
				break;
			}
		}	
	}
}
				

HASH_NODE_OLD *HashJoin_old::findGetHashTable(HASH_NODE_OLD* outerhnp_, unsigned int hashkey_){
	HASH_NODE_OLD *hnp;

	hnp = innerHashTable[hashkey_];
	return hnp;
}


unsigned int HashJoin_old::getAttriNum(void){
	return attriNum;
}

void HashJoin_old::getAttriRec(ATTRIBUTE_REC **attriRec_, unsigned int attriNum_){
	for(unsigned int i = 0; i < attriNum_; i++){
		memcpy(attriRec_[i], attriRec[i], sizeof(ATTRIBUTE_REC));
	}
}

void HashJoin_old::initHashTable(void){
	memset(innerHashTable, 0, sizeof(HASH_NODE_OLD *) * HASH_SIZE);
	memset(outerHashTable, 0, sizeof(HASH_NODE_OLD *) * HASH_SIZE);
}

void HashJoin_old::storeInnerNode(void){
	unsigned int hashkey;
	HASH_NODE_OLD *setNode;
	int returnCode;
	unsigned int dataSize;
	int buffSize = getInnerDataBuffSize();
	char innerDataBuffer[buffSize];
	unsigned key = 1;
	while(1){
		returnCode = innerOpeNode->getRow(pv, innerAttriNum);
		if(returnCode == -1)break;
		hashkey = 0;
		for(unsigned int i = 0; i < nodeNum; i++)
			hashkey += hashFunc(pv[innerPos[i]]);
		hashkey %= HASH_SIZE;

		setNode = findSetHashTable(innerHashTable, hashkey, innerPos);
		
		dataSize = getDataBuffer(innerDataBuffer, buffSize, 0 , innerAttriNum);
		setNode->db->writeRecord(&key, sizeof(key), innerDataBuffer, dataSize, false);
		setNode->num++;
		key++;
	}
}

void HashJoin_old::storeOuterNode(void){
	unsigned int hashkey;
	HASH_NODE_OLD *setNode;
	int returnCode;
	unsigned int dataSize;
	int buffSize = getOuterDataBuffSize();
	char outerDataBuffer[buffSize];
	unsigned key = 1;
	while(1){
		returnCode = outerOpeNode->getRow(&pv[innerAttriNum], outerAttriNum);
		if(returnCode == -1)break;
		hashkey = 0;
		for(unsigned int i = 0; i < nodeNum; i++)
			hashkey += hashFunc(pv[outerPos[i]]);
		hashkey %= HASH_SIZE;

		setNode = findSetHashTable(outerHashTable, hashkey, outerPos);
		dataSize = getDataBuffer(outerDataBuffer, buffSize, innerAttriNum, outerAttriNum);
//		cout << "out = " << dataSize << endl;		
//		for(int i = 0; i<dataSize; i++) cout << outerDataBuffer[i];
//		cout << endl;
		setNode->db->writeRecord(&key, sizeof(key), outerDataBuffer, dataSize, false);
		setNode->num++;
		key++;
	}
}

/*
HASH_NODE_OLD *HashJoin_old::findGetHashTable(unsigned int hashkey_){
	HASH_NODE_OLD *hnp;
	hnp = hashTable[hashkey_];

	for(hnp = hashTable[hashkey_]; hnp != NULL; hnp = hnp->next){
		if(cmpHashNode(hnp, outerPos) ==  0)return hnp;
	}
	return NULL;
}
*/

HASH_NODE_OLD *HashJoin_old::findSetHashTable(HASH_NODE_OLD **hashTable_, unsigned int hashkey_, unsigned int *posSet_){
	HASH_NODE_OLD *hnp;

	hnp = hashTable_[hashkey_];
	if(hnp != NULL) return hnp;

	hnp = initHashNode();
	hashTable_[hashkey_] = hnp;
	return hnp;
}


HASH_NODE_OLD *HashJoin_old::initHashNode(void){
	HASH_NODE_OLD *hnp;

	hnp = new HASH_NODE_OLD;
	hnp->num = 0;
	tmpnam(tmpFileName);
	hnp->dbName = tmpFileName;
	hnp->db = new BDBOpe(env, hnp->dbName);
	hnp->db->open();

	return hnp;
}


void HashJoin_old::setJoinPos(void){
	innerPos = new unsigned int[nodeNum];
	outerPos = new unsigned int[nodeNum];

	unsigned int i;
	for(unsigned int j = 0; j < nodeNum; j++){
		for(i = 0;i < innerAttriNum; i++){
			if(joinOpeNode[j].rightNode.attributeID == attriRec[i]->attributeID && joinOpeNode[j].rightNode.tableID == attriRec[i]->tableID){
				innerPos[j] = i;
				break;
			}
		}
		assert(i != innerAttriNum);

		for(i = innerAttriNum; i < attriNum; i++){
			if(joinOpeNode[j].leftNode.attributeID == attriRec[i]->attributeID && joinOpeNode[j].leftNode.tableID == attriRec[i]->tableID){
				outerPos[j] = i;
				break;
			}
		}
		assert(i != attriNum);
	}
}
/*		
int HashJoin_old::cmpHashNode(HASH_NODE_OLD *hnp_, unsigned int *posSet_){
	unsigned int i;
	for(i = 0; i < nodeNum; i++)
		if(!(*pv[posSet_[i]] == hnp_->pv[i]))break;	
	
	if(i == nodeNum)return 0;
	return 1;
}
*/
int HashJoin_old::getInnerDataBuffSize(void){
	int size = 0;
	for(unsigned int i = 0 ; i < innerAttriNum; i++){
		size += attriRec[i]->dataLength;
		if(attriRec[i]->dataType == VARIABLE_TEXT)size++;
	}
	return size;
}

int HashJoin_old::getOuterDataBuffSize(void){
	int size = 0;
	for(unsigned int i = innerAttriNum ; i < attriNum; i++){
		size += attriRec[i]->dataLength;
		if(attriRec[i]->dataType == VARIABLE_TEXT)size++;
	}
	return size;
}

unsigned int HashJoin_old::getDataBuffer(char *dataBuffer_, unsigned int dataBufSize_, unsigned int startPos_, unsigned int getNum_)
{
	unsigned int size = 0;
	unsigned int endPos = startPos_ + getNum_;

	for(unsigned int i = startPos_; i < endPos; i++){
		switch(attriRec[i]->dataType){
			case INT:
				assert(size + sizeof(int) <= dataBufSize_);
				memcpy(dataBuffer_ + size, pv[i]->value, sizeof(int));
				size += sizeof(int);
				break;

			case LONG:
				assert(size + sizeof(long) <= dataBufSize_);
				memcpy(dataBuffer_ + size, pv[i]->value, sizeof(long));
				size += sizeof(long);
				break;

			case FLOAT:
				assert(size + sizeof(float) <= dataBufSize_);
				memcpy(dataBuffer_ + size, pv[i]->value, sizeof(float));
				size += sizeof(float);
				break;

			case DOUBLE:	
				assert(size + sizeof(double) <= dataBufSize_);
				memcpy(dataBuffer_ + size, pv[i]->value, sizeof(double));
				size += sizeof(double);
				break;

			case FIXED_TEXT:
				assert(size + attriRec[i]->dataLength <= dataBufSize_);
				memcpy(dataBuffer_ + size, pv[i]->value, attriRec[i]->dataLength);
				size += attriRec[i]->dataLength;
				break;

			case VARIABLE_TEXT:
				assert(size + strlen((char *)pv[i]->value) <= dataBufSize_);
				strcpy(dataBuffer_ + size, (char *)(pv[i]->value));
				size += strlen((char *)(pv[i])->value) + 1;
				break;

			case DATE:
				assert(size + attriRec[i]->dataLength <= dataBufSize_);
				memcpy(dataBuffer_ + size, (char *)pv[i]->value, attriRec[i]->dataLength);
				size += attriRec[i]->dataLength;
				break;

			default:
				cout << "Error insertVoidData" << endl;
				exit (EXIT_FAILURE);
		}
	}
	return size;
}


