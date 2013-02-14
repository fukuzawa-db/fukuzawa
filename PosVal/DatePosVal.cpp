#include"DatePosVal.h"

using namespace std;

DatePosVal::DatePosVal(){
	type = DATE;
	position = 0;
	value = new unsigned char[10];
	memset((char *)value, 0, 10);
}

DatePosVal::DatePosVal(unsigned int pos_, unsigned char *value_){
	type = DATE;
	position = pos_;
	value = new unsigned char[10];
	memcpy((char *)value, (char *)value_, 10);
}

DatePosVal::DatePosVal(DatePosVal& posVal_){
	assert(posVal_.type == DATE);
	type = posVal_.type;
	position = posVal_.position;
	value = new unsigned char[10];
	memcpy((char *)value, (char *)posVal_.value, 10);
}

DatePosVal::~DatePosVal(){
	if(value != NULL)delete value;
}

PosVal *DatePosVal::clone(){
	PosVal *newPosVal = new DatePosVal(*this);
	return newPosVal;
}

unsigned short DatePosVal::getSize(){
	return 10;
}

void DatePosVal::set(unsigned char *value_){
	memcpy(value, value_, 10);
}

void DatePosVal::set(unsigned int pos_, unsigned char *value_){
	position = pos_;
	memcpy(value, value_, 10);
}

void DatePosVal::set(DataType dataType_, unsigned int pos_, unsigned char *value_){
	assert(dataType_ == DATE);
	type = dataType_;
	position = pos_;
	memcpy(value, value_, 10);
}

void DatePosVal::printVal(){
	char printStr[11];
	memcpy(printStr, value ,10);
	printStr[10] = '\0';
	cout << printStr;
}


void DatePosVal::filterYear(void)
{
	for(int i=0; i < 4; i++)value[i] = '0';
}

void DatePosVal::filterMonth(void)
{
	for(int i=5; i < 7; i++)value[i] = '0';
}

void DatePosVal::filterDay(void)
{
	for(int i=8; i < 10; i++)value[i] = '0';
}


PosVal &DatePosVal::operator= (const PosVal& posVal_){
	assert(posVal_.type == DATE);
	type = posVal_.type;
	position = ((DatePosVal &)posVal_).position;
	set(((DatePosVal &)posVal_).value);
	return *this;
}

bool DatePosVal::operator> (PosVal* posVal_) {
  assert(posVal_->type == DATE);
  return (strncmp((char *)value, (char *)posVal_->value, 10) > 0);
}

bool DatePosVal::operator< (PosVal* posVal_) {
  assert(posVal_->type == DATE);
  return (strncmp((char *)value, (char *)posVal_->value, 10) < 0);
}

bool DatePosVal::operator>= (PosVal* posVal_) {
  assert(posVal_->type == DATE);
  return (strncmp((char *)value, (char *)posVal_->value, 10) >= 0);
}

bool DatePosVal::operator<= (PosVal* posVal_) {
  assert(posVal_->type == DATE);
  return (strncmp((char *)value, (char *)posVal_->value, 10) <= 0);
}

bool DatePosVal::operator== (PosVal* posVal_) {
  assert(posVal_->type == DATE);
  return (strncmp((char *)value, (char *)posVal_->value, 10) == 0);
}

bool DatePosVal::operator!= (PosVal* posVal_) {
  assert(posVal_->type == DATE);
  return (strncmp((char *)value, (char *)posVal_->value, 10) != 0);
}

/*
bool DatePosVal::operator> (unsigned int Val_) {
  return dateValue > Val_;
}

bool DatePosVal::operator< (unsigned int Val_) {
  return dateValue < Val_;
}

bool DatePosVal::operator>= (unsigned int Val_) {
  return dateValue >= Val_;
}

bool DatePosVal::operator<= (unsigned int Val_) {
  return dateValue <= Val_;
}

bool DatePosVal::operator== (unsigned int Val_) {
  return dateValue == Val_;
}

bool DatePosVal::operator!= (unsigned int Val_) {
  return dateValue != Val_;
}
*/
