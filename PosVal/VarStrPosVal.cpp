#include"VarStrPosVal.h"

using namespace std;

VarStrPosVal::VarStrPosVal(){
	type = VARIABLE_TEXT;
	position = 0;
	maxLen = 0;
	valLen = 0;
	value = NULL;
}

VarStrPosVal::VarStrPosVal(unsigned int pos_, unsigned short maxLen_){
	type = VARIABLE_TEXT;
	position = pos_;
	maxLen = maxLen_;
	valLen = 0;
	value = NULL;
}

VarStrPosVal::VarStrPosVal(VarStrPosVal& posVal_){
	assert(posVal_.type == VARIABLE_TEXT);
	type = posVal_.type;
	position = posVal_.position;
	maxLen = posVal_.maxLen;
	valLen = strlen((char *)posVal_.value);
	value = new unsigned char[strlen((char *)posVal_.value) + 1];
	strcpy((char *)value, (char *)posVal_.value);
}

VarStrPosVal::~VarStrPosVal(){
	if(value != NULL)delete value;
	//if(sValue != NULL)delete sValue;
}

PosVal *VarStrPosVal::clone(){
	PosVal *newPosVal = new VarStrPosVal(*this);
	return newPosVal;
}

unsigned short VarStrPosVal::getSize(){
	//assert(valLen > 0);
	return valLen;
}

void VarStrPosVal::set(unsigned char *value_){
	assert(maxLen > 0);
	assert(maxLen >= strlen((char *)value_));
	valLen = strlen((char *)value_);
	if(value != NULL){delete value;}
	value = new unsigned char[strlen((char *)value_) + 1];
	strcpy((char *)value, (char *)value_);

}

void VarStrPosVal::set(unsigned int pos_, unsigned char *value_){
	position = pos_;
	assert(maxLen > 0);
	assert(maxLen >= strlen((char *)value_));
	valLen = strlen((char *)value_);
	if(value != NULL){delete value;}
	value = new unsigned char[strlen((char *)value_) + 1];
	strcpy((char *)value, (char *)value_);
}

void VarStrPosVal::set(DataType dataType_, unsigned int pos_, unsigned char *value_){
	assert(dataType_ == VARIABLE_TEXT);
	type = dataType_;
	position = pos_;
	assert(maxLen > 0);
	assert(maxLen >= strlen((char *)value_));
	valLen = strlen((char *)value_);
	if(value != NULL)delete value;
	value = new unsigned char[strlen((char *)value_) + 1];
	strcpy((char *)value, (char *)value_);
}

/*
void VarStrPosVal::setStr(string str_){
	assert(str_.length() <= maxLen);
	sValue = str_;
	valLen = sValue.length();
	value = (unsigned char *)sValue.c_str();
}


void VarStrPosVal::setStr(unsigned int pos_, string str_){
	assert(str_.length() <= maxLen);
	position = pos_;
	sValue = str_;
	valLen = sValue.length();
	value = (unsigned char *)sValue.c_str();
}
*/

void VarStrPosVal::setLength(unsigned short maxLen_){
	maxLen = maxLen_;
}

void VarStrPosVal::printVal(){
	//std::cout << value << std::endl;
	std::cout << (char *)value;
}

PosVal &VarStrPosVal::operator= (const PosVal& posVal_){
	assert(posVal_.type == VARIABLE_TEXT);
	type = posVal_.type;
	position = ((VarStrPosVal &)posVal_).position;
	maxLen = ((VarStrPosVal &)posVal_).maxLen;
	valLen = ((VarStrPosVal &)posVal_).valLen;
	if(value != NULL){delete value;}
	value = new unsigned char[strlen((char *)((VarStrPosVal &)posVal_).value) + 1];
	strcpy((char *)value, (char *)((VarStrPosVal &)posVal_).value);
	return *this;
}

bool VarStrPosVal::operator> (PosVal* posVal_) {
	assert(posVal_->type == VARIABLE_TEXT);
	//assert(valLen >= 0);
	return (strcmp((char *)value, (char *)posVal_->value) > 0);
}

bool VarStrPosVal::operator< (PosVal* posVal_) {
	assert(posVal_->type == VARIABLE_TEXT);
	//assert(valLen >= 0);
	return (strcmp((char *)value, (char *)posVal_->value) < 0);
}

bool VarStrPosVal::operator>= (PosVal* posVal_) {
	assert(posVal_->type == VARIABLE_TEXT);
	//assert(valLen >= 0);
	return (strcmp((char *)value, (char *)posVal_->value) >= 0);
}

bool VarStrPosVal::operator<= (PosVal* posVal_) {
	assert(posVal_->type == VARIABLE_TEXT);
	//assert(valLen >= 0);
	return (strcmp((char *)value, (char *)posVal_->value) <= 0);
}

bool VarStrPosVal::operator== (PosVal* posVal_) {
	assert(posVal_->type == VARIABLE_TEXT);
	//assert(valLen >= 0);
	return (strcmp((char *)value, (char *)posVal_->value) == 0);
}

bool VarStrPosVal::operator!= (PosVal* posVal_) {
	assert(posVal_->type == VARIABLE_TEXT);
	//assert(valLen >= 0);
	return (strcmp((char *)value, (char *)posVal_->value) != 0);
}
/*
bool VarStrPosVal::operator> (string Val_) {
	assert(valLen > 0);
	return (sValue > Val_);
}

bool VarStrPosVal::operator< (string Val_) {
	assert(valLen > 0);
	return (sValue < Val_);
}

bool VarStrPosVal::operator>= (string Val_) {
	assert(valLen > 0);
	return (sValue >= Val_);
}

bool VarStrPosVal::operator<= (string Val_) {
	assert(valLen > 0);
	return (sValue <= Val_);
}

bool VarStrPosVal::operator== (string Val_) {
	assert(valLen > 0);
	return (sValue == Val_);
}

bool VarStrPosVal::operator!= (string Val_) {
	assert(valLen > 0);
	return (sValue != Val_);
}
*/
