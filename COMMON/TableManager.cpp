#include<iostream>
#include<fstream>
#include"TableManager.h"

using namespace std;

TableManager::TableManager() : tableFileName(TABLE_MANEGE_FILE), dbTableFileName(BDB_TABLE_MANEGE_FILE)
{
	db = new BDBOpe(dbTableFileName);
	assert(db != NULL);
	int err = db->open();
	if(err != 0){
		cerr << "TableFile open error#" << err << endl;
		exit(1);
	}
}

TableManager::TableManager(DbEnv *env_) : tableFileName(TABLE_MANEGE_FILE), dbTableFileName(BDB_TABLE_MANEGE_FILE)
{
	db = new BDBOpe(env_, dbTableFileName);
	assert(db != NULL);
	int err = db->open();
	if(err != 0){
		cerr << "TableFile open error#" << err << endl;
		exit(1);
	}
}

TableManager::~TableManager()
{
	if(db != NULL){ 
		db->close();
		delete db;
	}
}		

int TableManager::writeRecord(TABLE_REC *tableRec_)
{
	char buffer[sizeof(TABLE_REC)];
	ofstream outfile(tableFileName.c_str(), ios_base::out | ios_base::app);
	outfile << tableRec_->tableName << "|" << tableRec_->attriNum << "|" << tableRec_->tableID << endl;

	memcpy(buffer, &tableRec_->tableID, sizeof(unsigned int));
	memcpy(buffer + sizeof(unsigned int), &tableRec_->attriNum, sizeof(unsigned int));
	memcpy(buffer + sizeof(unsigned int) * 2, tableRec_->tableName, strlen(tableRec_->tableName) +1 );
	outfile.close();
	int returnCode = db->writeRecord(&tableRec_->tableID, (unsigned int)sizeof(tableRec_->tableID), buffer, sizeof(int) + strlen(tableRec_->tableName) + 1, false);

	if(returnCode != 0){
		cerr << "tableDB->writeRecord error:" << returnCode << endl;
		exit(1);
	}
	return 0;
}

void TableManager::showAllRecord(){
	key = new Dbt;
	data = new Dbt;
	int k_data;
	TABLE_REC d_data;
	while(db->readNextRecord(key, data) == 0){
		k_data = *(int *)key->get_data();
		memcpy(&d_data, data->get_data(), data->get_size());
		cout << "dataSize = " << data->get_size();
		cout << " : key = " << k_data;
		cout << ", tableID = " << d_data.tableID << ", attriNum = " << d_data.attriNum << ", tableName = " << d_data.tableName << endl;
	}
	delete key;
	delete data;
}

