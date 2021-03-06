#include"TableMaker.h"

using namespace std;

TableMaker::TableMaker(){
}

TableMaker::~TableMaker(){
}

int TableMaker::run(string FileName_){

	string tName;

	cout << "Please enter the table name" << endl;
	cin >> tName;
	while(tName.length() >= MAX_NAME_LENGTH){
		cout << "Too long length!" << endl;
		cout << "Please enter the table name agein" << endl;
		cin >> tName;
	}
	cout << "Table name is " << tName << endl;

	cout << "How many attributes are in this table?" << endl;
	cin >> numAttribute;
	if(numAttribute < 1 || numAttribute > MAX_ATTRIBUTE_NUM){
		cout << "Num Attributes must be between 1 and " << MAX_ATTRIBUTE_NUM << "." << endl;
		return EXIT_FAILURE;
	}
	
	attriDatas = new void*[numAttribute];
	attriRecs = new ATTRIBUTE_REC[numAttribute];
	tID = TableFile.getNextID();

	int typeNum;	
	char isPrimary;
	for(int i=0; i < numAttribute; i++){
		cout << "Please enter the name of Attribute: " << (i+1) << endl;
		cin >> attriRecs[i].attributeName;
		attriRecs[i].tableID = tID;
		attriRecs[i].attributeID = i + 1;
		while(1){
			cout << "Which is data type of " << attriRecs[i].attributeName << " ?" << endl;
			cout << "1 : Integer" << endl;
			cout << "2 : Long Integer" << endl;
			cout << "3 : Decimal" << endl;
			cout << "4 : Big Decimal" << endl;
			cout << "5 : Fixed Text" << endl;
			cout << "6 : Variable Text" << endl;
			cout << "7 : Date" << endl;
			cout << "Pease enter number : ";
			cin >> typeNum;
			if(0 < typeNum  && 	typeNum < 8) break;
			cout << "Error number! Please again." << endl;
		}
		while(1){
			cout << attriRecs[i].attributeName << " is primary key?" << endl;
			cout << "(y,n):";
			cin >> isPrimary;
			if(isPrimary == 'y' || isPrimary == 'Y' || isPrimary == 'n' || isPrimary == 'N')
				break;
			cout << "Error input! Please again." << endl;
		}

		setAttriInf(i, typeNum, isPrimary);
	}

	strcpy(tableRec.tableName, tName.c_str());
	tableRec.tableID = tID;
	TableFile.writeRecord(&tableRec);
	
	for(int i=0; i < numAttribute; i++)
		AttriFile.writeRecord(&attriRecs[i]);

	insertTable(FileName_);

	return EXIT_SUCCESS;
}
	



void TableMaker::setAttriInf(int i_, int typeNum_, char isPrimary_){
	assert(0 < typeNum_ && typeNum_ < 8);

	switch(isPrimary_){
		case 'y':
		case 'Y':
			attriRecs[i_].primary = true;
			break;

		case 'n':
		case 'N':
			attriRecs[i_].primary = false;
			break;

		default:
			cout << "Error setAttribute!" << endl;
			exit (1);
	}

	unsigned int textSize = 0;

	switch(typeNum_){
		case 1:
			attriRecs[i_].dataType = INT;
			attriRecs[i_].dataLength = sizeof(int);
			attriDatas[i_] = new int;	
			break;

		case 2:
			attriRecs[i_].dataType = LONG;
			attriRecs[i_].dataLength = sizeof(long);
			attriDatas[i_] = new long;
			break;

		case 3:
			attriRecs[i_].dataType = FLOAT;
			attriRecs[i_].dataLength = sizeof(float);
			attriDatas[i_] = new float;
			break;

		case 4:
			attriRecs[i_].dataType = DOUBLE;
			attriRecs[i_].dataLength = sizeof(double);
			attriDatas[i_] = new double;
			break;

		case 5:
			attriRecs[i_].dataType = FIXED_TEXT;
			while(1){
				cout << "Please enter fixed text size of " << attriRecs[i_].attributeName << ":";
				cin >> textSize;
				if(0 < textSize && textSize < UINT_MAX)break;
				cout << "Error number! Please enter again.";
			}
			assert(0 < textSize && textSize < UINT_MAX);
			attriRecs[i_].dataLength = textSize;
			attriDatas[i_] = new char[textSize];
			break;

		case 6:
			attriRecs[i_].dataType = VARIABLE_TEXT;
			while(1){
				cout << "Please enter variable text size of " << attriRecs[i_].attributeName << ":";
				cin >> textSize;
				if(0 < textSize && textSize < UINT_MAX)break;
				cout << "Error number! Please enter again.";
			}
			assert(0 < textSize && textSize < UINT_MAX);
			attriRecs[i_].dataLength = textSize;
			attriDatas[i_] = new char[textSize + 1];
			break;

		case 7:
			attriRecs[i_].dataType = DATE;
			attriRecs[i_].dataLength = unsigned int;
			attriDatas[i_] = new unsigned int;
			break;

		default:
			cout << "Error setAttribute!" << endl;
			exit (1);
	}
}

