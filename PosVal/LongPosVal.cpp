#include"LongPosVal.h"

using namespace std;

LongPosVal::LongPosVal(){
	type = LONG;
	position = 0;
	longValue = 0;
	value = (unsigned char *)&longValue;
}

LongPosVal::LongPosVal(unsigned int pos_, long value_){
	type = LONG;
	position = pos_;
	longValue = value_;
	value = (unsigned char *)&longValue;
}

LongPosVal::LongPosVal(LongPosVal& posVal_){
	assert(posVal_.type == LONG);
	type = posVal_.type;
	position = posVal_.position;
	longValue = posVal_.longValue;
	value = (unsigned char *)&longValue;
}

LongPosVal::~LongPosVal(){
	if(value != NULL)value = NULL;
}

PosVal *LongPosVal::clone(){
	PosVal *newPosVal = new LongPosVal(*this);
	return newPosVal;
}

unsigned short LongPosVal::getSize(){
	return sizeof(long);
}

void LongPosVal::set(unsigned char *value_){
	longValue = *(long *)value_;
}

void LongPosVal::set(unsigned int pos_, unsigned char *value_){
	position = pos_;
	longValue = *(long *)value_;
}

void LongPosVal::set(DataType dataType_, unsigned int pos_, unsigned char *value_){
	assert(dataType_ == LONG);
	type = dataType_;
	position = pos_;
	longValue = *(long *)value_;
}

void LongPosVal::printVal(){
	std::cout << longValue;
}

PosVal &LongPosVal::operator= (const PosVal& posVal_){
	assert(posVal_.type == LONG);
	type = posVal_.type;
	position = ((LongPosVal &)posVal_).position;
	longValue = ((LongPosVal &)posVal_).longValue;
	return *this;
}

bool LongPosVal::operator> (PosVal* posVal_) {
  assert(posVal_->type == LONG);
  return longValue > *(long *)posVal_->value;
}

bool LongPosVal::operator< (PosVal* posVal_) {
  assert(posVal_->type == LONG);
  return longValue < *(long *)posVal_->value;
}

bool LongPosVal::operator>= (PosVal* posVal_) {
  assert(posVal_->type == LONG);
  return longValue >= *(long *)posVal_->value;
}

bool LongPosVal::operator<= (PosVal* posVal_) {
  assert(posVal_->type == LONG);
  return longValue <= *(long *)posVal_->value;
}

bool LongPosVal::operator== (PosVal* posVal_) {
  assert(posVal_->type == LONG);
  return longValue == *(long *)posVal_->value;
}

bool LongPosVal::operator!= (PosVal* posVal_) {
  assert(posVal_->type == LONG);
  return longValue != *(long *)posVal_->value;
}

bool LongPosVal::operator> (long Val_) {
  return longValue > Val_;
}

bool LongPosVal::operator< (long Val_) {
  return longValue < Val_;
}

bool LongPosVal::operator>= (long Val_) {
  return longValue >= Val_;
}

bool LongPosVal::operator<= (long Val_) {
  return longValue <= Val_;
}

bool LongPosVal::operator== (long Val_) {
  return longValue == Val_;
}

bool LongPosVal::operator!= (long Val_) {
  return longValue != Val_;
}
