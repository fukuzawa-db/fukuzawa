#include<iostream>
#include"PosVal.h"
#include"FloatPosVal.h"

using namespace std;

int main(){
	PosVal *pv1,*pv2;
	FloatPosVal a(3,54.3), *b;
	float x,y;

	x = 1234.342;
	y = 5678.432;

	a.printVal();
	cout << *(float *)a.value << " : a size = " << a.getSize() << " : a pos = " << a.position << endl;

	FloatPosVal c(a);
	c.printVal();
	cout << *(float *)c.value << " : c size = " << c.getSize() << " : c pos = " << c.position << endl;

	pv1 = a.clone();
	pv1->printVal();
	cout << *(float *)pv1->value << " : pv1 size = " << pv1->getSize() << " : pv1 pos = " << pv1->position << endl;

	a.set((unsigned char *)&x);
	a.printVal();
	cout << *(float *)a.value << " : a size = " << a.getSize() << " : a pos = " << a.position << endl;

	a.set(34,(unsigned char *)&x);
	a.printVal();
	cout << *(float *)a.value << " : a size = " << a.getSize() << " : a pos = " << a.position << endl;

	x = 89213.3;
	a.set(FLOAT,89,(unsigned char *)&x);
	a.printVal();
	cout << *(float *)a.value << " : a size = " << a.getSize() << " : a pos = " << a.position << endl;

	b = new FloatPosVal(5,y);
	b->printVal();
	cout << *(float *)b->value << " : b size = " << b->getSize() << " : b pos = " << b->position << endl;
	
	pv2 = c.clone();
	pv2->printVal();
	cout << *(float *)pv2->value << " : pv2 size = " << pv2->getSize() << " : pv2 pos = " << pv2->position << endl;

	cout << endl;

	if(a < b){cout << "NG";}
	else{cout << "OK";}
	if(c < b){cout << " : OK";}
	else{cout << " : NG";}
	if(c < pv1){cout << " : NG";}
	else{cout << " : OK";}
	if(*pv1 < pv2){cout << " : NG" << endl;}
	else{cout << " : OK" << endl;}

	if(a > b){cout << "OK";}
	else{cout << "NG";}
	if(c > b){cout << " : NG";}
	else{cout << " : OK";}
	if(c > pv1){cout << " : NG";}
	else{cout << " : OK";}
	if(*pv1 > pv2){cout << " : NG" << endl;}
	else{cout << " : OK" << endl;}

	if(a <= b){cout << "NG";}
	else{cout << "OK";}
	if(c <= b){cout << " : OK";}
	else{cout << " : NG";}
	if(c <= pv1){cout << " : OK";}
	else{cout << " : NG";}
	if(*pv1 <= pv2){cout << " : OK" << endl;}
	else{cout << " : NG" << endl;}

	if(a >= b){cout << "OK";}
	else{cout << "NG";}
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
}
