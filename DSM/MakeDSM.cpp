#include"MakeDSM.h"

using namespace std;

MakeDSM::MakeDSM(string fileName_, ATTRIBUTE_REC *attriRec_){
	fileName = fileName_;
	attriRec = attriRec_;
	
	//DSMファイルの作成
	char str[BUFFER_SIZE];
	sprintf(str, "%d.%d.DSM", attriRec->tableID, attriRec->attributeID);
	DbName = string(str);
}

MakeDSM::~MakeDSM(){}

void MakeDSM::run(){
		//非圧縮ファイルの作成
	encode = new BareEncode(fileName, attriRec->dataType, attriRec->dataLength);

	Db = new BDBOpe(DbName, true);
	Db->open();
#ifdef DEBUG
	ofstream ofs("DEBUG_DSM");
#endif
	while(encode->getBuffer(buffer, &bufSize, &key) != NULL){
		Db->writeRecord(&key, sizeof(key), buffer, bufSize, false);
#ifdef DEBUG
		ofs.write((char *)buffer, bufSize);
#endif
	}

	Db->close();
	delete Db;
	delete encode;
	
	//インデックスファイルの作成
	
	if(attriRec->isIndex == true){
		char str[BUFFER_SIZE];
		sprintf(str, "%d.%d.index", attriRec->tableID, attriRec->attributeID);
		DbName = string(str);
		Db = new BDBOpe(DbName, false);
		
		switch(attriRec->dataType){
			case INT:
				break;

			case LONG:
				Db->setLongCmp();
				break;

			case FLOAT:
				Db->setFloatCmp();
				break;

			case DOUBLE:
				Db->setDoubleCmp();
				break;

			case FIXED_TEXT:
				Db->setfStrCmp();
				break;

			case VARIABLE_TEXT:
				Db->setvStrCmp();
				break;
	
			case DATE:
				Db->setfStrCmp();
				break;

			default:
				cout << "ERROR : illegal DataType ; IndexEncode" << endl;
				exit(EXIT_FAILURE);
		}
		Db->open();
		
		encode = new IndexEncode(fileName, attriRec->dataType, attriRec->dataLength);
		key = 1;
		while(encode->getBuffer(buffer, &bufSize, NULL) != NULL){
			Db->writeRecord(buffer, bufSize, &key, sizeof(key), true);
			key++;
		}

		Db->close();
		delete Db;
		delete encode;
	}
	
	//圧縮ファイルの作成
	if(attriRec->isCompress == true){
		char str[BUFFER_SIZE];
		sprintf(str, "%d.%d.DSM_C", attriRec->tableID, attriRec->attributeID);
		DbName = string(str);
		Db = new BDBOpe(DbName, true);
		Db->open();
	
		if(attriRec->isSort == false){
			//ソートしていないファイルをソート
			string sortFile;
			SortColumn sortC = SortColumn(fileName, attriRec);
			sortFile = sortC.exec();
			fileName = sortFile;
		}
		//圧縮ファイルの作成
		encode = new RLEEncode(fileName, attriRec->dataType, attriRec->dataLength);
	
		while(encode->getBuffer(buffer, &bufSize, &key) != NULL){
			Db->writeRecord(&key, sizeof(key), buffer, bufSize, false);
		}
		if(attriRec->isSort == false){
			char exec[256];
			sprintf(exec, "rm %s", fileName.c_str());
			system(exec);
		}
		Db->close();
		delete Db;
		delete encode;
	}
	

}	
