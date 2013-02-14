#include"NestedJoin.h"

NestedJoin::NestedJoin(Operator *innerOpeNode_, Operator *outerOpeNode_, JOIN_OPERATION_NODE *joinOpeNode_, unsigned int nodeNum_){
	innerOpeNode = innerOpeNode_;
	outerOpeNode = outerOpeNode_;
	preOperator = NULL;
	joinOpeNode = joinOpeNode_;
	nodeNum = nodeNum_;
}

NestedJoin::~NestedJoin(){
	//delete innerScanNode;
	db->close();
	db->remove();
	delete db;
}


void NestedJoin::init(DbEnv *env_){
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

	storeInnerNode();
	setJoinPos();
	innerScanNode = new Scan(db, attriRec, innerAttriNum);
	getRowFlag = 0;
}

int NestedJoin::getRow(PosVal **pv_, unsigned int pvNum_){
	int returnCode;
	unsigned int i;

	if(getRowFlag == 0){
		returnCode = outerOpeNode->getRow(&pv[innerAttriNum], outerAttriNum);
		if(returnCode == 0)
			getRowFlag = 1;
		else
			getRowFlag = -1;
	}
	if(getRowFlag == -1){
		return -1;
	}

	while(1){
		returnCode = 2;
		returnCode = innerScanNode->getRow(pv, innerAttriNum);
		if(returnCode != 0){
			returnCode = outerOpeNode->getRow(&pv[innerAttriNum], outerAttriNum);
			if(returnCode != 0){
				getRowFlag = -1;
				return(-1);
			}
			innerScanNode->resetGetPos();
			returnCode = innerScanNode->getRow(pv, innerAttriNum);
		}
		for(i = 0; i < nodeNum; i++){
			if(*pv[innerPos[i]] != pv[outerPos[i]])break;
		}
		if(i == nodeNum){
			for(i = 0; i < attriNum; i++)
				*pv_[i] = *pv[i];
			return 0;
		}
	}	
}

unsigned int NestedJoin::getAttriNum(void){
	return attriNum;
}

void NestedJoin::getAttriRec(ATTRIBUTE_REC **attriRec_, unsigned int attriNum_){
	for(unsigned int i = 0; i < attriNum_; i++){
		memcpy(attriRec_[i], attriRec[i], sizeof(ATTRIBUTE_REC));
	}
}


void NestedJoin::setJoinPos(void){
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
		

void NestedJoin::storeInnerNode(void){
	if(tmpnam(tmpFileName) == NULL){
		cerr << "NestedJoin : Can't create FILE" << endl;
	}
	fileName = tmpFileName;
	db = new BDBOpe(env, fileName);
	db->open();

	int buffSize = getInnerDataBuffSize();
	char innerDataBuffer[buffSize];
	int returnCode;
	unsigned int dataSize;
	unsigned int key = 1;
	
	while(1){
		returnCode = innerOpeNode->getRow(pv, innerAttriNum);
		if(returnCode == -1)break;
		
		dataSize = getInnerDataBuffer(innerDataBuffer, buffSize);
		db->writeRecord(&key, sizeof(key), innerDataBuffer, dataSize, false);
		key++;
	}
}


int NestedJoin::getInnerDataBuffSize(void){
	int size = 0;
	for(unsigned int i = 0 ; i < innerAttriNum; i++){
		size += attriRec[i]->dataLength;
		if(attriRec[i]->dataType == VARIABLE_TEXT)size++;
	}
	return size;
}


unsigned int NestedJoin::getInnerDataBuffer(char *dataBuffer_, unsigned int dataBufSize_)
{
	unsigned int size = 0;

	for(int i = 0; i < (int)innerAttriNum; i++){
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

