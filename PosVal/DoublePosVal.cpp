#include"DoublePosVal.h"

using namespace std;

DoublePosVal::DoublePosVal(){
	type = DOUBLE;
	position = 0;
	doubleValue = 0.0;
	value = (unsigned char *)&doubleValue;
}

DoublePosVal::DoublePosVal(unsigned int pos_, double value_){
	type = DOUBLE;
	position = pos_;
	doubleValue = value_;
	value = (unsigned char *)&doubleValue;
}

DoublePosVal::DoublePosVal(DoublePosVal& posVal_){
	assert(posVal_.type == DOUBLE);
	type = posVal_.type;
	position = posVal_.position;
	doubleValue = posVal_.doubleValue;
	value = (unsigned char *)&doubleValue;
}

DoublePosVal::~DoublePosVal(){
	if(value != NULL)value = NULL;
}

PosVal *DoublePosVal::clone(){
	PosVal *newPosVal = new DoublePosVal(*this);
	return newPosVal;
}

unsigned short DoublePosVal::getSize(){
	return sizeof(double);
}

void DoublePosVal::set(unsigned char *value_){
	doubleValue = *(double *)value_;
}

void DoublePosVal::set(unsigned int pos_, unsigned char *value_){
	position = pos_;
	doubleValue = *(double *)value_;
}

void DoublePosVal::set(DataType dataType_, unsigned int pos_, unsigned char *value_){
	assert(dataType_ == DOUBLE);
	type = dataType_;
	position = pos_;
	doubleValue = *(double *)value_;
}

void DoublePosVal::printVal(){
	std::cout << doubleValue;
}

PosVal &DoublePosVal::operator= (const PosVal& posVal_){
	assert(posVal_.type == DOUBLE);
	type = posVal_.type;
	position = ((DoublePosVal &)posVal_).position;
	doubleValue = ((DoublePosVal &)posVal_).doubleValue;
	return *this;
}

bool DoublePosVal::operator> (PosVal* posVal_) {
  assert(posVal_->type == DOUBLE);
  return doubleValue > *(double *)posVal_->value;
}

bool DoublePosVal::operator< (PosVal* posVal_) {
  assert(posVal_->type == DOUBLE);
  return doubleValue < *(double *)posVal_->value;
}

bool DoublePosVal::operator>= (PosVal* posVal_) {
  assert(posVal_->type == DOUBLE);
  return doubleValue >= *(double *)posVal_->value;
}

bool DoublePosVal::operator<= (PosVal* posVal_) {
  assert(posVal_->type == DOUBLE);
  return doubleValue <= *(double *)posVal_->value;
}

bool DoublePosVal::operator== (PosVal* posVal_) {
  assert(posVal_->type == DOUBLE);
  return doubleValue == *(double *)posVal_->value;
}

bool DoublePosVal::operator!= (PosVal* posVal_) {
  assert(posVal_->type == DOUBLE);
  return doubleValue != *(double *)posVal_->value;
}

bool DoublePosVal::operator> (double Val_) {
  return doubleValue > Val_;
}

bool DoublePosVal::operator< (double Val_) {
  return doubleValue < Val_;
}

bool DoublePosVal::operator>= (double Val_) {
  return doubleValue >= Val_;
}

bool DoublePosVal::operator<= (double Val_) {
  return doubleValue <= Val_;
}

bool DoublePosVal::operator== (double Val_) {
  return doubleValue == Val_;
}

bool DoublePosVal::operator!= (double Val_) {
  return doubleValue != Val_;
}
