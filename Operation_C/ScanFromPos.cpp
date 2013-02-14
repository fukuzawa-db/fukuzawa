#include"ScanFromPos.h"

using namespace std;


ScanFromPos::ScanFromPos(Operator *op_, BDBOpe *db_, ATTRIBUTE_REC *attriRec_, unsigned int attriNum_)
{
	assert(db_ != NULL);
	db = db_;
	preOperator = op_;

	assert(attriNum_ == 1);
	
	outAttriNum = attriNum_;
	initOutAttriRec(attriNum_);
	memcpy(outAttriRec[0], &attriRec_[0], sizeof(ATTRIBUTE_REC));
}


ScanFromPos::~ScanFromPos()
{
}

void ScanFromPos::init(DbEnv *env_)
{
	env = env_;
	preOperator->init(env);
	attriNum = preOperator->getAttriNum();
	initAttriRec(attriNum);
	preOperator->getAttriRec(attriRec, attriNum);
	initPosVal();
	getFlag = 0;
}


int ScanFromPos::getRow(PosVal **pv_, unsigned int pvNum_)
{
	int returnCode;

	if(getFlag == -1){
		return (-1);
	}
	
	returnCode = preOperator->getRow(pv, attriNum);
	if(returnCode != 0){
		getFlag = -1;
		return (-1);
	}
	
	indexPos = pv[0]->position;
	if(getFlag == 0 || indexPos > end){
		key.set_data(&pv[0]->position);
		key.set_size(sizeof(unsigned int));
		db->readRangeRecord(&key, &data);
		setHeader();
		getFlag = 1;
		if(outAttriRec[0]->dataType == VARIABLE_TEXT){
			currentPos = start;
			currentOffset = sizeof(unsigned int)*2;
		}
	}
	
	switch(outAttriRec[0]->dataType){
			case INT:
				pv_[0]->set(((unsigned char*)data.get_data()) + sizeof(unsigned int)*2 + sizeof(int)*(indexPos - start));
				break;

			case LONG:
				pv_[0]->set(((unsigned char*)data.get_data()) + sizeof(unsigned int)*2 + sizeof(long)*(indexPos - start));
				break;

			case FLOAT:
				pv_[0]->set(((unsigned char*)data.get_data()) + sizeof(unsigned int)*2 + sizeof(float)*(indexPos - start));
				break;

			case DOUBLE:
				pv_[0]->set(((unsigned char*)data.get_data()) + sizeof(unsigned int)*2 + sizeof(double)*(indexPos - start));
				break;

			case FIXED_TEXT:
				pv_[0]->set(((unsigned char*)data.get_data()) + sizeof(unsigned int)*2 + attriRec[0]->dataLength*(indexPos - start));
				break;

			case VARIABLE_TEXT:
				setOffset();
				pv_[0]->set(((unsigned char*)data.get_data()) + currentOffset);
				break;

			case DATE:
				pv_[0]->set(((unsigned char*)data.get_data()) + sizeof(unsigned int)*2 + attriRec[0]->dataLength*(indexPos - start));
				break;

			default:
				cout << "ERROR : illegal DataType ; BareEncode" << endl;
				exit(EXIT_FAILURE);
				break;
		
	}
	pv_[0]->position = indexPos;
	return 0;
}

unsigned int ScanFromPos::getAttriNum(void){
	return attriNum;
}

void ScanFromPos::getAttriRec(ATTRIBUTE_REC **attriRec_, unsigned int attriNum_){
	for(unsigned int i = 0; i < attriNum_; i++){
		memcpy(attriRec_[i], outAttriRec[i], sizeof(ATTRIBUTE_REC));
	}
}

void ScanFromPos::initOutAttriRec(unsigned int attriNum_){
	outAttriRec = new ATTRIBUTE_REC*[attriNum_];
	for(unsigned int i = 0; i< attriNum_; i++){
		outAttriRec[i] = new ATTRIBUTE_REC;
	}
}

void ScanFromPos::setHeader(void){
	itemNum = *(int *)data.get_data();
	start = *((int *)data.get_data()+1);
	end = start + itemNum - 1;
}

void ScanFromPos::setOffset(void){
	while(currentPos < indexPos){
		while(1){
			if(*((char *)data.get_data() + currentPos) == '\0'){
				currentPos++;
				break;
			}
			currentPos++;
		}
	}
}

