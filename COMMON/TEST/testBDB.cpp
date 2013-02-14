#include<iostream>
#include<string>
#include<cstdlib>

#include"BDBOpe.h"

using namespace std;

int main(){
	BDBOpe	BDBFile1("t1", false);
	BDBOpe *BDBFile2;

	BDBFile2 = new BDBOpe("t2");
	
	cout << "BDBFile Open!" << endl;

	BDBFile1.open();
	BDBFile2->open();

	cout << "Record Count t1 = " << BDBFile1.getRecordCount() << endl;
	cout << "Record Count t2 = " << BDBFile2->getRecordCount() << endl; 
	BDBFile1.dumpDB();
	BDBFile2->showRecordCount();

	char *key = "abcdefghijk";
	char *data = "ABCDEFGHIJK";
	if(BDBFile1.writeRecord(key, strlen(key), data, strlen(data), true)!= 0)
		cout << "writeError!" << endl;



	BDBFile1.dumpDB();
	cout << "BDBFile Close!" << endl;

	BDBFile1.close();
	BDBFile2->close();

	delete BDBFile2;
}

