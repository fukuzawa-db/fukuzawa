#include<iostream>
#include<string>

using namespace std;

int main(){
	char c[6];
	string *a,b;
	b = "abcdef";
	char d[9] = "abcdefgh";
	string str1(d, 4);
	cout << str1.c_str() << endl;

	memcpy(c, b.c_str(), b.length());
	cout << sizeof(double) << endl;
	cout << sizeof(float) << endl;
	cout << sizeof(long) << endl;
	cout << sizeof(int) << endl;
	
	string str = "abcd";
	a = new string(c, 6);

	cout << "string len = "<< str.length() << endl;
	cout << c << endl;
	cout << *a << endl;

	c[2] = 0;
	cout << c << endl;
	memset(c, 0, 6);
	cout << c[0];
	cout << '|' << c[1];
	cout << '|' << c[2];
	cout << '|' << c[3];
	cout << '|' << c[4];
	cout << '|' << c[5] << endl;
	return 0;
}
	
