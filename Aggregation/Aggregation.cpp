#include"Aggregation.h"

Aggregation::Aggregation(){}

Aggregation::~Aggregation(){}


ATTRIBUTE_REC Aggregation::getAttriRec(void){
	return attriRec;
}


PosVal *Aggregation::getValue(void){
	return pv;
}
