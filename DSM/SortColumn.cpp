#include"SortColumn.h"

SortColumn::SortColumn(string fileName_, ATTRIBUTE_REC *attriRec_){
	fileName = fileName_;
	attriRec = attriRec_;
}

SortColumn::~SortColumn(){
}

string SortColumn::exec(){
	sprintf(buf, "tmpFile-%d.%d", attriRec->tableID, attriRec->attributeID);
	string tmpFile = buf;
	cout << tmpFile << endl;

	if((attriRec->dataType != FIXED_TEXT) && (attriRec->dataType != VARIABLE_TEXT) && (attriRec->dataType != DATE)){
		sprintf(buf, "nl %s | sort -n -k 2 > %s", fileName.c_str(), tmpFile.c_str());
		execStr = buf;
		cout << execStr << endl;
	}
	else if(attriRec->dataType != FIXED_TEXT || attriRec->dataType != DATE){
		sprintf(buf, "nl %s | sort -k 2 > %s", fileName.c_str(), tmpFile.c_str());
		execStr = buf;
		cout << execStr << endl;
	}
	else{
		cout << "VARIABLE_TEXT is illigal type in SortColumn" << endl;
		exit(EXIT_FAILURE);
	}
	
	system(execStr.c_str());
	
	sprintf(buf, "numFile-%d.%d", attriRec->tableID, attriRec->attributeID);
	string numFile = buf;

	sprintf(buf, "dataFile-%d.%d", attriRec->tableID, attriRec->attributeID);
	string dataFile = buf;

	sprintf(buf, "awk '{print $1}' %s > %s", tmpFile.c_str(), numFile.c_str());
	execStr = buf;
	system(execStr.c_str());

	sprintf(buf, "cut -f2- %s > %s", tmpFile.c_str(), dataFile.c_str());
	execStr = buf;
	system(execStr.c_str());
	
	sprintf(buf, "rm %s", tmpFile.c_str());
	execStr = buf;
	system(execStr.c_str());


	sprintf(buf, "%d.%d-to-%d.0.JoinIndex", attriRec->tableID, attriRec->attributeID, attriRec->tableID);
	string joinIndex = buf;

	Db = new BDBOpe(joinIndex);
	Db->open();
	BareEncode *encode = new BareEncode(numFile, INT, (unsigned short)sizeof(int));


	while(encode->getBuffer(buffer, &bufSize, &key) != NULL){
		Db->writeRecord(&key, sizeof(key), buffer, bufSize, false);
	}
/*
	ofstream ofs("debug.txt");
	while(encode->getBuffer(buffer, &bufSize, &key) != NULL){
		ofs.write((char *)buffer, bufSize);
		Db->writeRecord(&key, sizeof(key), buffer, bufSize, false);
	}
*/

	Db->close();
	delete Db;
	delete encode;

	sprintf(buf, "rm %s", numFile.c_str());
	execStr = buf;
	system(execStr.c_str());
	

	return dataFile;

}

