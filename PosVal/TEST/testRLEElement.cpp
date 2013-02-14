#include<iostream>
#include<string>

#include"RLEElement.h"
#include"IntPosVal.h"

using namespace std;

int main(){
	RLEElement *b;
	PosVal *c;

	c = new IntPosVal(4,54);
	c->printVal();
	
	RLEElement x, a = RLEElement(c, 4, 7);
	cout << "a.pos = " << a.startPos << " a.rep = " << a.repeat << " a.value = " << *(int *)a.value->value << endl;
	a.value->printVal();

	b = new RLEElement(a);
	cout << "b.pos = " << b->startPos << " b.rep = " << b->repeat << " b.value = " << *(int *)b->value->value << endl;
	if(x.isNull() == true)cout << "OK" << endl;
	else cout << "NG" << endl;
}
