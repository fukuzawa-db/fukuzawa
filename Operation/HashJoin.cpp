#include"HashJoin.h"

HashJoin::HashJoin(Operator *innerOpeNode_, Operator *outerOpeNode_, JOIN_OPERATION_NODE *joinOpeNode_, unsigned int nodeNum_){
	innerOpeNode = innerOpeNode_;
	outerOpeNode = outerOpeNode_;
	preOperator = NULL;
	joinOpeNode = joinOpeNode_;
	nodeNum = nodeNum_;
}

HashJoin::~HashJoin(){
}

void HashJoin::delHash(void){
	delete innerHash->ScanNode;
	innerHash->db->close();
	delete innerHash->db;
	delete innerHash;
	
	delete outerHash->ScanNode;
	outerHash->db->close();
	delete outerHash->db;
	delete outerHash;
}

void HashJoin::init(DbEnv *env_){
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
	initHash();
	storeInnerNode();
	storeOuterNode();
	getRowFlag = 0;
}


int HashJoin::getRow(PosVal **pv_, unsigned int pvNum_){
	int returnCode;

	if(getRowFlag == 0){
		searchHashkey = 0;
		while(1){
			if(searchHashkey == HASH_SIZE){
				getRowFlag = -1;
				delHash();
				return -1;
			}
			outerHash->ScanNode->setHashkey(searchHashkey);
			returnCode = outerHash->ScanNode->getRow(&pv[innerAttriNum], outerAttriNum);
			if(returnCode == 0){
				innerHash->ScanNode->setHashkey(searchHashkey);
				searchHashkey++;
				getRowFlag = 1;
				break;
			}
			searchHashkey++;
		}
	}

	if(getRowFlag == -1){
		return -1;
	}

	while(1){
		returnCode = innerHash->ScanNode->getRow(pv, innerAttriNum);
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
			continue;
		}
		
		returnCode = outerHash->ScanNode->getRow(&pv[innerAttriNum], outerAttriNum);
		if(returnCode == 0){
			innerHash->ScanNode->setHashkey(searchHashkey-1);
			continue;
		}		
		
		while(1){	
			if(searchHashkey == HASH_SIZE){
				getRowFlag = -1;
				delHash();
				return -1;
			}
			outerHash->ScanNode->setHashkey(searchHashkey);
			returnCode = outerHash->ScanNode->getRow(&pv[innerAttriNum], outerAttriNum);
			if(returnCode == 0){
				innerHash->ScanNode->setHashkey(searchHashkey);
				searchHashkey++;
				break;
			}
			searchHashkey++;
		}
	}
}


unsigned int HashJoin::getAttriNum(void){
	return attriNum;
}

void HashJoin::getAttriRec(ATTRIBUTE_REC **attriRec_, unsigned int attriNum_){
	for(unsigned int i = 0; i < attriNum_; i++){
		memcpy(attriRec_[i], attriRec[i], sizeof(ATTRIBUTE_REC));
	}
}


void HashJoin::storeInnerNode(void){
	unsigned int hashkey;
	int returnCode;
	unsigned int dataSize;
	int buffSize = getInnerDataBuffSize();
	char innerDataBuffer[buffSize];

	while(1){
		returnCode = innerOpeNode->getRow(pv, innerAttriNum);
		if(returnCode == -1)break;
		hashkey = 0;
		for(unsigned int i = 0; i < nodeNum; i++)
			hashkey += hashFunc(pv[innerPos[i]]);
		hashkey %= HASH_SIZE;
		
		dataSize = getDataBuffer(innerDataBuffer, buffSize, 0 , innerAttriNum);
		innerHash->db->writeRecord(&hashkey, sizeof(hashkey), innerDataBuffer, dataSize, true);
	}
}

void HashJoin::storeOuterNode(void){
	unsigned int hashkey;
	int returnCode;
	unsigned int dataSize;
	int buffSize = getOuterDataBuffSize();
	char outerDataBuffer[buffSize];

	while(1){
		returnCode = outerOpeNode->getRow(&pv[innerAttriNum], outerAttriNum);
		if(returnCode == -1)break;
		hashkey = 0;
		for(unsigned int i = 0; i < nodeNum; i++)
			hashkey += hashFunc(pv[outerPos[i]]);
		hashkey %= HASH_SIZE;

		dataSize = getDataBuffer(outerDataBuffer, buffSize, innerAttriNum, outerAttriNum);
		outerHash->db->writeRecord(&hashkey, sizeof(hashkey), outerDataBuffer, dataSize, true);
	}
}


void HashJoin::initHash(void){
	innerHash = new HASH_INMEM_NODE;
	if(tmpnam(tmpFileName) == NULL){
		cerr << "HashJoin : Can't create FILE" << endl;
	}
	innerHash->dbName = tmpFileName;
	innerHash->db = new InMemDB(env, innerHash->dbName, false);
	innerHash->db->open();
	innerHash->ScanNode = new ScanInMemHash(innerHash->db, attriRec, innerAttriNum);
	
	outerHash = new HASH_INMEM_NODE;
	if(tmpnam(tmpFileName) == NULL){
		cerr << "HashJoin : Can't create FILE" << endl;
	}
	outerHash->dbName = tmpFileName;
	outerHash->db = new InMemDB(env, outerHash->dbName, false);
	outerHash->db->open();
	outerHash->ScanNode = new ScanInMemHash(outerHash->db, attriRec+innerAttriNum, outerAttriNum);
}


void HashJoin::setJoinPos(void){
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


int HashJoin::getInnerDataBuffSize(void){
	int size = 0;
	for(unsigned int i = 0 ; i < innerAttriNum; i++){
		size += attriRec[i]->dataLength;
		if(attriRec[i]->dataType == VARIABLE_TEXT)size++;
	}
	return size;
}

int HashJoin::getOuterDataBuffSize(void){
	int size = 0;
	for(unsigned int i = innerAttriNum ; i < attriNum; i++){
		size += attriRec[i]->dataLength;
		if(attriRec[i]->dataType == VARIABLE_TEXT)size++;
	}
	return size;
}

unsigned int HashJoin::getDataBuffer(char *dataBuffer_, unsigned int dataBufSize_, unsigned int startPos_, unsigned int getNum_)
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


