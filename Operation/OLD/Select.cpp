#include"Select.h"

Select::Select(string fileName_, ATTRIBUTE_REC *attriRec_, unsigned int attriNum_, PosVal **selectAttri_, unsigned int selectNum_, OUT_FLAG outFlag_){
	fileName = fileName_;
	attriRec = attriRec_;
	attriNum = attriNum_;
	selectAttri = selectAttri_;
	selectNum = selectNum_;

	outFlag = outFlag_;
	outDb = NULL;
	init();
	initPosVal();

#ifdef DEBUG
	cout << "attriNum = " << attriNum << "  selectNum = " << selectNum << endl;
#endif
}


Select::Select(string fileName_, ATTRIBUTE_REC *attriRec_, unsigned int attriNum_, PosVal **selectAttri_, unsigned int selectNum_, OUT_FLAG outFlag_, BDBOpe *outDb_){
	fileName = fileName_;
	attriRec = attriRec_;
	attriNum = attriNum_;
	selectAttri = selectAttri_;
	selectNum = selectNum_;

	outFlag = outFlag_;
	outDb = outDb_;
	init();
	initPosVal();
}


Select::~Select(){
	delete []attriLen;
	delete buffer;
	delete Db;
	for(unsigned int i =0 ; i < selectNum ; i++) delete pv[i];
	delete[] pv;
}


void Select::init(){
	attriLen = new unsigned int[attriNum];
	bufferSize = 0;
	for (unsigned int i = 0; i < attriNum; i++){
		if(attriRec[i].dataType != VARIABLE_TEXT){
			attriLen[i] = attriRec[i].dataLength;
		}else{
			attriLen[i] = 0;
		}
		bufferSize += attriRec[i].dataLength;
	}
	buffer = new unsigned char[bufferSize + 1];
	Db = new BDBOpe(fileName);
	Db->open();
}

void Select::initPosVal(){
	pv = new PosVal*[selectNum];

	for(unsigned int i= 0; i <selectNum; i++){
		switch(attriRec[selectAttri[i]->position - 1].dataType){
			case INT:
				pv[i] = new IntPosVal;
				break;

			case LONG:
				pv[i] = new LongPosVal;
				break;

			case FLOAT:
				pv[i] = new FloatPosVal;
				break;

			case DOUBLE:
				pv[i] = new DoublePosVal;
				break;

			case FIXED_TEXT:
				pv[i] = new FixStrPosVal(0, attriRec[selectAttri[i]->position - 1].dataLength);
				break;

			case VARIABLE_TEXT:
				pv[i] = new VarStrPosVal(0, attriRec[selectAttri[i]->position - 1].dataLength);
				break;

			case DATE:
				pv[i] = new DatePosVal;
				break;

			default:
				cout << "ERROR : illegal DataType ; BareEncode" << endl;
				exit(EXIT_FAILURE);
				break;
		}
	}
}

void Select::exec(void){
	int line = 1;
	while(Db->readNextRecord(&key, &data) == 0){
		buffer[bufferSize] = '\0';
		unsigned int pos = 0; 
		unsigned int index = 0;
		for(unsigned int i = 0; i < attriNum; i++){
			if((i + 1) == selectAttri[index]->position){
				pv[index]->set((unsigned char *)(data.get_data()) + pos);	
				if(*pv[index] != selectAttri[index])goto next;
				if(++index == selectNum)break;
			}

			if(attriLen[i] != 0){
				pos += attriLen[i];
			}else{
				pos += ((unsigned char *)strchr((char *)(buffer+pos), '\0') - &buffer[0]) + 1;
			}
		}
					
		cout << line << endl;
next:
		line++;
	}
}
	

