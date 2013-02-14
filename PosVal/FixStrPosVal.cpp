#include"FixStrPosVal.h"

using namespace std;

FixStrPosVal::FixStrPosVal(){
	type = FIXED_TEXT;
	position = 0;
	valLen = 0;
	value = NULL;
}

FixStrPosVal::FixStrPosVal(unsigned int pos_, unsigned short valLen_){
	type = FIXED_TEXT;
	position = pos_;
	valLen = valLen_;
	value = new unsigned char[valLen];
	memset((char *)value, ' ', valLen);
}

FixStrPosVal::FixStrPosVal(FixStrPosVal& posVal_){
	assert(posVal_.type == FIXED_TEXT);
	type = posVal_.type;
	position = posVal_.position;
	valLen = posVal_.valLen;
	value = new unsigned char[valLen];
	memset((char *)value, ' ', valLen);
	set(posVal_.value);
}

FixStrPosVal::~FixStrPosVal(){
	if(value != NULL)delete value;
}

PosVal *FixStrPosVal::clone(){
	PosVal *newPosVal = new FixStrPosVal(*this);
	return newPosVal;
}

unsigned short FixStrPosVal::getSize(){
	assert(valLen > 0);
	return valLen;
}

void FixStrPosVal::set(unsigned char *value_){
	assert(valLen > 0);
	memcpy(value, value_, valLen);
}

void FixStrPosVal::set(unsigned int pos_, unsigned char *value_){
	position = pos_;
	assert(valLen > 0);
	memcpy(value, value_, valLen);
}

void FixStrPosVal::set(DataType dataType_, unsigned int pos_, unsigned char *value_){
	assert(dataType_ == FIXED_TEXT);
	type = dataType_;
	position = pos_;
	assert(valLen > 0);
	memcpy(value, value_, valLen);
}
void FixStrPosVal::setStr(string str_){
	assert(str_.length() <= valLen);
	memcpy(value, str_.c_str(), str_.length());
}

void FixStrPosVal::setStr(unsigned int pos_, string str_){
	position = pos_;
	assert(str_.length() <= valLen);
	memcpy(value, str_.c_str(), str_.length());
}

void FixStrPosVal::setLength(unsigned short valLen_){
	valLen = valLen_;
	if(value != NULL)delete value;
	value = new unsigned char[valLen];
	memset((char *)value, ' ', valLen);
}

void FixStrPosVal::setNull(void){
	assert(value != NULL);
	memset(value, 0, valLen);
	position = 0;
}

void FixStrPosVal::printVal(){
	char printStr[valLen +1];
	int i;
	memcpy(printStr, value ,valLen);

	printStr[valLen] = ' ';
	for(i=valLen; printStr[i] == ' '; i--);
	printStr[i+1] = '\0';

	cout << printStr;
}

PosVal &FixStrPosVal::operator= (const PosVal& posVal_){
	assert(posVal_.type == FIXED_TEXT);
	type = posVal_.type;
	position = ((FixStrPosVal &)posVal_).position;
	valLen = ((FixStrPosVal &)posVal_).valLen;
	if(value != NULL)delete value;
	value = new unsigned char[valLen];
	memset((char *)value, ' ', valLen);
	set(((FixStrPosVal &)posVal_).value);
	return *this;
}

bool FixStrPosVal::operator> (PosVal* posVal_) {
	assert(posVal_->type == FIXED_TEXT);
	assert(valLen == posVal_->getSize());
	return (StrNCmp(value, posVal_->value, valLen) > 0);
}

bool FixStrPosVal::operator< (PosVal* posVal_) {
	assert(posVal_->type == FIXED_TEXT);
	assert(valLen == posVal_->getSize());
	return (StrNCmp(value, posVal_->value, valLen) < 0);
}

bool FixStrPosVal::operator>= (PosVal* posVal_) {
	assert(posVal_->type == FIXED_TEXT);
	assert(valLen == posVal_->getSize());
	return (StrNCmp(value, posVal_->value, valLen) >= 0);
}

bool FixStrPosVal::operator<= (PosVal* posVal_) {
	assert(posVal_->type == FIXED_TEXT);
	assert(valLen == posVal_->getSize());
	return (StrNCmp(value, posVal_->value, valLen) <= 0);
}

bool FixStrPosVal::operator== (PosVal* posVal_) {
	assert(posVal_->type == FIXED_TEXT);
	assert(valLen == posVal_->getSize());
	return (StrNCmp(value, posVal_->value, valLen) == 0);
}

bool FixStrPosVal::operator!= (PosVal* posVal_) {
	assert(posVal_->type == FIXED_TEXT);
	assert(valLen == posVal_->getSize());
	return (StrNCmp(value, posVal_->value, valLen) != 0);
}
/*
bool FixStrPosVal::operator> (string Val_) {
	assert(valLen == Val_.length());
	unsigned char sVal[valLen];
	memcpy(sVal, Val_.c_str(), valLen);
	return (StrNCmp(value, sVal, valLen) > 0);
}

bool FixStrPosVal::operator< (string Val_) {
	assert(valLen == Val_.length());
	unsigned char sVal[valLen];
	memcpy(sVal, Val_.c_str(), valLen);
	return (StrNCmp(value, sVal, valLen) < 0);
}

bool FixStrPosVal::operator>= (string Val_) {
	assert(valLen == Val_.length());
	unsigned char sVal[valLen];
	memcpy(sVal, Val_.c_str(), valLen);
	return (StrNCmp(value, sVal, valLen) >= 0);
}

bool FixStrPosVal::operator<= (string Val_) {
	assert(valLen == Val_.length());
	unsigned char sVal[valLen];
	memcpy(sVal, Val_.c_str(), valLen);
	return (StrNCmp(value, sVal, valLen) <= 0);
}

bool FixStrPosVal::operator== (string Val_) {
	assert(valLen == Val_.length());
	unsigned char sVal[valLen];
	memcpy(sVal, Val_.c_str(), valLen);
	return (StrNCmp(value, sVal, valLen) == 0);
}

bool FixStrPosVal::operator!= (string Val_) {
	assert(valLen == Val_.length());
	unsigned char sVal[valLen];
	memcpy(sVal, Val_.c_str(), valLen);
	return (StrNCmp(value, sVal, valLen) != 0);
}
*/
