#include"ScanDSM.h"

using namespace std;

ScanDSM::ScanDSM(BDBOpe *db_, ATTRIBUTE_REC *attriRec_, unsigned int attriNum_)
{
	assert(db_ != NULL);
	db = db_;

	assert(attriNum_ == 1);
	attriNum = attriNum_;
	initAttriRec(attriNum);

	memcpy(attriRec[0], &attriRec_[0], sizeof(ATTRIBUTE_REC));
}


ScanDSM::~ScanDSM()
{
}

void ScanDSM::init(void)
{
	readFlag = 0;
	count = 1;
}


void ScanDSM::resetGetPos(void)
{
	readFlag = 0;
}


int ScanDSM::getRow(PosVal **pv_, unsigned int pvNum_)
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

unsigned int ScanDSM::getAttriNum(void){
	return attriNum;
}

void ScanDSM::getAttriRec(ATTRIBUTE_REC **attriRec_, unsigned int attriNum_){
	for(unsigned int i = 0; i < attriNum_; i++){
		memcpy(attriRec_[i], attriRec[i], sizeof(ATTRIBUTE_REC));
	}
}
