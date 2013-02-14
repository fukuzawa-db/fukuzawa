#include"Projection.h"

Projection::Projection(string fileName_, ATTRIBUTE_REC *attriRec_, unsigned int attriNum_, unsigned int *projectionAttriNum_, unsigned int projectionNum_, OUT_FLAG outFlag_){
	fileName = fileName_;
	attriRec = attriRec_;
	attriNum = attriNum_;
	projectionAttriNum = projectionAttriNum_;
	projectionNum = projectionNum_;

	outFlag =outFlag_;
	outDb = NULL;
	init();
	initPosVal();

#ifdef DEBUG
	cout << "attriNum = " << attriNum << "  projectionNum = " << projectionNum << endl;
#endif
	oBuffer = new unsigned char[oBufferSize];
}


Projection::Projection(string fileName_, ATTRIBUTE_REC *attriRec_, unsigned int attriNum_, unsigned int *projectionAttriNum_, unsigned int projectionNum_, OUT_FLAG outFlag_, BDBOpe *outDb_){
	fileName = fileName_;
	attriRec = attriRec_;
	attriNum = attriNum_;
	projectionAttriNum = projectionAttriNum_;
	projectionNum = projectionNum_;

	outFlag = outFlag_;
	outDb = outDb_;

	init();
	initPosVal();
	oBuffer = new unsigned char[oBufferSize];
}


Projection::~Projection(){
	delete []attriLen;
	delete buffer;
	delete Db;
	if(outDb == NULL)delete outDb;
	for(unsigned int i =0 ; i < projectionNum ; i++) delete pv[i];
	delete[] pv;
}


void Projection::init(){
	oBufferSize = 0;
	int index = 0;
	attriLen = new unsigned int[attriNum];
	bufferSize = 0;
	for (unsigned int i = 0; i < attriNum; i++){
		if(attriRec[i].dataType != VARIABLE_TEXT){
			attriLen[i] = attriRec[i].dataLength;
		}else{
			attriLen[i] = 0;
		}
		bufferSize += attriRec[i].dataLength;
		
		if(outFlag == DB_OUT && (index < (int)projectionNum)){
			if((i + 1) == projectionAttriNum[index]){
				oBufferSize += attriRec[i].dataLength;
			}
			index++;
		}		
	}
	buffer = new unsigned char[bufferSize + 1];
	Db = new BDBOpe(fileName);
	Db->open();
}


void Projection::initPosVal(){
	pv = new PosVal*[projectionNum];

	for(unsigned int i= 0; i < projectionNum; i++){
		switch(attriRec[projectionAttriNum[i] - 1].dataType){
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
				pv[i] = new FixStrPosVal(0, attriRec[projectionAttriNum[i] - 1].dataLength);
				break;

			case VARIABLE_TEXT:
				pv[i] = new VarStrPosVal(0, attriRec[projectionAttriNum[i] - 1].dataLength);
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


void Projection::exec(void){
	while(Db->readNextRecord(&key, &data) == 0){
		buffer[bufferSize] = '\0';
		unsigned int pos = 0; 
		unsigned int index = 0;
		for(unsigned int i = 0; i < attriNum; i++){
			if((i + 1) == projectionAttriNum[index]){
				pv[index]->set((unsigned char *)(data.get_data()) + pos);	
				if(++index == projectionNum)break;
			}

			if(attriLen[i] != 0){
				pos += attriLen[i];
			}else{
				pos += ((unsigned char *)strchr((char *)(buffer+pos), '\0') - &buffer[0]) + 1;
			}
		}
		if(outFlag == STD_OUT){
			printPosVal();
		}else{
			printDb();
		}
	}
}
	


void Projection::printPosVal(){

	for(unsigned int i= 0; i < projectionNum; i++){
		switch(attriRec[projectionAttriNum[i] - 1].dataType){
			case INT:
				cout << *(int *)pv[i]->value << "|";
				break;

			case LONG:
				cout << *(long *)pv[i]->value << "|";
				break;

			case FLOAT:
				cout << *(float *)pv[i]->value << "|";
				break;

			case DOUBLE:
				cout << *(double *)pv[i]->value << "|";
				break;

			case FIXED_TEXT:
				{
				int valLen = attriLen[projectionAttriNum[i] - 1];
				char printStr[valLen +1];
				memcpy(printStr, (char *)pv[i]->value ,valLen);
				printStr[valLen] = '\0';
				cout << printStr << "|";
				break;
				}

			case VARIABLE_TEXT:
				{
				cout << (char *)pv[i]->value << "|";
				break;
				}

			case DATE:
				{
				int valLen = attriLen[projectionAttriNum[i] - 1];
				char printStr[valLen +1];
				memcpy(printStr, (char *)pv[i]->value ,valLen);
				printStr[valLen] = '\0';
				cout << printStr << "|";
				break;
				}

			default:
				cout << "ERROR : illegal DataType ; BareEncode" << endl;
				exit(EXIT_FAILURE);
				break;
		}
	}
	cout << endl;
}

void Projection::printDb(){
	unsigned int size = 0;
	cout << "start" << endl;
	for(int i = 0; i < (int)projectionNum; i++){
		switch(attriRec[projectionAttriNum[i] - 1].dataType){
			case INT:
				assert(size + sizeof(int) <= oBufferSize);
				memcpy(oBuffer + size, (int *)pv[i]->value, sizeof(int));
				size += sizeof(int);
				break;

			case LONG:
				assert(size + sizeof(long) <= oBufferSize);
				memcpy(oBuffer + size, (long *)pv[i]->value, sizeof(long));
				size += sizeof(long);
				break;

			case FLOAT:
				assert(size + sizeof(float) <= oBufferSize);
				memcpy(oBuffer + size, (float *)pv[i]->value, sizeof(float));
				size += sizeof(float);
				break;

			case DOUBLE:	
				assert(size + sizeof(double) <= oBufferSize);
				memcpy(oBuffer + size, (double *)pv[i]->value, sizeof(double));
				size += sizeof(double);
				break;

			case FIXED_TEXT:
				assert(size + attriRec[projectionAttriNum[i] - 1].dataLength <= oBufferSize);
				memcpy(oBuffer + size, (char *)pv[i]->value, attriRec[projectionAttriNum[i] - 1].dataLength);
				size += attriRec[projectionAttriNum[i] - 1].dataLength;
				break;

			case VARIABLE_TEXT:
				assert(size + strlen((char *)pv[i]->value) <= oBufferSize);
				strcpy((char *)oBuffer + size, (char *)pv[i]->value);
				size += strlen((char *)pv[i]->value) + 1;
				break;

			case DATE:
				assert(size + attriRec[projectionAttriNum[i] - 1].dataLength <= oBufferSize);
				memcpy(oBuffer + size, (char *)pv[i]->value, attriRec[projectionAttriNum[i] - 1].dataLength);
				size += attriRec[projectionAttriNum[i] - 1].dataLength;
				break;

			default:
				cout << "Error insertVoidData" << endl;
				exit (EXIT_FAILURE);
		}
	}
}
