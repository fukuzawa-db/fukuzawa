#include"ScanDSM_U.h"

using namespace std;

ScanDSM_U::ScanDSM_U(BDBOpe *db_, ATTRIBUTE_REC *attriRec_, unsigned int attriNum_)
{
	assert(db_ != NULL);
	db = db_;

	assert(attriNum_ == 1);
	attriNum = attriNum_;
	initAttriRec(attriNum);

	memcpy(attriRec[0], &attriRec_[0], sizeof(ATTRIBUTE_REC));
	num = GET_DSM_DATA;
	loop = 1;
}

ScanDSM_U::ScanDSM_U(BDBOpe *db_, ATTRIBUTE_REC *attriRec_, unsigned int attriNum_, unsigned int num_)
{
	assert(db_ != NULL);
	db = db_;

	assert(attriNum_ == 1);
	attriNum = attriNum_;
	initAttriRec(attriNum);

	memcpy(attriRec[0], &attriRec_[0], sizeof(ATTRIBUTE_REC));
	num = num_;
	loop = 1;
}

ScanDSM_U::ScanDSM_U(BDBOpe *db_, ATTRIBUTE_REC *attriRec_, unsigned int attriNum_, unsigned int num_, unsigned int loop_)
{
	assert(db_ != NULL);
	db = db_;

	assert(attriNum_ == 1);
	attriNum = attriNum_;
	initAttriRec(attriNum);

	memcpy(attriRec[0], &attriRec_[0], sizeof(ATTRIBUTE_REC));
	num = num_;
	loop = loop_;
}

ScanDSM_U::~ScanDSM_U()
{
}

void ScanDSM_U::init(DbEnv *env_)
{
	env = env_;
	readFlag = 0;
	count = 1;
	
	//storeData();
}


void ScanDSM_U::resetGetPos(void)
{
	bufferPoint = 0;
	getFlag = 0;
}

void ScanDSM_U::storeData(void){
	storePosVal = new PosVal**[num];
	for(unsigned int i=0; i<num; i++){
		initPosVal(storePosVal[i]);
		if(setPosVal(storePosVal[i], attriNum) == -1)break;
	}
	bufferPoint = 0;	
}

int ScanDSM_U::getRow(PosVal **pv_, unsigned int pvNum_){
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

int ScanDSM_U::setPosVal(PosVal **pv_, unsigned int pvNum_)
{
	int returnCode;

	if(readFlag ==2){
		return (-1);
	}
	if(readFlag == 0){
		returnCode = db->readFirstRecord(&key, &data);
		if(returnCode == DB_NOTFOUND){
			readFlag = 2;
			return (-1);
		}
		if(returnCode != 0){
			cout << "Error ScanDSM firstrecord" << endl;
			exit(-1);
		}
		readFlag = 1;
		dataItemNum = *(unsigned int *)(data.get_data());
		readItemNum = 0;
		dataPos = sizeof(unsigned int) * 2;
	}
	if(!(readItemNum < dataItemNum)){
		returnCode = db->readNextRecord(&key, &data);
		if(returnCode == DB_NOTFOUND){
			readFlag = 2;
			return (-1);
		}
		if(returnCode != 0){
			cout << "Error ScanDSM" << endl;
			exit(-1);
		}
		dataItemNum = *(unsigned int *)(data.get_data());
		readItemNum = 0;
		dataPos = sizeof(unsigned int) * 2;
	}

	for(unsigned int i=0; i < pvNum_; i++){
		pv_[i]->set((unsigned char *)(data.get_data()) + dataPos);
		dataPos += pv_[i]->getSize();
		if(pv_[i]->type == VARIABLE_TEXT)dataPos++;
		pv_[i]->setPos(count);
	}
	count++;
	readItemNum++;
	return 0;
}

unsigned int ScanDSM_U::getAttriNum(void){
	return attriNum;
}

void ScanDSM_U::getAttriRec(ATTRIBUTE_REC **attriRec_, unsigned int attriNum_){
	for(unsigned int i = 0; i < attriNum_; i++){
		memcpy(attriRec_[i], attriRec[i], sizeof(ATTRIBUTE_REC));
	}
}
