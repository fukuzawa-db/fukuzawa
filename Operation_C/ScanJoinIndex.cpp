#include"ScanJoinIndex.h"

using namespace std;

ScanJoinIndex::ScanJoinIndex(BDBOpe *db_, ATTRIBUTE_REC *attriRec_, unsigned int attriNum_){
	assert(db_ != NULL);
	db = db_;
	initFlag = 0;

	initAttriRec(attriNum_);

	for(unsigned int i = 0; i < attriNum_; i++){
		memcpy(attriRec[i], &attriRec_[i], sizeof(ATTRIBUTE_REC));
	}
	attriNum = attriNum_;
}

ScanJoinIndex::ScanJoinIndex(BDBOpe *db_, ATTRIBUTE_REC **attriRec_, unsigned int attriNum_){
	assert(db_ != NULL);
	db = db_;
	initFlag = 0;
	initKeyFlag = 0;
	preKey = 0;

	initAttriRec(attriNum_);

	for(unsigned int i = 0; i < attriNum_; i++){
		memcpy(attriRec[i], attriRec_[i], sizeof(ATTRIBUTE_REC));
	}
	attriNum = attriNum_;
}

ScanJoinIndex::~ScanJoinIndex(){
	delete[] attriRec;
}

void ScanJoinIndex::init(DbEnv *env_){
	env = env_;
}

void ScanJoinIndex::resetGetPos(void){
	initFlag = 0;
}

void ScanJoinIndex::setkey(unsigned int key_){
	key.set_size(sizeof(unsigned int));
	key.set_data(&key_);
	initFlag = 0;
} 

int ScanJoinIndex::getRow(PosVal **pv_, unsigned int pvNum_){
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
		//setPosVal(pv_, pvNum_);
		return (*(unsigned int *)data.get_data());
	}
}



int ScanJoinIndex::getKey(void){
	int returnCode;
	while(1){
		if(initKeyFlag == 0){
			returnCode = db->readFirstRecord(&key, &data);
			initKeyFlag = 1;
		}else{
			returnCode = db->readNextRecord(&key, &data);
		}

		if(returnCode == DB_NOTFOUND){
			return (-1);
		}
		else if(returnCode != 0){
			cout << "Error ScanHash" << endl;
			exit(-1);
		}
		else{
			if(preKey == *(unsigned int *)key.get_data())continue;
			preKey = *(unsigned int *)key.get_data();
			return (*(unsigned int *)key.get_data());
		}
	}
}

int ScanJoinIndex::getData(unsigned int *key_, unsigned int *data_){
	int returnCode;
	while(1){
		if(initKeyFlag == 0){
			returnCode = db->readFirstRecord(&key, &data);
			initKeyFlag = 1;
		}else{
			returnCode = db->readNextRecord(&key, &data);
		}

		if(returnCode == DB_NOTFOUND){
			return (-1);
		}
		else if(returnCode != 0){
			cout << "Error ScanHash" << endl;
			exit(-1);
		}
		else{
			*key_ = *(unsigned int *)key.get_data();
			*data_ = *(unsigned int *)data.get_data();
			return 0;
		}
	}
}


/*
void ScanHash::setPosVal(PosVal **pv_, unsigned int pvNum_){
	unsigned int pos = 0;

	for(unsigned int i=0; i < pvNum_; i++){
		pv_[i]->set((unsigned char *)(data.get_data()) + pos);
		pos += pv_[i]->getSize();
		if(pv_[i]->type == VARIABLE_TEXT)pos++;
	}
}
*/
unsigned int ScanJoinIndex::getAttriNum(void){
	return attriNum;
}

void ScanJoinIndex::getAttriRec(ATTRIBUTE_REC **attriRec_, unsigned int attriNum_){
	for(unsigned int i = 0; i < attriNum_; i++){
		memcpy(attriRec_[i], attriRec[i], sizeof(ATTRIBUTE_REC));
	}
}

	 
