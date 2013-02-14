#include"OutPut.h"

using namespace std;

OutPut::OutPut(OUT_FLAG outFlag_){
	outFlag = outFlag_;
	outDb = NULL;
	count = -1;
}

OutPut::OutPut(OUT_FLAG outFlag_, BDBOpe *outDb_){
	outFlag = outFlag_;
	outDb = outDb_;
	count = -1;
}

OutPut::~OutPut(){}

void OutPut::setOutCount(int count_){
	count = count_;
}

void OutPut::init(DbEnv *env_){
	env = env_;
	assert(preOperator != NULL);
	if(outFlag == TIME_OUT){
		t.start();
	}
	preOperator->init(env);
	if(outFlag == TIME_OUT){
		t.stop();
	}
	assert(preOperator != NULL);
	attriNum = preOperator->getAttriNum();
	initAttriRec(attriNum);
	preOperator->getAttriRec(attriRec, attriNum);
	initPosVal();
}

void OutPut::exec(){
	if(outFlag == TIME_OUT){
		timeOut();
	}
	if(count >= 0){
		countOut();
	}else{
		allOut();
	}
}

void OutPut::countOut(){
	int returnCode;
	for(int i = 0; i < count; i++){
		returnCode = getRow(pv, attriNum);
		if(returnCode != 0)
			break;
	}
}

void OutPut::timeOut(){
	int returnCode;

	t.start();
	while(1){
		returnCode = preOperator->getRow(pv, attriNum);
		if(returnCode != 0)
			break;
	}
	t.stop();
	t.showTime("time-out");
}

void OutPut::allOut(){
	int returnCode;
	int i=0;
	for(;;){
		returnCode = preOperator->getRow(pv, attriNum);
		if(returnCode != 0)
			break;
		if(outFlag == STD_OUT){
			i++;
			for(unsigned int index = 0; index < attriNum ; index++){
				pv[index]->printVal();
				cout << '|';
			}
			cout << endl;
		}
	}
}

int OutPut::getRow(PosVal **pv_, unsigned int pvNum_){
	cout << "Error not define this function in OutPut" << endl;
	exit(-1);
}

unsigned int OutPut::getAttriNum(void){
	cout << "Error not define this function in OutPut" << endl;
	exit(-1);
}

void OutPut::getAttriRec(ATTRIBUTE_REC **attriRec_, unsigned int attriNum){
	cout << "Error not define this function in OutPut" << endl;
	exit(-1);
}