void TableMaker::insertTable(string FileName_)
{
	string buffer;
	int end_pos;
	FileName = FileName_;
	int returnCode;

	std::ifstream inFile(FileName.c_str());
	if(inFile.fail()){
		cerr << "Error: Could not open  " << FileName << endl;
		exit(EXIT_FAILURE);
	}
	
	string BDBName = tableRec.tableName;
	BDBName += ".row";
	BDBOpe BDBFile(BDBName);
	BDBFile.open();

	//unsigned int keySize;
	unsigned int dataSize;
	//unsigned int keyBufSize = getKeyBufSize();
	unsigned int dataBufSize = getDataBufSize();
	//char keyBuffer[keyBufSize];
	char dataBuffer[dataBufSize];
	unsigned int keyIdentify = 1;
	
	while(getline(inFile, buffer)){
		returnCode = 0;
		for(int i= 0; i < numAttribute; i++){
			end_pos = buffer.find(PAUSE);
			returnCode = insertVoidData(i, buffer.substr(0, end_pos));
			if(returnCode != 0)break;
			buffer = buffer.substr(end_pos+1);
		}
		if(returnCode != 0){
			cout << "Wrong Data type : " << buffer << endl;
			continue;
		}
		//keySize = getKey(keyBuffer, keyBufSize);
		dataSize = getData(dataBuffer, dataBufSize);
		
		BDBFile.writeRecord(&keyIdentify, sizeof(keyIdentify), dataBuffer, dataSize, false);
		keyIdentify += 1;
	}
	
	BDBFile.close();
	inFile.close();
}
	
unsigned int TableMaker::getKeyBufSize(){
	int size = 0;
	for(int i = 0; i < numAttribute; i++){
		if(attriRecs[i].primary == true){
			size += attriRecs[i].dataLength;
			if(attriRecs[i].dataType == VARIABLE_TEXT)size++;
		}
	}
	return size;
}

unsigned int TableMaker::getDataBufSize()
{
	int size = 0;
	for(int i = 0; i < numAttribute; i++){
		size += attriRecs[i].dataLength;
		if(attriRecs[i].dataType == VARIABLE_TEXT)size++;
	}
	return size;
}

int TableMaker::insertVoidData(int i_, string str_)
{
	
	switch(attriRecs[i_].dataType){
		case INT:
			*(int *)attriDatas[i_] = atoi(str_.c_str());
			break;

		case LONG:
			*(long *)attriDatas[i_] = atol(str_.c_str());
			break;

		case FLOAT:
			*(float *)attriDatas[i_] = (float)atof(str_.c_str());
			break;

		case DOUBLE:	
			*(double *)attriDatas[i_] = (double)atof(str_.c_str());
			break;

		case FIXED_TEXT:
			if(str_.length() < 0 || str_.length() > attriRecs[i_].dataLength)
				return (EXIT_FAILURE);
			for(unsigned int j = 0; j < attriRecs[i_].dataLength; j++)
				memcpy((char *)attriDatas[i_] + j, "' ", 1);
			memcpy((char *)attriDatas[i_], str_.c_str(), str_.length());
			break;

		case VARIABLE_TEXT:
			if(str_.length() < 0 || str_.length() > attriRecs[i_].dataLength)
				return (EXIT_FAILURE);
			strcpy((char *)attriDatas[i_],str_.c_str());
			break;

		case DATE:
			*(unsigned int *)attriDatas[i_] = (unsigned int)atoi(str_.c_str());
			break;
			
		default:
			cout << "Error insertVoidData" << endl;
			exit (EXIT_FAILURE);
	}
	return(EXIT_SUCCESS);
}

