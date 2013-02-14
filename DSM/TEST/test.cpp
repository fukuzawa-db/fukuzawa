#include<iostream>
#include<string>
#include<cstdlib>
#include<stdio.h>
#include<fstream>

using namespace std;

int main(){
/*	string str;
	string file = "a.txt";
	ifstream ifs;

	ifs.open(file.c_str());
	//ifs = new ifstream(file.c_str());
	ifs >> str;
	while(!ifs.eof()) {
		cout << str << endl;;
		ifs >> str;
	}
*/
	unsigned short a = 2;
	std::cout.write((char *)&a,sizeof(unsigned short));	
	cout << endl;
}
