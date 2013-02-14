#include"JoinFromJoinIndex.h"

JoinFromJoinIndex::JoinFromJoinIndex(Operator *innerOpeNode_, Operator *outerOpeNode_, JOIN_INDEX *joinIndex_, JOIN_OPERATION_NODE *joinOpeNode_){
	innerOpeNode = innerOpeNode_;
	outerOpeNode = outerOpeNode_;
	joinIndex = joinIndex_;
	joinOpeNode = joinOpeNode_;
	preOperator = NULL;
}


JoinFromJoinIndex::~JoinFromJoinIndex(){
}

void JoinFromJoinIndex::init(DbEnv *env_){
	env = env_;
	assert(innerOpeNode != NULL &&  outerOpeNode != NULL);
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
	
	initTmp();
	storeInnerNode();

	getRowFlag = 0;
}



int JoinFromJoinIndex::getRow(PosVal **pv_, unsigned int pvNum_)
{
	int returnCode;

	if(getRowFlag == -1){
		return (-1);
	}
	if(getRowFlag == 0){
		returnCode = outerOpeNode->getRow(&pv[innerAttriNum], outerAttriNum);
		if(returnCode == DB_NOTFOUND){
			getRowFlag = -1;
			return (-1);
		}
		if(returnCode != 0){
			cout << "Error : JoinFromJoinIndex" << endl;
			exit(-1);
		}

		outerIndex = pv[outerPos]->position;
		joinIndex->ScanNode->setkey(outerIndex);
		currentPos = 1;
		getRowFlag = 1;
	}
		
	while(1){
		innerIndex = joinIndex->ScanNode->getRow(pv, 0);
		
		if(innerIndex > 0){
			do{
				returnCode = innerTmp->ScanNode->getRowKey(pv, innerAttriNum);
				if(returnCode < 0){
					cout << "Error : JoinFromJoinIndex" << endl;
					exit(-1);
				}
			}while(returnCode != innerIndex);
			
			for(unsigned int i = 0; i < attriNum; i++) *pv_[i] = *pv[i];
			return 0;
		}
		returnCode = outerOpeNode->getRow(&pv[innerAttriNum], outerAttriNum);
		if(returnCode != 0){
			getRowFlag = -1;
			return -1;
		}else{
			outerIndex = pv[outerPos]->position;
			innerTmp->ScanNode->resetGetPos();
			joinIndex->ScanNode->setkey(outerIndex);
			currentPos = 1;
		}
	}
}		
		

void JoinFromJoinIndex::setJoinPos(void){
	unsigned int i;
	
	if(joinOpeNode[0].rightNode.attributeID == 0 && joinOpeNode[0].rightNode.tableID == 0){
		innerPos = joinOpeNode[0].rightNode.position;
	}else{
		for(i = 0;i < innerAttriNum; i++){
			if(joinOpeNode[0].rightNode.attributeID == attriRec[i]->attributeID && joinOpeNode[0].rightNode.tableID == attriRec[i]->tableID){
				innerPos = i;
				break;
			}
		}
		assert(i != innerAttriNum);
	}
	
	if(joinOpeNode[0].leftNode.attributeID == 0 && joinOpeNode[0].leftNode.tableID == 0){
		outerPos = joinOpeNode[0].leftNode.position;
	}else{
		for(i = innerAttriNum; i < attriNum; i++){
			if(joinOpeNode[0].leftNode.attributeID == attriRec[i]->attributeID && joinOpeNode[0].leftNode.tableID == attriRec[i]->tableID){
				outerPos = i;
				break;
			}
		}
		assert(i != attriNum);
	}
}


unsigned int JoinFromJoinIndex::getAttriNum(void){
	return attriNum;
}

void JoinFromJoinIndex::getAttriRec(ATTRIBUTE_REC **attriRec_, unsigned int attriNum_){
	for(unsigned int i = 0; i < attriNum_; i++){
		memcpy(attriRec_[i], attriRec[i], sizeof(ATTRIBUTE_REC));
	}
}


void JoinFromJoinIndex::initTmp(void){
	innerTmp = new TMP_NODE;
	tmpnam(tmpFileName);
	innerTmp->dbName = tmpFileName;
	innerTmp->db = new BDBOpe(env, innerTmp->dbName, true);
	innerTmp->db->open();
	innerTmp->ScanNode = new Scan(innerTmp->db, attriRec, innerAttriNum);
}



void JoinFromJoinIndex::storeInnerNode(void){
	unsigned int hashkey;
	int returnCode;
	unsigned int dataSize;
	int buffSize = getInnerDataBuffSize();
	char innerDataBuffer[buffSize];

	while(1){
		returnCode = innerOpeNode->getRow(pv, innerAttriNum);
		if(returnCode == -1)break;
		hashkey = pv[innerPos]->position;
		
		dataSize = getDataBuffer(innerDataBuffer, buffSize, 0 , innerAttriNum);
		innerTmp->db->writeRecord(&hashkey, sizeof(hashkey), innerDataBuffer, dataSize, true);
	}
}


int JoinFromJoinIndex::getInnerDataBuffSize(void){
	int size = 0;
	for(unsigned int i = 0 ; i < innerAttriNum; i++){
		size += attriRec[i]->dataLength;
		if(attriRec[i]->dataType == VARIABLE_TEXT)size++;
	}
	return size;
}


unsigned int JoinFromJoinIndex::getDataBuffer(char *dataBuffer_, unsigned int dataBufSize_, unsigned int startPos_, unsigned int getNum_)
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


