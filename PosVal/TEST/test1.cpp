#include<iostream>
#include<string>

using namespace std;

int main(){
	char *c;
	char str[12] ="abcdefghijk";
	string str1,str2;
	str1 = str;
	c = (char *)str1.c_str();
	cout << c << " : " << str1.length() << endl;

	str2 = str1;

	c = (char *)str2.c_str();
	cout << c << " : " << str2.length() << endl;

	return 0;
}
