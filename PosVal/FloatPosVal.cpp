#include"FloatPosVal.h"

using namespace std;

FloatPosVal::FloatPosVal(){
	type = FLOAT;
	position = 0;
	floatValue = 0.0;
	value = (unsigned char *)&floatValue;
}

FloatPosVal::FloatPosVal(unsigned int pos_, float value_){
	type = FLOAT;
	position = pos_;
	floatValue = value_;
	value = (unsigned char *)&floatValue;
}

FloatPosVal::FloatPosVal(FloatPosVal& posVal_){
	assert(posVal_.type == FLOAT);
	type = posVal_.type;
	position = posVal_.position;
	floatValue = posVal_.floatValue;
	value = (unsigned char *)&floatValue;
}

FloatPosVal::~FloatPosVal(){
	if(value != NULL)value = NULL;
}


PosVal *FloatPosVal::clone(){
	PosVal *newPosVal = new FloatPosVal(*this);
	return newPosVal;
}

unsigned short FloatPosVal::getSize(){
	return sizeof(float);
}

void FloatPosVal::set(unsigned char *value_){
	floatValue = *(float *)value_;
}

void FloatPosVal::set(unsigned int pos_, unsigned char *value_){
	position = pos_;
	floatValue = *(float *)value_;
}

void FloatPosVal::set(DataType dataType_, unsigned int pos_, unsigned char *value_){
	assert(dataType_ == FLOAT);
	type = dataType_;
	position = pos_;
	floatValue = *(float *)value_;
}

void FloatPosVal::printVal(){
	std::cout << floatValue;
}

PosVal &FloatPosVal::operator= (const PosVal& posVal_){
	assert(posVal_.type == FLOAT);
	type = posVal_.type;
	position = ((FloatPosVal &)posVal_).position;
	floatValue = ((FloatPosVal &)posVal_).floatValue;
	return *this;
}

bool FloatPosVal::operator> (PosVal* posVal_) {
  assert(posVal_->type == FLOAT);
  return floatValue > *(float *)posVal_->value;
}

bool FloatPosVal::operator< (PosVal* posVal_) {
  assert(posVal_->type == FLOAT);
  return floatValue < *(float *)posVal_->value;
}

bool FloatPosVal::operator>= (PosVal* posVal_) {
  assert(posVal_->type == FLOAT);
  return floatValue >= *(float *)posVal_->value;
}

bool FloatPosVal::operator<= (PosVal* posVal_) {
  assert(posVal_->type == FLOAT);
  return floatValue <= *(float *)posVal_->value;
}

bool FloatPosVal::operator== (PosVal* posVal_) {
  assert(posVal_->type == FLOAT);
  return floatValue == *(float *)posVal_->value;
}

bool FloatPosVal::operator!= (PosVal* posVal_) {
  assert(posVal_->type == FLOAT);
  return floatValue != *(float *)posVal_->value;
}

bool FloatPosVal::operator> (float Val_) {
  return floatValue > Val_;
}

bool FloatPosVal::operator< (float Val_) {
  return floatValue < Val_;
}

bool FloatPosVal::operator>= (float Val_) {
  return floatValue >= Val_;
}

bool FloatPosVal::operator<= (float Val_) {
  return floatValue <= Val_;
}

bool FloatPosVal::operator== (float Val_) {
  return floatValue == Val_;
}

bool FloatPosVal::operator!= (float Val_) {
  return floatValue != Val_;
}
