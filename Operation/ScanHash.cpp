#include"ScanHash.h"

using namespace std;

ScanHash::ScanHash(BDBOpe *db_, ATTRIBUTE_REC *attriRec_, unsigned int attriNum_){
	assert(db_ != NULL);
	db = db_;
	initFlag = 0;

	initAttriRec(attriNum_);

	for(unsigned int i = 0; i < attriNum_; i++){
		memcpy(attriRec[i], &attriRec_[i], sizeof(ATTRIBUTE_REC));
	}
	attriNum = attriNum_;
}

ScanHash::ScanHash(BDBOpe *db_, ATTRIBUTE_REC **attriRec_, unsigned int attriNum_){
	assert(db_ != NULL);
	db = db_;
	initFlag = 0;

	initAttriRec(attriNum_);

	for(unsigned int i = 0; i < attriNum_; i++){
		memcpy(attriRec[i], attriRec_[i], sizeof(ATTRIBUTE_REC));
	}
	attriNum = attriNum_;
}

ScanHash::~ScanHash(){
	delete[] attriRec;
}

void ScanHash::init(DbEnv *env_){
	env = env_;
}

void ScanHash::resetGetPos(void){
	initFlag = 0;
}

void ScanHash::setHashkey(unsigned int hashkey){
	key.set_size(sizeof(unsigned int));
	key.set_data(&hashkey);
	initFlag = 0;
} 

int ScanHash::getRow(PosVal **pv_, unsigned int pvNum_){
	int returnCode;

	if(initFlag == 0){
		returnCode = db->readDupFirstRecord(&key, &data);
		initFlag = 1;
	}else{
		returnCode = db->readDupNextRecord(&key, &data);
	}

	if(returnCode == DB_NOTFOUND){
		return (-1);
	}
	else if(returnCode != 0){
		cout << "Error ScanHash" << endl;
		exit(-1);
	}
	else{
		setPosVal(pv_, pvNum_);
		return (0);
	}
}

void ScanHash::setPosVal(PosVal **pv_, unsigned int pvNum_){
	unsigned int pos = 0;

	for(unsigned int i=0; i < pvNum_; i++){
		pv_[i]->set((unsigned char *)(data.get_data()) + pos);
		pos += pv_[i]->getSize();
		if(pv_[i]->type == VARIABLE_TEXT)pos++;
	}
}

unsigned int ScanHash::getAttriNum(void){
	return attriNum;
}

void ScanHash::getAttriRec(ATTRIBUTE_REC **attriRec_, unsigned int attriNum_){
	for(unsigned int i = 0; i < attriNum_; i++){
		memcpy(attriRec_[i], attriRec[i], sizeof(ATTRIBUTE_REC));
	}
}

	 
