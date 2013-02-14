#include"RLEElement.h"

RLEElement::RLEElement(){
	value = NULL;
	startPos = 0;
	repeat =0;
}

RLEElement::RLEElement(PosVal *val_, unsigned int pos_, unsigned int rep_){
	assert(rep_ > 0);
	value = (val_ == NULL?NULL:val_->clone());
	startPos = pos_;
	repeat = rep_;
}

RLEElement::RLEElement(const RLEElement& element_){
	value = (element_.value == NULL?NULL:element_.value->clone());
	startPos = element_.startPos;
	repeat = element_.repeat;
}

RLEElement::~RLEElement(){
	delete value;
}

void RLEElement::setElement(PosVal *val_, int pos_, int rep_){
	if(value != NULL)delete value;
	value = (val_ == NULL?NULL:val_->clone());
	assert(pos_ > 0 && rep_ > 0);
	startPos = (unsigned int)pos_;
	repeat = (unsigned int)rep_;
}

void RLEElement::setElement(RLEElement *element_){
	assert(element_ != NULL);
	if(value != NULL)delete value;
	value = (element_->value == NULL?NULL:element_->value->clone());
	startPos = element_->startPos;
	repeat = element_->repeat;
}

void RLEElement::setNull(){
	value = NULL;
	startPos = 0;
	repeat = 0;
}

bool RLEElement::isNull(){
	return (value == NULL && startPos == 0 && repeat ==0);
}
