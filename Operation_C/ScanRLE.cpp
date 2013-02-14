#include"ScanRLE.h"

using namespace std;

ScanRLE::ScanRLE(BDBOpe *db_, ATTRIBUTE_REC *attriRec_, unsigned int attriNum_)
{
	assert(db_ != NULL);
	db = db_;
	assert(attriNum_ == 1);
	initAttriRec(attriNum_);

	memcpy(attriRec[0], &attriRec_[0], sizeof(ATTRIBUTE_REC));
	attriNum = attriNum_;
	
}


ScanRLE::~ScanRLE()
{
}

void ScanRLE::init(DbEnv *env_)
{
	readFlag = 0;
	count = 1;
	position=1;
	initPosVal();
	env = env_;
	
	sprintf(buf, "%d.%d-to-%d.0.JoinIndex", attriRec[0]->tableID, attriRec[0]->attributeID, attriRec[0]->tableID);
	string joinIndexName = buf;
	joinIndex = new BDBOpe(env, joinIndexName);
	joinIndex->open();
	
	pos = new IntPosVal;
	posAttri = new ATTRIBUTE_REC;
	posAttri->dataType = INT;
	posAttri->dataLength = 4;
	scanJI = new ScanDSM(joinIndex, posAttri, 1);
	scanJI->init(env);
}


void ScanRLE::resetGetPos(void)
{
	readFlag = 0;
}


int ScanRLE::getRow(PosVal **pv_, unsigned int pvNum_)
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
			cout << "Error ScanRLE" << endl;
			exit(-1);
		}
		readFlag = 1;
		dataItemNum = *(unsigned int *)(data.get_data());
		readItemNum = 0;
		dataPos = sizeof(unsigned int) * 2;
		
		getRLE();
		readItemNum++;
	}
	if((!(readItemNum < dataItemNum)) && !(repeat < repeatMax)){
		returnCode = db->readNextRecord(&key, &data);
		if(returnCode == DB_NOTFOUND){
			readFlag = 2;
			return (-1);
		}
		if(returnCode != 0){
			cout << "Error ScanRLE" << endl;
			exit(-1);
		}
		dataItemNum = *(unsigned int *)(data.get_data());
		readItemNum = 0;
		dataPos = sizeof(unsigned int) * 2;

		getRLE();
		readItemNum++;
	}
	
	if(!(repeat < repeatMax)){
		getRLE();
		readItemNum++;
	}
	
		
	if(attriRec[0]->isSort != true){
		returnCode = scanJI->getRow(&pos,1);
		if(returnCode != 0){
			cout << "Error ScanJI : ScanRLE" << endl;
			exit(1);
		}
	}

	for(unsigned int i=0; i < pvNum_; i++){
		pv_[i] = pv[0];
		if(attriRec[0]->isSort == true){
			pv_[i]->setPos(position);
			position++;
		}else{
			pv_[i]->setPos(*(unsigned int*)pos->value);
		}
	}
	count++;
	repeat++;
	return 0;
}

void ScanRLE::getRLE(void){
		repeat = 0;
		pv[0]->set(count, (unsigned char *)(data.get_data()) + dataPos);
		dataPos += pv[0]->getSize();
		if(pv[0]->type == VARIABLE_TEXT)dataPos++;
		startPos = *(int *)((unsigned char *)(data.get_data()) + dataPos);
		dataPos += sizeof(unsigned int);
		repeatMax = *(int *)((unsigned char *)(data.get_data()) + dataPos);
		dataPos += sizeof(unsigned int);
		
//		cout << "* Pos = " << startPos << "\tMax = " << repeatMax << endl;
}
	
unsigned int ScanRLE::getAttriNum(void){
	return attriNum;
}

void ScanRLE::getAttriRec(ATTRIBUTE_REC **attriRec_, unsigned int attriNum_){
	for(unsigned int i = 0; i < attriNum_; i++){
		memcpy(attriRec_[i], attriRec[i], sizeof(ATTRIBUTE_REC));
	}
}
