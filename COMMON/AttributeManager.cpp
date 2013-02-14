#include<iostream>
#include<string>
#include<fstream>
#include<cstdlib>
#include<cassert>

#include"AttributeManager.h"

using namespace std;

AttributeManager::AttributeManager() : attributeFileName(ATTRIBUTE_MANEGE_FILE), dbAttributeFileName(BDB_ATTRIBUTE_MANEGE_FILE)
{
	db = new BDBOpe(dbAttributeFileName);
	assert(db != NULL);
	int err = db->open();
	if(err != 0){
		cerr << "AttributeFile open error#" << err << endl;
		exit(1);
	}
}

AttributeManager::AttributeManager(DbEnv *env_) : attributeFileName(ATTRIBUTE_MANEGE_FILE), dbAttributeFileName(BDB_ATTRIBUTE_MANEGE_FILE)
{
	db = new BDBOpe(env_, dbAttributeFileName);
	assert(db != NULL);
	int err = db->open();
	if(err != 0){
		cerr << "AttributeFile open error#" << err << endl;
		exit(1);
	}
}


AttributeManager::~AttributeManager()
{
	if(db != NULL){
		db->close();
		delete db;
	}
}

int AttributeManager::writeRecord(ATTRIBUTE_REC *attributeRec_)
{
	unsigned char buffer[sizeof(ATTRIBUTE_REC)];
	int pos = 0;

	ofstream outfile(attributeFileName.c_str(), ios_base::out | ios_base::app);
	outfile << attributeRec_->attributeName << '|' << attributeRec_->tableID << '|' << attributeRec_->attributeID 
			<< '|' << attributeRec_->dataType << '|' << attributeRec_->dataLength << '|'  << attributeRec_->primary
			<< '|' << attributeRec_->isCompress << '|' << attributeRec_->isSort << '|' << attributeRec_->isIndex << 				endl;
	outfile.close();

	memcpy(buffer + pos, attributeRec_->attributeName, strlen(attributeRec_->attributeName) + 1); 
	pos += strlen(attributeRec_->attributeName)  + 1;
	memcpy(buffer + pos, &attributeRec_->tableID, sizeof(unsigned int));
	pos += sizeof(unsigned int);
	memcpy(buffer + pos, &attributeRec_->attributeID, sizeof(unsigned int));
	pos += sizeof(unsigned int);
	memcpy(buffer + pos, &attributeRec_->dataType, sizeof(DataType));
	pos += sizeof(DataType);
	memcpy(buffer + pos, &attributeRec_->dataLength, sizeof(unsigned int));
	pos += sizeof(unsigned int);
	memcpy(buffer + pos, &attributeRec_->primary, sizeof(bool));
	pos += sizeof(bool);
	memcpy(buffer + pos, &attributeRec_->isCompress, sizeof(bool));
	pos += sizeof(bool);
	memcpy(buffer + pos, &attributeRec_->isSort , sizeof(bool));
	pos += sizeof(bool);
	memcpy(buffer + pos, &attributeRec_->isIndex , sizeof(bool));
	pos += sizeof(bool);

	unsigned int attriKey = ((attributeRec_->tableID << 16) | attributeRec_->attributeID);
	int returnCode = db->writeRecord(&attriKey, sizeof(attriKey), buffer, (unsigned int)pos, false);

	if(returnCode != 0){
		cerr << "tableDB->writeRecord error:" << returnCode << endl;
		exit(1);
	}
	return 0;
}


int AttributeManager::getForTableID(TABLE_REC tableRec_, ATTRIBUTE_REC *attriRec_){
	unsigned int tableID = tableRec_.tableID;
	unsigned int attriNum = tableRec_.attriNum;
	Dbt key, data;
	unsigned char buffer[sizeof(ATTRIBUTE_REC)];

	for(int i = 0; i < (int)attriNum; i++){
		unsigned int attriKey = ((tableID << 16) | (i+1));
		int pos = 0;
		key.set_data(&attriKey);
		key.set_size(sizeof(attriKey));
		data.set_data(buffer);
		data.set_ulen(sizeof(buffer));
		data.set_flags(DB_DBT_USERMEM);

		db->readForKey(&key, &data);

		strcpy(attriRec_[i].attributeName, ((char*)data.get_data() + pos));
		pos += strlen(attriRec_[i].attributeName) + 1;
		memcpy(&attriRec_[i].tableID, (char *)data.get_data() + pos, sizeof(unsigned int));
		pos += sizeof(unsigned int);
		memcpy(&attriRec_[i].attributeID, (char *)data.get_data() + pos, sizeof(unsigned int));
		pos += sizeof(unsigned int);
		memcpy(&attriRec_[i].dataType, (char *)data.get_data() + pos, sizeof(DataType));
		pos += sizeof(DataType);
		memcpy(&attriRec_[i].dataLength, (char *)data.get_data() + pos, sizeof(unsigned int));
		pos += sizeof(unsigned int);
		memcpy(&attriRec_[i].primary, (char *)data.get_data() + pos, sizeof(bool));
		pos += sizeof(bool);
		memcpy(&attriRec_[i].isCompress, (char *)data.get_data() + pos, sizeof(bool));
		pos += sizeof(bool);
		memcpy(&attriRec_[i].isSort, (char *)data.get_data() + pos, sizeof(bool));
		pos += sizeof(bool);
		memcpy(&attriRec_[i].isIndex, (char *)data.get_data() + pos, sizeof(bool));
		pos += sizeof(bool);
	}
	return 0;
}

void AttributeManager::showAllRecord(){
	Dbt *key = new Dbt;
	Dbt *data = new Dbt;
	int k_data;
	ATTRIBUTE_REC d_data;
	int pos;

	while(db->readNextRecord(key, data) == 0){
		pos = 0;
		k_data = *(int *)key->get_data();
		strcpy(d_data.attributeName, ((char*)data->get_data() + pos));
		pos += strlen(d_data.attributeName) + 1;
		memcpy(&d_data.tableID, (char *)data->get_data() + pos, sizeof(unsigned int));
		pos += sizeof(unsigned int);
		memcpy(&d_data.attributeID, (char *)data->get_data() + pos, sizeof(unsigned int));
		pos += sizeof(unsigned int);
		memcpy(&d_data.dataType, (char *)data->get_data() + pos, sizeof(DataType));
		pos += sizeof(DataType);
		memcpy(&d_data.dataLength, (char *)data->get_data() + pos, sizeof(unsigned int));
		pos += sizeof(unsigned int);
		memcpy(&d_data.primary, (char *)data->get_data() + pos, sizeof(bool));
		pos += sizeof(bool);

		
		cout << "dataSize = " << data->get_size() << " : " << pos << endl;
		cout << "key = " << k_data;
		cout << ", attriName = " << d_data.attributeName << ", tableID = " << d_data.tableID << " , attriID = " << d_data.attributeID << ", dataType = " 
			<< d_data.dataType<< ", Length = " << d_data.dataLength << ", primary = " << d_data.primary << endl;
	}
	delete key;
	delete data;
}

