#include<iostream>
#include<stdlib.h>
#include"PosVal.h"
#include"VarStrPosVal.h"

using namespace std;

int main(){
	PosVal *pv1,*pv2;
	VarStrPosVal a(3,256), *b;
	string x,y;

	x = "1234";
	y = "3567890234";

	char w[10];
	w[0] = '1';
	w[1] = '2';
	w[2] = '3';

	a.set((unsigned char *)w);
	cout << "a size = " << a.getSize() << " : a pos = " << a.position << " : value = ";
	a.printVal();

	a.set((unsigned char *)"asbcd");
	cout << "a size = " << a.getSize() << " : a pos = " << a.position << " : value = ";
	a.printVal();

	VarStrPosVal c(a);
	cout << "c size = " << c.getSize() << " : c pos = " << c.position << " : value = ";
	c.printVal();

	pv1 = a.clone();
	cout << "pv1 size = " << pv1->getSize() << " : pv1 pos = " << pv1->position << " : value = ";
	pv1->printVal();

	char str[pv1->getSize()];
	memcpy(str, pv1->value, sizeof(str));
	cout << str << endl;

	a.set((unsigned char *)x.c_str());
	cout << "a size = " << a.getSize() << " : a pos = " << a.position << " : value = ";
	a.printVal();

	a.set(34,(unsigned char *)x.c_str());
	cout << "a size = " << a.getSize() << " : a pos = " << a.position << " : value = ";
	a.printVal();

	x = "89213";
	a.set(VARIABLE_TEXT,89,(unsigned char *)x.c_str());
	cout << "a size = " << a.getSize() << " : a pos = " << a.position << " : value = ";
	a.printVal();


	b = new VarStrPosVal(5,50);
	b->set((unsigned char*)y.c_str());	
	cout << "b size = " << b->getSize() << " : b pos = " << b->position << " : value = ";
	b->printVal();
	
	pv2 = c.clone();
	cout << "pv2 bsize = " << pv2->getSize() << " : pv2 pos = " << pv2->position << " : value = ";
	pv2->printVal();

	cout << endl;

	if(a < b){cout << "NG";}
	else{cout << "OK";}
	if(c < b){cout << " : NG ";}
	else{cout << " : OK";}
	if(c < pv1){cout << " : NG";}
	else{cout << " : OK";}
	if(*pv1 < pv2){cout << " : NG" << endl;}
	else{cout << " : OK" << endl;}

	if(a > b){cout << "OK";}
	else{cout << "NG";}
	if(c > b){cout << " : OK";}
	else{cout << " : NG";}
	if(c > pv1){cout << " : NG";}
	else{cout << " : OK";}
	if(*pv1 > pv2){cout << " : NG" << endl;}
	else{cout << " : OK" << endl;}

	if(a <= b){cout << "NG";}
	else{cout << "OK";}
	if(c <= b){cout << " : NG";}
	else{cout << " : OK";}
	if(c <= pv1){cout << " : OK";}
	else{cout << " : NG";}
	if(*pv1 <= pv2){cout << " : OK" << endl;}
	else{cout << " : NG" << endl;}

	if(a >= b){cout << "OK";}
	else{cout << "NG";}
	if(c >= b){cout << " : OK";}
	else{cout << " : NG";}
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
