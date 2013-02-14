#include<iostream>
#include<cstdlib>

#include "TableMaker.h"

int main(int argc, char *argv[])
{
	TableMaker *TMaker;

	if(argc != 2){
		cout << "Error plase input Table File|" << endl;
		cout << "Usage : " << argv[0] << " TableFile" << endl;
		exit(EXIT_FAILURE);
	}
	TMaker = new TableMaker();
	string fileName = argv[1];

	cout << "File Name is " << fileName << endl;
	cout << "\n========== TAbleMaker begin run ==========\n" << endl;

	TMaker->run(fileName);

	delete TMaker;

}
