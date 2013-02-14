#include"IntPosVal.h"

using namespace std;

IntPosVal::IntPosVal(){
	type = INT;
	position = 0;
	intValue = 0;
	value = (unsigned char *)&intValue;
}

IntPosVal::IntPosVal(unsigned int pos_, int value_){
	type = INT;
	position = pos_;
	intValue = value_;
	value = (unsigned char *)&intValue;
}

IntPosVal::IntPosVal(IntPosVal& posVal_){
	assert(posVal_.type == INT);
	type = posVal_.type;
	position = posVal_.position;
	intValue = posVal_.intValue;
	value = (unsigned char *)&intValue;
}

IntPosVal::~IntPosVal(){
	if(value != NULL)value = NULL;
}

PosVal *IntPosVal::clone(){
	PosVal *newPosVal = new IntPosVal(*this);
	return newPosVal;
}

unsigned short IntPosVal::getSize(){
	return sizeof(int);
}

void IntPosVal::set(unsigned char *value_){
	intValue = *(int *)value_;
}

void IntPosVal::set(unsigned int pos_, unsigned char *value_){
	position = pos_;
	intValue = *(int *)value_;
}

void IntPosVal::set(DataType dataType_, unsigned int pos_, unsigned char *value_){
	assert(dataType_ == INT);
	type = dataType_;
	position = pos_;
	intValue = *(int *)value_;
}

void IntPosVal::printVal(){
	std::cout << intValue;
}

PosVal &IntPosVal::operator= (const PosVal& posVal_){
	assert(posVal_.type == INT);
	type = posVal_.type;
	position = ((IntPosVal &)posVal_).position;
	intValue = ((IntPosVal &)posVal_).intValue;
	return *this;
}

bool IntPosVal::operator> (PosVal* posVal_) {
  assert(posVal_->type == INT);
  return intValue > *(int *)posVal_->value;
}

bool IntPosVal::operator< (PosVal* posVal_) {
  assert(posVal_->type == INT);
  //test    cout << intValue << " < " <<*(int *)posVal_->value << endl;
  return intValue < *(int *)posVal_->value;
}

bool IntPosVal::operator>= (PosVal* posVal_) {
  assert(posVal_->type == INT);
  return intValue >= *(int *)posVal_->value;
}

bool IntPosVal::operator<= (PosVal* posVal_) {
  assert(posVal_->type == INT);
  return intValue <= *(int *)posVal_->value;
}

bool IntPosVal::operator== (PosVal* posVal_) {
  assert(posVal_->type == INT);
  return intValue == *(int *)posVal_->value;
}

bool IntPosVal::operator!= (PosVal* posVal_) {
  assert(posVal_->type == INT);
  return intValue != *(int *)posVal_->value;
}

bool IntPosVal::operator> (int Val_) {
  return intValue > Val_;
}

bool IntPosVal::operator< (int Val_) {
  return intValue < Val_;
}

bool IntPosVal::operator>= (int Val_) {
  return intValue >= Val_;
}

bool IntPosVal::operator<= (int Val_) {
  return intValue <= Val_;
}

bool IntPosVal::operator== (int Val_) {
  return intValue == Val_;
}

bool IntPosVal::operator!= (int Val_) {
  return intValue != Val_;
}
