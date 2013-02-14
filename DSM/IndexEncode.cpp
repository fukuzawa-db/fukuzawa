#include"IndexEncode.h"

IndexEncode::IndexEncode(string fileName_, DataType dataType_, unsigned short dataLength_){
	fileName = fileName_;
	dataType = dataType_;
	dataLength = dataLength_;

	//列データファイルを格納した一時ファイルをオープン
	ifs.open(fileName.c_str());
	if(ifs == NULL){
		cout << "Can't open File : " << fileName.c_str() << endl;
		exit(EXIT_FAILURE);
	}
	pos = 1;
	//各データ型のPosValを作成
	switch(dataType){
		case INT:
			pv = new IntPosVal;
			fetchPV = new IntPosVal;
			break;

		case LONG:
			pv = new LongPosVal;
			fetchPV = new LongPosVal;
			break;

		case FLOAT:
			pv = new FloatPosVal;
			fetchPV = new FloatPosVal;
			break;

		case DOUBLE:
			pv = new DoublePosVal;
			fetchPV = new DoublePosVal;
			break;

		case FIXED_TEXT:
			pv = new FixStrPosVal(0, dataLength);
			fetchPV = new FixStrPosVal(0, dataLength);
			break;

		case VARIABLE_TEXT:
			pv = new VarStrPosVal;
			break;

		case DATE:
			pv = new DatePosVal;
			fetchPV = new DatePosVal;
			break;

		default:
			cout << "ERROR : illegal DataType ; IndexEncode" << endl;
			exit(EXIT_FAILURE);
	}
	//ページのヘッダサイズ
	initVal();
}

IndexEncode::~IndexEncode(){
	if(pv != NULL)delete pv;
	if(fetchPV != NULL)delete fetchPV;
	freeVal();
	ifs.close();
}

unsigned char *IndexEncode::getBuffer(unsigned char *buffer_, unsigned int *bufSize_, unsigned int *key_){
	getVal();
	if(ifs.eof()) return NULL;
	
	if(dataType != VARIABLE_TEXT){
		memcpy(buffer_, val, dataLength);
		*bufSize_ = dataLength;
		return buffer_;
	}else{
		memcpy(buffer_, val, dataLength+1);
		*bufSize_ = dataLength + 1;
		return buffer_;
	}
}

