#include<iostream>
#include<fstream>

int main(){
	ifstream ifs("data3.txt");


	float f;
	double d;

		ifs >> f;
		ifs >> d;
	while(!ifs.eof()){
		cout.write((char *)&f, sizeof(float));
		cout.write((char *)&d, sizeof(double));
		ifs >> f;
		ifs >> d;
		cout << endl;
	}
}
