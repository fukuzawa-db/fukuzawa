#include"Scan.h"

using namespace std;

Scan::Scan(BDBOpe *db_, ATTRIBUTE_REC *attriRec_, unsigned int attriNum_){
	assert(db_ != NULL);
	db = db_;
	initFlag = 0;
	getFlag = 0;
	attriNum = attriNum_;
	initAttriRec(attriNum);

	for(unsigned int i = 0; i < attriNum; i++){
		memcpy(attriRec[i], &attriRec_[i], sizeof(ATTRIBUTE_REC));
	}
}

Scan::Scan(BDBOpe *db_, ATTRIBUTE_REC **attriRec_, unsigned int attriNum_){
	assert(db_ != NULL);
	db = db_;
	initFlag = 0;
	getFlag = 0;
	attriNum = attriNum_;
	initAttriRec(attriNum);
	
	for(unsigned int i = 0; i < attriNum_; i++){
		memcpy(attriRec[i], attriRec_[i], sizeof(ATTRIBUTE_REC));
	}
}

Scan::~Scan(){
	delete[] attriRec;
}

void Scan::init(DbEnv *env_){
	env = env_;
}

void Scan::resetGetPos(void){
	initFlag = 0;
	getFlag = 0;
}

int Scan::getRow(PosVal **pv_, unsigned int pvNum_){
	int returnCode;

	if(getFlag == -1){
#ifdef SanTime
	t.showTime("Snac");
#endif
		return (-1);
	}
	
#ifdef SanTime
	t.start();
#endif

	if(initFlag == 0){
		returnCode = db->readFirstRecord(&key, &data);
		initFlag = 1;
	}else{
		returnCode = db->readNextRecord(&key, &data);
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
#ifdef SanTime
	t.stop();
#endif
		return (0);
	}
}

int Scan::getRowKey(PosVal **pv_, unsigned int pvNum_){
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
		cout << "Error Scan" << endl;
		exit(-1);
	}
	else{
		setPosVal(pv_, pvNum_);
		return *(int *)key.get_data();
	}
}

void Scan::setPosVal(PosVal **pv_, unsigned int pvNum_){
	unsigned int pos = 0;

	for(unsigned int i=0; i < pvNum_; i++){
		pv_[i]->set((unsigned char *)(data.get_data()) + pos);
		pos += pv_[i]->getSize();
		if(pv_[i]->type == VARIABLE_TEXT)pos++;
	}
}

unsigned int Scan::getAttriNum(void){
	return attriNum;
}

void Scan::getAttriRec(ATTRIBUTE_REC **attriRec_, unsigned int attriNum_){
	for(unsigned int i = 0; i < attriNum_; i++){
		memcpy(attriRec_[i], attriRec[i], sizeof(ATTRIBUTE_REC));
	}
}

	 