unsigned int TableMaker::getKey(char *keyBuffer_, unsigned int keyBufSize_)
{
	unsigned int size = 0;

	for(int i = 0; i < numAttribute; i++){
		if(attriRecs[i].primary == true){
			switch(attriRecs[i].dataType){
				case INT:
					assert(size + sizeof(int) <= keyBufSize_);
					memcpy(keyBuffer_ + size, (int *)attriDatas[i], sizeof(int));
					size += sizeof(int);
					break;

				case LONG:
					assert(size + sizeof(long) <= keyBufSize_);
					memcpy(keyBuffer_ + size, (long *)attriDatas[i], sizeof(long));
					size += sizeof(long);
					break;

				case FLOAT:
					assert(size + sizeof(float) <= keyBufSize_);
					memcpy(keyBuffer_ + size, (float *)attriDatas[i], sizeof(float));
					size += sizeof(float);
					break;

				case DOUBLE:	
					assert(size + sizeof(double) <= keyBufSize_);
					memcpy(keyBuffer_ + size, (double *)attriDatas[i], sizeof(double));
					size += sizeof(double);
					break;
	
				case FIXED_TEXT:
					assert(size + attriRecs[i].dataLength <= keyBufSize_);
					memcpy(keyBuffer_ + size, (char *)attriDatas[i], attriRecs[i].dataLength);
					size += attriRecs[i].dataLength;
					break;

				case VARIABLE_TEXT:
					assert(size + strlen((char *)attriDatas[i]) <= keyBufSize_);
					strcpy(keyBuffer_ + size, (char *)attriDatas[i]);
					size += strlen((char *)attriDatas[i]) + 1;
					break;

				case DATE:
					assert(size + sizeof(unsigned int) <= keyBufSize_);
					memcpy(keyBuffer_ + size, (unsigned int *)attriDatas[i], sizeof(unsigned int));
					size += sizeof(unsigned int);
					break;
		
				default:
					cout << "Error insertVoidData" << endl;
					exit (EXIT_FAILURE);
			}
		}
	}
	return size;
}

unsigned int TableMaker::getData(char *dataBuffer_, unsigned int dataBufSize_)
{
	unsigned int size = 0;

	for(int i = 0; i < numAttribute; i++){
		switch(attriRecs[i].dataType){
			case INT:
				assert(size + sizeof(int) <= dataBufSize_);
				memcpy(dataBuffer_ + size, (int *)attriDatas[i], sizeof(int));
				size += sizeof(int);
				break;

			case LONG:
				assert(size + sizeof(long) <= dataBufSize_);
				memcpy(dataBuffer_ + size, (long *)attriDatas[i], sizeof(long));
				size += sizeof(long);
				break;

			case FLOAT:
				assert(size + sizeof(float) <= dataBufSize_);
				memcpy(dataBuffer_ + size, (float *)attriDatas[i], sizeof(float));
				size += sizeof(float);
				break;

			case DOUBLE:	
				assert(size + sizeof(double) <= dataBufSize_);
				memcpy(dataBuffer_ + size, (double *)attriDatas[i], sizeof(double));
				size += sizeof(double);
				break;

			case FIXED_TEXT:
				assert(size + attriRecs[i].dataLength <= dataBufSize_);
				memcpy(dataBuffer_ + size, (char *)attriDatas[i], attriRecs[i].dataLength);
				size += attriRecs[i].dataLength;
				break;

			case VARIABLE_TEXT:
				assert(size + strlen((char *)attriDatas[i]) <= dataBufSize_);
				strcpy(dataBuffer_ + size, (char *)attriDatas[i]);
				size += sizeof((char *)attriDatas[i]) + 1;
				break;

			case DATE:
				assert(size + sizeof(unsigned int) <= dataBufSize_);
				memcpy(dataBuffer_ + size, (unsigned int *)attriDatas[i], sizeof(unsigned int));
				size += sizeof(unsigned int);
				break;

			default:
				cout << "Error insertVoidData" << endl;
				exit (EXIT_FAILURE);
		}
	}
	return size;
}


