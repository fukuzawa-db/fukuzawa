#include"KeyIndex.h"

KeyIndex::KeyIndex(BDBOpe *db_, Operator *keyOpe_, ATTRIBUTE_REC *attriRec_, unsigned int attriNum_){
	assert(db_ != NULL);
	db = db_;
	preOperator = keyOpe_;
	attriNum = attriNum_;
	initAttriRec(attriNum+1);
	
	for(unsigned int i = 0; i < attriNum; i++){
		memcpy(attriRec[i], &attriRec_[i], sizeof(ATTRIBUTE_REC));
	}
}

KeyIndex::~KeyIndex(){}

void KeyIndex::init(DbEnv *env_){
	env = env_;
	assert(preOperator != NULL);
	preOperator->init(env);
	preOperator->getAttriRec(&attriRec[attriNum], 1);
	attriNum++;
	initPosVal();
	attriNum--;
}


int KeyIndex::getRow(PosVal **pv_, unsigned int pvNum_){
	int returnCode;
	while(1){
		returnCode = preOperator->getRow(&pv[attriNum], 1);
		if(returnCode < 0){
			return (-1);
		}
		key.set_data(pv[attriNum]->value);
		key.set_size(pv[attriNum]->getSize());
		
		returnCode = db->readForKey(&key, &data);
		if(returnCode == DB_NOTFOUND){
			//returnCode = -1;
			//return (-1);
		}
		else if(returnCode != 0){
			cout << "Error Scan" << endl;
			exit(-1);
		}
		else{
			setPosVal(pv_, pvNum_);
			//return *(int *)key.get_data();
			return 0;
		}
	}
}

void KeyIndex::setPosVal(PosVal **pv_, unsigned int pvNum_){
	unsigned int pos = 0;

	for(unsigned int i=0; i < pvNum_; i++){
		pv_[i]->set((unsigned char *)(data.get_data()) + pos);
		pos += pv_[i]->getSize();
		if(pv_[i]->type == VARIABLE_TEXT)pos++;
	}
}


unsigned int KeyIndex::getAttriNum(void){
	return attriNum;
}


void KeyIndex::getAttriRec(ATTRIBUTE_REC **attriRec_, unsigned int attriNum_){
	for(unsigned int i = 0; i < attriNum_; i++){
		memcpy(attriRec_[i], attriRec[i], sizeof(ATTRIBUTE_REC));
	}
}
