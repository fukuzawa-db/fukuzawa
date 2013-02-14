#include"Operator.h"

Operator::Operator(){
	preOperator = NULL;
}

Operator::~Operator(){}

void Operator::initPosVal(void){
	pv = new PosVal*[attriNum];

	for(unsigned int i= 0; i < attriNum; i++){
		switch(attriRec[i]->dataType){
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
				pv[i] = new FixStrPosVal(0, attriRec[i]->dataLength);
				break;

			case VARIABLE_TEXT:
				pv[i] = new VarStrPosVal(0, attriRec[i]->dataLength);
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

void Operator::initPosVal(PosVal **&pv_){
	pv_ = new PosVal*[attriNum];

	for(unsigned int i= 0; i < attriNum; i++){
		switch(attriRec[i]->dataType){
			case INT:
				pv_[i] = new IntPosVal;
				break;

			case LONG:
				pv_[i] = new LongPosVal;
				break;

			case FLOAT:
				pv_[i] = new FloatPosVal;
				break;

			case DOUBLE:
				pv_[i] = new DoublePosVal;
				break;

			case FIXED_TEXT:
				pv_[i] = new FixStrPosVal(0, attriRec[i]->dataLength);
				break;

			case VARIABLE_TEXT:
				pv_[i] = new VarStrPosVal(0, attriRec[i]->dataLength);
				break;

			case DATE:
				pv_[i] = new DatePosVal;
				break;

			default:
				cout << "ERROR : illegal DataType ; BareEncode" << endl;
				exit(EXIT_FAILURE);
				break;
		}
	}
}

void Operator::initPosVal(PosVal **&pv_, unsigned int start_, unsigned int end_){
	assert(end_ - start_ >= 0);
	pv_ = new PosVal*[end_ - start_ +1];

	for(unsigned int i= start_ ; i <= end_; i++){
		switch(attriRec[i]->dataType){
			case INT:
				pv_[i] = new IntPosVal;
				break;

			case LONG:
				pv_[i] = new LongPosVal;
				break;

			case FLOAT:
				pv_[i] = new FloatPosVal;
				break;

			case DOUBLE:
				pv_[i] = new DoublePosVal;
				break;

			case FIXED_TEXT:
				pv_[i] = new FixStrPosVal(0, attriRec[i]->dataLength);
				break;

			case VARIABLE_TEXT:
				pv_[i] = new VarStrPosVal(0, attriRec[i]->dataLength);
				break;

			case DATE:
				pv_[i] = new DatePosVal;
				break;

			default:
				cout << "ERROR : illegal DataType ; BareEncode" << endl;
				exit(EXIT_FAILURE);
				break;
		}
	}
}

void Operator::initAttriRec(unsigned int attriNum_){
	attriRec = new ATTRIBUTE_REC*[attriNum_];
	for(unsigned int i = 0; i< attriNum_; i++){
		attriRec[i] = new ATTRIBUTE_REC;
	}
}
