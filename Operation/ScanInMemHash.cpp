#include"ScanInMemHash.h"

using namespace std;

ScanInMemHash::ScanInMemHash(InMemDB *db_, ATTRIBUTE_REC *attriRec_, unsigned int attriNum_){
	assert(db_ != NULL);
	db = db_;
	initFlag = 0;

	initAttriRec(attriNum_);

	for(unsigned int i = 0; i < attriNum_; i++){
		memcpy(attriRec[i], &attriRec_[i], sizeof(ATTRIBUTE_REC));
	}
	attriNum = attriNum_;
}

ScanInMemHash::ScanInMemHash(InMemDB *db_, ATTRIBUTE_REC **attriRec_, unsigned int attriNum_){
	assert(db_ != NULL);
	db = db_;
	initFlag = 0;

	initAttriRec(attriNum_);

	for(unsigned int i = 0; i < attriNum_; i++){
		memcpy(attriRec[i], attriRec_[i], sizeof(ATTRIBUTE_REC));
	}
	attriNum = attriNum_;
}

ScanInMemHash::~ScanInMemHash(){
	delete[] attriRec;
}

void ScanInMemHash::init(DbEnv *env_){
	env = env_;
}

void ScanInMemHash::resetGetPos(void){
	initFlag = 0;
}

void ScanInMemHash::setHashkey(unsigned int hashkey_){
	hashKey = hashkey_;
	key.set_size(sizeof(unsigned int));
	key.set_data(&hashKey);
	initFlag = 0;
} 

int ScanInMemHash::getRow(PosVal **pv_, unsigned int pvNum_){
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
		cout << "Error ScanInMemHash" << endl;
		exit(-1);
	}
	else{
		setPosVal(pv_, pvNum_);
		return (0);
	}
}

void ScanInMemHash::setPosVal(PosVal **pv_, unsigned int pvNum_){
	unsigned int pos = 0;

	for(unsigned int i=0; i < pvNum_; i++){
		pv_[i]->set((unsigned char *)(data.get_data()) + pos);
		pos += pv_[i]->getSize();
		if(pv_[i]->type == VARIABLE_TEXT)pos++;
	}
}

unsigned int ScanInMemHash::getAttriNum(void){
	return attriNum;
}

void ScanInMemHash::getAttriRec(ATTRIBUTE_REC **attriRec_, unsigned int attriNum_){
	for(unsigned int i = 0; i < attriNum_; i++){
		memcpy(attriRec_[i], attriRec[i], sizeof(ATTRIBUTE_REC));
	}
}

	 
