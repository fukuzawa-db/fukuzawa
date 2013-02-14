#include"IndexScanDSM.h"

IndexScanDSM::IndexScanDSM(BDBOpe *db_, PosVal *skey_, ATTRIBUTE_REC *attriRec_, unsigned int attriNum_){
	assert(db_ != NULL);
	db = db_;
	skey = skey_;
	attriNum = attriNum_;
	initAttriRec(attriNum);
	
	for(unsigned int i = 0; i < attriNum; i++){
		memcpy(attriRec[i], &attriRec_[i], sizeof(ATTRIBUTE_REC));
	}
}

IndexScanDSM::~IndexScanDSM(){
	delete[] attriRec;
}

void IndexScanDSM::init(DbEnv *env_){
	env = env_;
	key.set_data(skey->value);
	key.set_size(skey->getSize());
}

int IndexScanDSM::getRow(PosVal **pv_, unsigned int pvNum_){
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
		return (0);
	}
}


void IndexScanDSM::setPosVal(PosVal **pv_, unsigned int pvNum_){
	*pv_[0] = *skey;
	pv_[0]->position = *(unsigned int *)(data.get_data()) ;
}


unsigned int IndexScanDSM::getAttriNum(void){
	return attriNum;
}

void IndexScanDSM::getAttriRec(ATTRIBUTE_REC **attriRec_, unsigned int attriNum_){
	for(unsigned int i = 0; i < attriNum_; i++){
		memcpy(attriRec_[i], attriRec[i], sizeof(ATTRIBUTE_REC));
	}
}
