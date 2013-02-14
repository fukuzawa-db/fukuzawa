#include"IndexRangScan.h"

using namespace std;

IndexRangScan::IndexRangScan(BDBOpe *db_, ATTRIBUTE_REC *attriRec_, unsigned int attriNum_){
	assert(db_ != NULL);
	db = db_;
	attriNum = attriNum_;
	initAttriRec(attriNum);
	
	for(unsigned int i = 0; i < attriNum; i++){
		memcpy(attriRec[i], &attriRec_[i], sizeof(ATTRIBUTE_REC));
	}
}

IndexRangScan::~IndexRangScan(){
	delete[] attriRec;
}

void IndexRangScan::init(DbEnv *env_){
	env = env_;
}

void IndexRangScan::keySet(PosVal *skey_, PosVal *ekey_, OPERATION_NODE *op_){
	key.set_data(skey_->value);
	key.set_size(skey_->getSize());
	unsigned int i;
	for(i = 0; i < attriNum ; i++){
		if(op_->attributeID == attriRec[i]->attributeID && op_->tableID == attriRec[i]->tableID){
			position = i;
			break;
		}
	}
	if(i == attriNum){
		cerr << "IndexRangScan : Error not exist position" << endl;
		exit(EXIT_FAILURE);
	}
	ekey = ekey_;
	initFlag = 0;
	getFlag = 0;
}

int IndexRangScan::getRow(PosVal **pv_, unsigned int pvNum_){
	int returnCode;

	if(getFlag == -1){
		return (-1);
	}
	

	if(initFlag == 0){
		returnCode = db->readRangeRecord(&key, &data);
		//returnCode = db->readFirstRecord(&key, &data);
		initFlag = 1;
	}else{
		returnCode = db->readNextRecord(&key, &data);
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
		//cout << data.get_data() << endl;
		if(*pv_[position] >= ekey){
			getFlag = -1;
			return -1;
		}
		
		return 0;
	}
}


void IndexRangScan::setPosVal(PosVal **pv_, unsigned int pvNum_){
	unsigned int pos = 0;

	for(unsigned int i=0; i < pvNum_; i++){
		pv_[i]->set((unsigned char *)(data.get_data()) + pos);
		pos += pv_[i]->getSize();
		if(pv_[i]->type == VARIABLE_TEXT)pos++;
	}
}


unsigned int IndexRangScan::getAttriNum(void){
	return attriNum;
}

void IndexRangScan::getAttriRec(ATTRIBUTE_REC **attriRec_, unsigned int attriNum_){
	for(unsigned int i = 0; i < attriNum_; i++){
		memcpy(attriRec_[i], attriRec[i], sizeof(ATTRIBUTE_REC));
	}
}

