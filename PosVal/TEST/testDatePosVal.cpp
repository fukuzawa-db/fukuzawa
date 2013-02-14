#include<iostream>
#include"PosVal.h"
#include"DatePosVal.h"

using namespace std;

int main(){
	PosVal *pv1,*pv2;
	DatePosVal a(3, (unsigned char *)"2010-04-05"), *b;
	unsigned char x[10],y[10];

	strncpy((char *)x, "2009-03-02", 10);
	strncpy((char *)y, "2012-09-30", 10);

	a.printVal();
	cout << *(unsigned int *)a.value << " : a size = " << a.getSize() << " : a pos = " << a.position << endl;

	DatePosVal c(a);
	c.printVal();
	cout << *(unsigned int *)c.value << " : c size = " << c.getSize() << " : c pos = " << c.position << endl;

	pv1 = a.clone();
	pv1->printVal();
	cout << *(unsigned int *)pv1->value << " : pv1 size = " << pv1->getSize() << " : pv1 pos = " << pv1->position << endl;

	a.set((unsigned char *)&x);
	a.printVal();
	cout << *(unsigned int *)a.value << " : a size = " << a.getSize() << " : a pos = " << a.position << endl;

	a.set(34,(unsigned char *)&x);
	a.printVal();
	cout << *(unsigned int *)a.value << " : a size = " << a.getSize() << " : a pos = " << a.position << endl;

	strncpy((char *)x, "2009-12-21", 10);
	a.set(DATE,89,(unsigned char *)&x);
	a.printVal();
	cout << *(unsigned int *)a.value << " : a size = " << a.getSize() << " : a pos = " << a.position << endl;

	b = new DatePosVal(5,y);
	b->printVal();
	cout << *(unsigned int *)b->value << " : b size = " << b->getSize() << " : b pos = " << b->position << endl;
	
	pv2 = c.clone();
	pv2->printVal();
	cout << *(unsigned int *)pv2->value << " : pv2 size = " << pv2->getSize() << " : pv2 pos = " << pv2->position << endl;

	cout << endl;

	*pv1 = a;
	pv1->printVal();
	cout << pv1->value << " : pv1 size = " << pv1->getSize() << " : pv1 pos = " << pv1->position << endl;
	*pv1 = *b;
	pv1->printVal();
	cout << pv1->value << " : pv1 size = " << pv1->getSize() << " : pv1 pos = " << pv1->position << endl;
	*pv1 = *pv2;
	pv1->printVal();
	cout << pv1->value << " : pv1 size = " << pv1->getSize() << " : pv1 pos = " << pv1->position << endl;
/*
	if(a < b){cout << "OK";}
	else{cout << "NG";}
	if(c < b){cout << " : OK";}
	else{cout << " : NG";}
	if(c < pv1){cout << " : NG";}
	else{cout << " : OK";}
	if(*pv1 < pv2){cout << " : NG" << endl;}
	else{cout << " : OK" << endl;}

	if(a > b){cout << "NG";}
	else{cout << "OK";}
	if(c > b){cout << " : NG";}
	else{cout << " : OK";}
	if(c > pv1){cout << " : NG";}
	else{cout << " : OK";}
	if(*pv1 > pv2){cout << " : NG" << endl;}
	else{cout << " : OK" << endl;}

	if(a <= b){cout << "OK";}
	else{cout << "NG";}
	if(c <= b){cout << " : OK";}
	else{cout << " : NG";}
	if(c <= pv1){cout << " : OK";}
	else{cout << " : NG";}
	if(*pv1 <= pv2){cout << " : OK" << endl;}
	else{cout << " : NG" << endl;}

	if(a >= b){cout << "NG";}
	else{cout << "OK";}
	if(c >= b){cout << " : NG";}
	else{cout << " : OK";}
	if(c >= pv1){cout << " : OK";}
	else{cout << " : NG";}
	if(*pv1 >= pv2){cout << " : OK" << endl;}
	else{cout << " : NG" << endl;}

	if(a == b){cout << "NG";}
	else{cout << "OK";}
	if(c == b){cout << " : NG";}
	else{cout << " : OK";}
	if(c == pv1){cout << " : OK";}
	else{cout << " : NG";}
	if(*pv1 == pv2){cout << " : OK" << endl;}
	else{cout << " : NG" << endl;}

	if(a != b){cout << "OK";}
	else{cout << "NG";}
	if(c != b){cout << " : OK";}
	else{cout << " : NG";}
	if(c != pv1){cout << " : NG";}
	else{cout << " : OK";}
	if(*pv1 != pv2){cout << " : NG" << endl;}
	else{cout << " : OK" << endl;}
*/
}
