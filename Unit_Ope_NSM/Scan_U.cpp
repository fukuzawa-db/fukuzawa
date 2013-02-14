#include"Scan_U.h"

using namespace std;

Scan_U::Scan_U(BDBOpe *db_, ATTRIBUTE_REC *attriRec_, unsigned int attriNum_){
	assert(db_ != NULL);
	db = db_;
	initFlag = 0;
	getFlag = 0;
	attriNum = attriNum_;
	initAttriRec(attriNum);

	for(unsigned int i = 0; i < attriNum; i++){
		memcpy(attriRec[i], &attriRec_[i], sizeof(ATTRIBUTE_REC));
	}
	num = GET_NSM_DATA;
	loop = 1;
}


Scan_U::Scan_U(BDBOpe *db_, ATTRIBUTE_REC *attriRec_, unsigned int attriNum_, unsigned int num_){
	assert(db_ != NULL);
	db = db_;
	initFlag = 0;
	getFlag = 0;
	attriNum = attriNum_;
	initAttriRec(attriNum);

	for(unsigned int i = 0; i < attriNum; i++){
		memcpy(attriRec[i], &attriRec_[i], sizeof(ATTRIBUTE_REC));
	}
	num = num_;
	loop = 1;
}


Scan_U::Scan_U(BDBOpe *db_, ATTRIBUTE_REC *attriRec_, unsigned int attriNum_, unsigned int num_, unsigned int loop_){
	assert(db_ != NULL);
	db = db_;
	initFlag = 0;
	getFlag = 0;
	attriNum = attriNum_;
	initAttriRec(attriNum);

	for(unsigned int i = 0; i < attriNum; i++){
		memcpy(attriRec[i], &attriRec_[i], sizeof(ATTRIBUTE_REC));
	}
	num = num_;
	loop = loop_;
}


Scan_U::~Scan_U(){
	delete[] attriRec;
}

void Scan_U::init(DbEnv *env_){
	env = env_;
	//storeData();
}

void Scan_U::resetGetPos(void){
	bufferPoint = 0;
	getFlag = 0;
}

void Scan_U::storeData(void){
	int returnCode;
	storePosVal = new PosVal**[num];

	for(unsigned int i=0; i<num; i++){
		if(initFlag == 0){
			returnCode = db->readFirstRecord(&key, &data);
			initFlag = 1;
		}else{
			returnCode = db->readNextRecord(&key, &data);
		}

		if(returnCode == DB_NOTFOUND){
			getFlag = -1;
			break;
		}
		else if(returnCode != 0){
			cout << "Error Scan_U" << endl;
			exit(-1);
		}
		else{
			initPosVal(storePosVal[i]);
			setPosVal(storePosVal[i], attriNum);
		}
	}
	bufferPoint = 0;	
}

int Scan_U::getRow(PosVal **pv_, unsigned int pvNum_){

	if(getFlag == -1){
		return (-1);
	}
	if(bufferPoint >= num){
		getFlag = -1;
		return(-1);
	}
	
	for(int i=0; i<(int)pvNum_; i++){
		*pv_[i] = *(storePosVal[bufferPoint][i]);
	}
	bufferPoint++;
	
	if(bufferPoint >= num && loop > 1){
		loop--;
		resetGetPos();
	}
	return (0);
}

int Scan_U::getRowKey(PosVal **pv_, unsigned int pvNum_){
	int returnCode;

	if(initFlag == 0){
		returnCode = db->readFirstRecord(&key, &data);
		initFlag = 1;
	}else{
		returnCode = db->readNextRecord(&key, &data);
	}

	if(returnCode == DB_NOTFOUND){
		return (-1);
	}
	else if(returnCode != 0){
		cout << "Error Scan_U" << endl;
		exit(-1);
	}
	else{
		setPosVal(pv_, pvNum_);
		return *(int *)key.get_data();
	}
}

void Scan_U::setPosVal(PosVal **pv_, unsigned int pvNum_){
	unsigned int pos = 0;

	for(unsigned int i=0; i < pvNum_; i++){
		pv_[i]->set((unsigned char *)(data.get_data()) + pos);
		pos += pv_[i]->getSize();
		if(pv_[i]->type == VARIABLE_TEXT)pos++;
	}
}

unsigned int Scan_U::getAttriNum(void){
	return attriNum;
}

void Scan_U::getAttriRec(ATTRIBUTE_REC **attriRec_, unsigned int attriNum_){
	for(unsigned int i = 0; i < attriNum_; i++){
		memcpy(attriRec_[i], attriRec[i], sizeof(ATTRIBUTE_REC));
	}
}

	 
