#include"JoinIndex_OneHash.h"

JoinIndex_OneHash::JoinIndex_OneHash(Operator *innerOpeNode_, Operator *outerOpeNode_){
	innerOpeNode = innerOpeNode_;
	outerOpeNode = outerOpeNode_;
	joinOpeNode = NULL;
	preOperator = NULL;
	nodeNum = 1;
}

JoinIndex_OneHash::JoinIndex_OneHash(Operator *innerOpeNode_, Operator *outerOpeNode_, JOIN_OPERATION_NODE *joinOpeNode_){
	innerOpeNode = innerOpeNode_;
	outerOpeNode = outerOpeNode_;
	joinOpeNode = joinOpeNode_;
	preOperator = NULL;
	nodeNum = 1;
	
}

JoinIndex_OneHash::~JoinIndex_OneHash(){
}

void JoinIndex_OneHash::delHash(){
	innerHash->db->close();
	delete innerHash->db;
	delete innerHash;
}

void JoinIndex_OneHash::init(DbEnv *env_){
	assert(innerOpeNode != NULL &&  outerOpeNode != NULL);
	env = env_;
	innerOpeNode->init(env);
	outerOpeNode->init(env);
	innerAttriNum = innerOpeNode->getAttriNum();
	outerAttriNum = outerOpeNode->getAttriNum();
	attriNum = innerAttriNum + outerAttriNum;
	initAttriRec(attriNum+1);
	attriRec[0]->dataType = INT;
	attriRec[0]->dataLength = sizeof(int);
	
	innerOpeNode->getAttriRec(attriRec+1, innerAttriNum);
	outerOpeNode->getAttriRec(attriRec + innerAttriNum +1, outerAttriNum);
	attriNum++;
	initPosVal();
	attriNum--;
	setJoinPos();

	
	initHash();

	storeInnerNode();
	getRowFlag = 0;
}



int JoinIndex_OneHash::getRow(PosVal **pv_, unsigned int pvNum_){
	int returnCode;
	unsigned int hashkey;
	
	if(getRowFlag == -1){
		return -1;
	}
	
	
	if(getRowFlag == 0){
		returnCode = outerOpeNode->getRow(&pv[innerAttriNum + 1], outerAttriNum);
		if(returnCode != 0){
			delHash();
			getRowFlag = -1;
			return -1;
		}else{
			hashkey = 0;
			for(unsigned int i = 0; i < nodeNum; i++)
				hashkey += hashFunc(pv[outerPos[i]]);
			hashkey = hashkey%HASH_SIZE;
			innerHash->ScanNode->setHashkey(hashkey);
			getRowFlag = 1;
		}
	}
	
	while(1){
		returnCode = innerHash->ScanNode->getRow(pv, innerAttriNum+1);
		if(returnCode == 0){
			unsigned int posIndex;
			for(posIndex = 0; posIndex < nodeNum; posIndex++){
				if(!(*pv[innerPos[posIndex]] == pv[outerPos[posIndex]]))
					break;
			}
			if(posIndex == nodeNum){
				pv[innerPos[0]]->position = *(int *)(pv[0]->value);
				for(unsigned int i=0; i<attriNum; i++){
					*pv_[i] = *pv[i+1];
				}
				return 0;
			}
			continue;
		}

		returnCode = outerOpeNode->getRow(&pv[innerAttriNum + 1], outerAttriNum);
		if(returnCode != 0){
			delHash();
			getRowFlag = -1;
			return -1;
		}else{
			hashkey = 0;
			for(unsigned int i = 0; i < nodeNum; i++)
				hashkey += hashFunc(pv[outerPos[i]]);
			hashkey %= HASH_SIZE;
			innerHash->ScanNode->setHashkey(hashkey);
		}
	}	
}


unsigned int JoinIndex_OneHash::getAttriNum(void){
	return attriNum;
}

void JoinIndex_OneHash::getAttriRec(ATTRIBUTE_REC **attriRec_, unsigned int attriNum_){
	for(unsigned int i = 0; i < attriNum_; i++){
		memcpy(attriRec_[i], attriRec[i+1], sizeof(ATTRIBUTE_REC));
	}
}


void JoinIndex_OneHash::initHash(void){
	
	innerHash = new ONESIDE_INMEM_HASH_NODE;
	tmpnam(tmpFileName);
	innerHash->dbName = tmpFileName;
	innerHash->db = new InMemDB(env, innerHash->dbName, false);
	innerHash->db->open();
	
	innerHash->ScanNode = new ScanInMemHash(innerHash->db, attriRec, innerAttriNum+1);
}

void JoinIndex_OneHash::storeInnerNode(void){
	unsigned int hashkey;
	int returnCode;
	unsigned int dataSize;
	int buffSize = getInnerDataBuffSize();
	char innerDataBuffer[buffSize];

	while(1){
		returnCode = innerOpeNode->getRow(pv+1, innerAttriNum);
		if(returnCode == -1)break;
		hashkey = 0;

		for(unsigned int i = 0; i < nodeNum; i++)
			hashkey += hashFunc(pv[innerPos[i]]);
		hashkey %= HASH_SIZE;

		
		dataSize = getDataBuffer(innerDataBuffer, buffSize, 0 , innerAttriNum);
		innerHash->db->writeRecord(&hashkey, sizeof(hashkey), innerDataBuffer, dataSize, true);
	}
}


void JoinIndex_OneHash::setJoinPos(void){
	innerPos = new unsigned int[1];
	outerPos = new unsigned int[1];
	
	if(joinOpeNode == NULL){
		innerPos[0] = 1;
		outerPos[0] = innerAttriNum + 1;
	}else{
		unsigned int i;
		if((joinOpeNode[0].rightNode.attributeID == 0) && (joinOpeNode[0].rightNode.tableID ==0)){
			innerPos[0] = joinOpeNode[0].rightNode.position;
		}else{
			for(i = 0;i < innerAttriNum+1; i++){
				if(joinOpeNode[0].rightNode.attributeID == attriRec[i]->attributeID && joinOpeNode[0].rightNode.tableID == attriRec[i]->tableID){
					innerPos[0] = i;
					break;
				}
			}
			assert(i != innerAttriNum+1);
		}
		
		if((joinOpeNode[0].leftNode.attributeID == 0) && (joinOpeNode[0].leftNode.tableID ==0)){
			outerPos[0] = joinOpeNode[0].leftNode.position;
		}else{
			for(i = innerAttriNum+1; i < attriNum+1; i++){
				if(joinOpeNode[0].leftNode.attributeID == attriRec[i]->attributeID && joinOpeNode[0].leftNode.tableID == attriRec[i]->tableID){
					outerPos[0] = i;
					break;
				}
			}
			assert(i != attriNum+1);
		}
	}
}


int JoinIndex_OneHash::getInnerDataBuffSize(void){
	int size = 0;
	for(unsigned int i = 0 ; i < innerAttriNum; i++){
		size += attriRec[i+1]->dataLength;
		if(attriRec[i+1]->dataType == VARIABLE_TEXT)size++;
	}
	size += sizeof(unsigned int);
	return size;
}


unsigned int JoinIndex_OneHash::getDataBuffer(char *dataBuffer_, unsigned int dataBufSize_, unsigned int startPos_, unsigned int getNum_)
{
	unsigned int size = 0;
	unsigned int endPos = startPos_ + getNum_;

	/*position　情報をバッファの先頭に格納*/
	*(unsigned int *)(dataBuffer_) = pv[innerPos[0]]->position;
	size += sizeof(unsigned int);

	for(unsigned int i = startPos_ + 1; i < endPos + 1; i++){
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


