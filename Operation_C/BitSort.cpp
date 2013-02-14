#include "BitSort.h"


BitSort::BitSort(){
}

BitSort::~BitSort(){
	delete joinIndex;
	delete JoinDSM;
}


void BitSort::init(DbEnv *env_){
	assert(preOperator != NULL);
	preOperator->init(env);
	attriNum = preOperator->getAttriNum();
	initAttriRec(attriNum);
	preOperator->getAttriRec(attriRec, attriNum);
	setData();
	initFlag = true;
}


void BitSort::setData(void){
	openJoinIndex();
	openTmpFile();
	maxNum = 0;

	int returnCode1, returnCode2;
	unsigned int bitBuf, setBuf;

	while(1){
		returnCode1 = preOperator->getRow(NULL, 0);
		returnCode2 = JoinDSM->getRow(&indexPV, 1);
	
		if(returnCode1 == -1 || returnCode2 == -1){
			if(returnCode1 == returnCode2)break;
			cout << "ERROR No match returnCode" << endl;
			exit(-1);
		}
		if(returnCode1 == 1){
			fseek(fp, setByte(*(int *)indexPV->value), SEEK_SET);
			if(!fread(&bitBuf, sizeof(unsigned int), 1, fp)){
				bitBuf = 0x00000000;
			}


			setBuf = (0x01 << setBit(*(unsigned int *)indexPV->value));
			bitBuf |= setBuf;
		
			fseek(fp, setByte(*(unsigned int *)indexPV->value), SEEK_SET);
			fwrite(&bitBuf, sizeof(unsigned int), 1, fp);
		}
		maxNum++;
	}
}




/*
void BitSort::setData(void){
	openJoinIndex();
	openTmpFile();
	maxNum = 0;

	int returnCode1, returnCode2;
	unsigned int bitBuf, setBuf;

	while(1){
		returnCode1 = preOperator->getRow(NULL, 0);
		returnCode2 = JoinDSM->getRow(&indexPV, 1);
	
		if(returnCode1 == -1 || returnCode2 == -1){
			if(returnCode1 == returnCode2)break;
			cout << "ERROR No match returnCode" << endl;
			exit(-1);
		}
		if(returnCode1 == 1){
			fseek(fp, setByte(*(int *)indexPV->value), SEEK_SET);
			c0 = fgetc(fp);
			if(c0 == EOF){
				c0 = 0x0000;
				c1 = 0x0000;
				c2 = 0x0000;
				c3 = 0x0000;
			}else{
				c1 = fgetc(fp);
				c2 = fgetc(fp);
				c3 = fgetc(fp);
			}
			bitBuf = ((c3 & 0xff) << (8 * 3)) | ((c2 & 0xff) << (8 * 2)) | ((c1 & 0xff) << (8 * 1)) | ((c0 & 0xff) << (8 * 0));
			
			cout << *(int *)indexPV->value << endl;

			setBuf = (0x00000001 << setBit(*(int *)indexPV->value));
			if(returnCode1 == 0){
				bitBuf &= ~setBuf;
			}else{
				bitBuf |= setBuf;
			}

			c0 = (bitBuf >> 8 * 0) | 0xff;
			c1 = (bitBuf >> 8 * 1) | 0xff;
			c2 = (bitBuf >> 8 * 2) | 0xff;
			c3 = (bitBuf >> 8 * 3) | 0xff;
		
			fseek(fp, setByte(*(int *)indexPV->value), SEEK_SET);
			if(!(fputc(c0, fp) != EOF && fputc(c1, fp) != EOF && fputc(c2, fp) != EOF && fputc(c3, fp)!= EOF)){
				cout << "ERROR fputc" << endl;
				exit(-1);
			}
		}
		maxNum++;
	}
	trancate(fp, 
}
*/
void BitSort::openJoinIndex(void){
	tableID = attriRec[0]->tableID;
	attriID = attriRec[0]->attributeID;

	char buf[256];
	sprintf(buf, "%d.%d-to-%d.0.JoinIndex", tableID, attriID, tableID);
	indexFile = buf;

	//cout << indexFile << endl;
	
	joinIndex = new BDBOpe(env, indexFile);
	joinIndex->open();
	 
	JoinAttriRec.dataType = INT;
	JoinAttriRec.dataLength = 4;
	JoinDSM = new ScanDSM(joinIndex, &JoinAttriRec, 1);
	indexPV = new IntPosVal;
}

void BitSort::openTmpFile(void){
	fp = tmpfile();
	if(fp == NULL){
		cout << "ERROR : Can't open tmpfile\n";
	}
}


int BitSort::getRow(PosVal **pv_, unsigned int pvNum_){
	if(initFlag == true){
		rewind(fp);
		readNum = 0;
		initFlag = false;
	}
	if(!(readNum <maxNum)){
		return -1;
	}

	if(readNum % (8 * 4) == 0){
		if(!fread(&readBuf, sizeof(int), 1, fp)){
			readBuf = 0;
		}
	}
	returnValue = (readBuf >> (readNum % (8 * 4))) & 0x00000001;
	assert(returnValue == 0 || returnValue == 1);
	readNum++;
	return returnValue;
}



/*
int BitSort::getRow(PosVal **pv_, unsigned int pvNum_){
	if(initFlag == true){
		rewind(fp);
		readNum = 0;
		initFlag = false;
	}
	if(!(readNum <maxNum)){
		return -1;
	}

	if(readNum % (8 * 4) == 0){
		c0 = fgetc(fp);
		c1 = fgetc(fp);
		c2 = fgetc(fp);
		c3 = fgetc(fp);
		if(c0 == EOF || c1 == EOF || c2 == EOF || c3 == EOF){
			cout << "EROOR fgetc" << endl;
			exit(1);
		}
		readBuf = ((c3 & 0xff) << (8 * 3)) | ((c2 & 0xff) << (8 * 2)) | ((c1 & 0xff) << (8 * 1)) | ((c0 & 0xff) << (8 * 0));
	
	}
	returnValue = (readBuf >> (readNum % (8 * 4))) & 0x00000001;
	assert(returnValue == 0 || returnValue == 1);
	readNum++;
	return returnValue;
}
*/

unsigned int BitSort::getAttriNum(){
	return attriNum;
}

void BitSort::getAttriRec(ATTRIBUTE_REC ** attriRec_, unsigned int attriNum_){
	for(unsigned int i = 0; i < attriNum; i++){
		memcpy(attriRec_+i, attriRec+i, sizeof(ATTRIBUTE_REC));
	}
}
