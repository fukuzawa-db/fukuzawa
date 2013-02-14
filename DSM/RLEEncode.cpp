#include"RLEEncode.h"

RLEEncode::RLEEncode(string fileName_, DataType dataType_, unsigned short dataLength_){
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
//可変長の圧縮は未実装
/*		case VARIABLE_TEXT:
			pv = new VarStrPosVal;
			break;
*/
		case DATE:
			pv = new DatePosVal;
			fetchPV = new DatePosVal;
			break;

		default:
			cout << "ERROR : illegal DataType ; RLEEncode" << endl;
			exit(EXIT_FAILURE);
	}
	//ページのヘッダサイズ
	RLEElementSize = dataLength + sizeof(rleElement.startPos) + sizeof(rleElement.repeat);
	initVal();
	getVal();
}

RLEEncode::~RLEEncode(){
	if(pv != NULL)delete pv;
	if(fetchPV != NULL)delete fetchPV;
	freeVal();
	ifs.close();
}

unsigned char *RLEEncode::getBuffer(unsigned char *buffer_, unsigned int *bufSize_, unsigned *key_){
	
	unsigned int offset = startOffset;

	if(dataType != VARIABLE_TEXT){
		itemNum = (unsigned int *)buffer_;
		startPos = (unsigned int *)(buffer_ + sizeof(unsigned int));
		
		*itemNum = 0;

		while(!ifs.eof() && ((offset + RLEElementSize) <= DSM_BUFFER_SIZE)){		
			pv->set(pos, (unsigned char *)val);
			
			unsigned int rep=1;
			while(!ifs.eof()){
			//while(1){
				getVal();
				if(ifs.eof())break;
				pos++;
				fetchPV->set(pos, (unsigned char *)val);
			
				if(*pv == fetchPV)
					rep++;
				else{
//debug					cout << " repeat = " << rep << endl;
					break;
				}
			}
			
			rleElement.setElement(pv, pv->position, rep);
			if(*itemNum == 0)
				*startPos = pv->position;

			memcpy(buffer_ + offset, pv->value, pv->getSize());
			offset += pv->getSize();
			memcpy(buffer_ + offset, &rleElement.startPos, sizeof(rleElement.startPos));
			offset += sizeof(rleElement.startPos);
			memcpy(buffer_ + offset, &rleElement.repeat, sizeof(rleElement.repeat));
			offset += sizeof(rleElement.repeat);

			(*itemNum)++;
		}
		if(!ifs.eof() && (*itemNum == 0)){
			cout << "RLEElement size is too big!  Cannot store entry" << endl;
			exit(EXIT_FAILURE);
		}

		if(*itemNum == 0)return NULL;

		*bufSize_ = offset;
		*key_ = pos - 1;
		return buffer_;
	}
	else{
		cout << "VARIABLE_TEXT type is illegal in RLE" << endl;
		exit(EXIT_FAILURE);
	}
}

