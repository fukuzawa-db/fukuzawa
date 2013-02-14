#include<iostream>
#include<string>
#include<cstdlib>
#include<cassert>

#include"CommonDataDef.h"

#include"Projection.h"
#include"AttributeManager.h"


int main(int argc, char *argv[]){
	chdir("../RunData");
	TABLE_REC tableRec;

	tableRec.tableID = 2;
	tableRec.attriNum = 4;

	ATTRIBUTE_REC attriRec[tableRec.attriNum];

	AttributeManager AM;
	AM.getForTableID(tableRec, attriRec);
	for(int i=0 ; i < (int)tableRec.attriNum ; i++){
		cout << attriRec[i].attributeName << endl;
	}

	unsigned int array[4] = {1,2,3,4};

	cout << "\n\n======================== strat test ==================================\n\n" << endl;

	Projection Pj = Projection(string("NATION.row"), attriRec, (unsigned int)(sizeof(attriRec)/sizeof(attriRec[0])), array, (unsigned int)(sizeof(array)/sizeof(array[0])), DB_OUT);
	Pj.exec();

	cout << "\n\n======================== end test ==================================\n\n" << endl;
}

	

