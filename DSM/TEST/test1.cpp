#include<iostream>
#include<fstream>
#include<string>

using namespace std;

int main(){
	ifstream ifs("a.txt");
	string str;
	ifs >> str;
	while(!ifs.eof()){
		cout << str << endl;
		ifs >> str;
	}
}
