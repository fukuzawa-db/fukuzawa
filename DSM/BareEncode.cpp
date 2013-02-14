#include"BareEncode.h"

BareEncode::BareEncode(string fileName_, DataType dataType_, unsigned short dataLength_) : Encode(){
	fileName = fileName_;
	dataType = dataType_;
	dataLength = dataLength_;

	ifs.open(fileName.c_str());
	if(ifs == NULL){
		cout << "Can't open File : " << fileName.c_str() << endl;
		exit(EXIT_FAILURE);
	}

	pos = 1;
	switch(dataType){
		case INT:
			pv = new IntPosVal;
			break;

		case LONG:
			pv = new LongPosVal;
			break;

		case FLOAT:
			pv = new FloatPosVal;
			break;

		case DOUBLE:
			pv = new DoublePosVal;
			break;

		case FIXED_TEXT:
			pv = new FixStrPosVal(0, dataLength);
			break;

		case VARIABLE_TEXT:
			pv = new VarStrPosVal(0, dataLength);
			break;

		case DATE:
			pv = new DatePosVal;
			break;

		default:
			cout << "ERROR : illegal DataType ; BareEncode" << endl;
			exit(EXIT_FAILURE);
			break;
	}
	initVal();
	getVal();
}

BareEncode::~BareEncode(){
	//if(pv != NULL)delete pv;
	//freeVal();
	ifs.close();
}

unsigned char *BareEncode::getBuffer(unsigned char *buffer_, unsigned int *bufSize_, unsigned *key_){
	
	unsigned int offset = startOffset;

	if(dataType != VARIABLE_TEXT){
		itemNum = (unsigned int *)buffer_;
		startPos = (unsigned int *)(buffer_ + sizeof(unsigned int));
		
		*itemNum = 0;

		while(!ifs.eof()){		
			pv->set(pos, (unsigned char *)val);
			if((int)(offset + pv->getSize()) > DSM_BUFFER_SIZE){
				*bufSize_ = offset;
				*key_ = pv->position - 1;
				return buffer_;
			}
			
			if((*itemNum) == 0)
				(*startPos) = pos;
			memcpy(buffer_ + offset, pv->value, pv->getSize());

			offset += pv->getSize();
			(*itemNum)++;
			pos++;
			getVal();
		}			

		if((*itemNum) == 0)return NULL;

		*bufSize_ = offset;
		*key_ = pv->position;
		return buffer_;
	}
	else{
		unsigned short strSize;
		itemNum = (unsigned int *)buffer_;
		startPos = (unsigned int *)(buffer_ + sizeof(unsigned int));
		*itemNum = 0;	

		 unsigned short poffset = DSM_BUFFER_SIZE - (sizeof(unsigned short));

		 
		while(!ifs.eof()){
			pv->set(pos, (unsigned char *)val);
			if(offset + pv->getSize() + 1 > poffset){
				*bufSize_ = DSM_BUFFER_SIZE;
				*key_ = pv->position - 1;
				return buffer_;
			}
			
			if((*itemNum) == 0)
				(*startPos) = pos;

			strSize = pv->getSize();
			memcpy((char *)(buffer_ + offset), pv->value, pv->getSize() + 1);
			memcpy((char *)(buffer_ + poffset), &offset, sizeof(unsigned short));

			offset += pv->getSize() + 1;
			poffset -= sizeof(unsigned short);
			(*itemNum)++;
			pos++;
			getVal();
		}
		if(*itemNum == 0)return NULL;
		cout << "Number = " << pos-1 << endl;

		*bufSize_ = DSM_BUFFER_SIZE;
		*key_ = pv->position;
		return buffer_;
	}
}
			
