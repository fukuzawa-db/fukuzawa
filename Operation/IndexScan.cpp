#include"IndexScan.h"

using namespace std;

IndexScan::IndexScan(BDBOpe *db_, ATTRIBUTE_REC *attriRec_, unsigned int attriNum_){
	assert(db_ != NULL);
	db = db_;
	attriNum = attriNum_;
	initAttriRec(attriNum);
	
	for(unsigned int i = 0; i < attriNum; i++){
		memcpy(attriRec[i], &attriRec_[i], sizeof(ATTRIBUTE_REC));
	}
}

IndexScan::~IndexScan(){
	delete[] attriRec;
}

void IndexScan::init(DbEnv *env_){
	env = env_;
}

void IndexScan::keySet(PosVal *skey_){
	key.set_data(skey_->value);
	key.set_size(skey_->getSize());
	initFlag = 0;
	getFlag = 0;
}

int IndexScan::getRow(PosVal **pv_, unsigned int pvNum_){
	int returnCode;

	if(getFlag == -1){
		return (-1);
	}
	

	if(initFlag == 0){
		returnCode = db->readDupFirstRecord(&key, &data);
		//returnCode = db->readFirstRecord(&key, &data);
		initFlag = 1;
	}else{
		returnCode = db->readDupNextRecord(&key, &data);
		//returnCode = db->readNextRecord(&key, &data);
	}


	if(returnCode == DB_NOTFOUND){
		getFlag = -1;
		return (-1);
	}
	else if(returnCode != 0){
		cout << "Error Scan" << endl;
		exit(-1);
	}
	else{
		setPosVal(pv_, pvNum_);
		return 0;
	}
}


void IndexScan::setPosVal(PosVal **pv_, unsigned int pvNum_){
	unsigned int pos = 0;

	for(unsigned int i=0; i < pvNum_; i++){
		pv_[i]->set((unsigned char *)(data.get_data()) + pos);
		pos += pv_[i]->getSize();
		if(pv_[i]->type == VARIABLE_TEXT)pos++;
	}
}


unsigned int IndexScan::getAttriNum(void){
	return attriNum;
}

void IndexScan::getAttriRec(ATTRIBUTE_REC **attriRec_, unsigned int attriNum_){
	for(unsigned int i = 0; i < attriNum_; i++){
		memcpy(attriRec_[i], attriRec[i], sizeof(ATTRIBUTE_REC));
	}
}

