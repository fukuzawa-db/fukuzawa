#include"MakeNSM.h"

using namespace std;

MakeNSM::MakeNSM(string fileName_, TABLE_REC *tableRec_, ATTRIBUTE_REC *attriRec_, unsigned int attriNum_, Insert_Option option_){
	fileName = fileName_;
	tableRec = tableRec_;
	attriRec = attriRec_;
	attriNum = attriNum_;
	option = option_;

	attriDatas = new void*[attriNum];
/*
	cout << "\n================================================" << endl;
	cout << "filename = " << fileName << endl;
	cout << "table ID = " << tableRec->tableID << endl;
	cout << "table Name = " << tableRec->tableName << endl;
	cout << endl;
	
	for(int i = 0 ; i < (int)attriNum; i++){
		cout << "\n" ;
		cout << "tableID = " << attriRec[i].tableID << endl;
		cout << "attributeID = " << attriRec[i].attributeID << endl;
		cout << "dataType = " << attriRec[i].dataType << endl;
		cout << "datLength = " << attriRec[i].dataLength << endl;
		cout << "primary = " << attriRec[i].primary << endl;
	}
	cout << "================================================\n\n" ;
*/	
	initAttriDatas();
}

MakeNSM::~MakeNSM()
{
	for(int i=0; i < (int )attriNum; i++){
		switch(attriRec[i].dataType){
			case INT:
				delete (int *)attriDatas[i];
				break;

			case LONG:
				delete (long *)attriDatas[i];
				break;

			case FLOAT:
				delete (float *)attriDatas[i];
				break;

			case DOUBLE:
				delete (double *)attriDatas[i];
				break;

			case FIXED_TEXT:
				delete (char *)attriDatas[i];
				break;

			case VARIABLE_TEXT:
				delete (char *)attriDatas[i];
				break;

			case DATE:
				delete (unsigned int *)attriDatas[i];
				break;
		}
	}
	delete [] attriDatas;
}

void MakeNSM::run(){
	std::ifstream inFile(fileName.c_str());
	if(inFile.fail()){
		cerr << "Error: Could not open  " << fileName << endl;
		exit(EXIT_FAILURE);
	}
	string BDBName = tableRec->tableName;
	BDBName += ".row";
	BDBOpe BDBFile(BDBName);
	
	secondNum = 0;
	stringstream fs;
	switch(option){
		case NON:
			secondNum = 0;
			break;
		
		case REGION:
			secondNum = 1;
			sDB = new SecondDB*[secondNum];
			pf = new (int (*[secondNum])(Db *, const Dbt*, const Dbt *, Dbt *));
			
			
			fs << attriRec[0].tableID << "." << attriRec[0].attributeID << ".secondary";
			sDB[0] = new SecondDB(fs.str());
			sDB[0]->setNumCmp();
			pf[0] = R_1_secondary;
			break;
		
		case NATION: {
			secondNum = 2;
			sDB = new SecondDB*[secondNum];
			pf = new (int (*[secondNum])(Db *, const Dbt*, const Dbt *, Dbt *));
			
			fs << attriRec[0].tableID << "." << attriRec[0].attributeID << ".secondary";
			sDB[0] = new SecondDB(fs.str());
			sDB[0]->setNumCmp();
			pf[0] = N_1_secondary;
			
			fs.str("");
			fs << attriRec[2].tableID << "." << attriRec[2].attributeID << ".secondary";
			sDB[1] = new SecondDB(fs.str());
			sDB[1]->setNumCmp();
			pf[1] = N_3_secondary;

			break;
		}
		
		case SUPPLIER: {
			secondNum = 2;
			sDB = new SecondDB*[secondNum];
			pf = new (int (*[secondNum])(Db *, const Dbt*, const Dbt *, Dbt *));
			
			fs << attriRec[0].tableID << "." << attriRec[0].attributeID << ".secondary";
			sDB[0] = new SecondDB(fs.str());
			sDB[0]->setNumCmp();
			pf[0] = S_1_secondary;
			
			fs.str("");
			fs << attriRec[3].tableID << "." << attriRec[3].attributeID << ".secondary";
			sDB[1] = new SecondDB(fs.str());
			sDB[1]->setNumCmp();
			pf[1] = S_4_secondary;
			
			break;
		}
			
		case PART:
			secondNum = 1;
			sDB = new SecondDB*[secondNum];
			pf = new (int (*[secondNum])(Db *, const Dbt*, const Dbt *, Dbt *));
			
			fs << attriRec[0].tableID << "." << attriRec[0].attributeID << ".secondary";
			sDB[0] = new SecondDB(fs.str());
			sDB[0]->setNumCmp();
			pf[0] = P_1_secondary;
			break;
		
		case PARTSUPP: {
			secondNum = 2;
			sDB = new SecondDB*[secondNum];
			pf = new (int (*[secondNum])(Db *, const Dbt*, const Dbt *, Dbt *));
			
			fs << attriRec[0].tableID << "." << attriRec[0].attributeID << ".secondary";
			sDB[0] = new SecondDB(fs.str());
			sDB[0]->setNumCmp();
			pf[0] = PS_1_secondary;
			
			fs.str("");
			fs << attriRec[1].tableID << "." << attriRec[1].attributeID << ".secondary";
			sDB[1] = new SecondDB(fs.str());
			sDB[1]->setNumCmp();
			pf[1] = PS_2_secondary;
			
			break;
		}
		
		case CUSTOMER: {
			secondNum = 2;
			sDB = new SecondDB*[secondNum];
			pf = new (int (*[secondNum])(Db *, const Dbt*, const Dbt *, Dbt *));
			
			fs << attriRec[0].tableID << "." << attriRec[0].attributeID << ".secondary";
			sDB[0] = new SecondDB(fs.str());
			sDB[0]->setNumCmp();
			pf[0] = C_1_secondary;
			
			fs.str("");
			fs << attriRec[3].tableID << "." << attriRec[3].attributeID << ".secondary";
			sDB[1] = new SecondDB(fs.str());
			sDB[1]->setNumCmp();
			pf[1] = C_4_secondary;
			
			break;
		}
		
		case ORDERS: {
			secondNum = 2;
			sDB = new SecondDB*[secondNum];
			pf = new (int (*[secondNum])(Db *, const Dbt*, const Dbt *, Dbt *));
			
			fs << attriRec[0].tableID << "." << attriRec[0].attributeID << ".secondary";
			sDB[0] = new SecondDB(fs.str());
			sDB[0]->setNumCmp();
			pf[0] = O_1_secondary;
			
			fs.str("");
			fs << attriRec[1].tableID << "." << attriRec[1].attributeID << ".secondary";
			sDB[1] = new SecondDB(fs.str());
			sDB[1]->setNumCmp();
			pf[1] = O_2_secondary;
			
			break;
		}
		
		case LINEITEM: {
			secondNum = 4;
			sDB = new SecondDB*[secondNum];
			pf = new (int (*[secondNum])(Db *, const Dbt*, const Dbt *, Dbt *));
			
			fs << attriRec[0].tableID << "." << attriRec[0].attributeID << ".secondary";
			sDB[0] = new SecondDB(fs.str());
			sDB[0]->setNumCmp();
			pf[0] = L_1_secondary;
			
			fs.str("");
			fs << attriRec[1].tableID << "." << attriRec[1].attributeID << ".secondary";
			sDB[1] = new SecondDB(fs.str());
			sDB[1]->setNumCmp();
			pf[1] = L_2_secondary;
			
			fs.str("");
			fs << attriRec[2].tableID << "." << attriRec[2].attributeID << ".secondary";
			sDB[2] = new SecondDB(fs.str());
			sDB[2]->setNumCmp();
			pf[2] = L_3_secondary;
			
			fs.str("");
			fs << attriRec[10].tableID << "." << attriRec[10].attributeID << ".secondary";
			sDB[3] = new SecondDB(fs.str());
			sDB[3]->setfStrCmp();
			pf[3] = L_11_secondary;
			break;
		}
		
		case TEST: {
			secondNum = 1;
			sDB = new SecondDB*[secondNum];
			pf = new (int (*[secondNum])(Db *, const Dbt*, const Dbt *, Dbt *));
			
			fs << attriRec[0].tableID << "." << attriRec[0].attributeID << ".secondary";
			sDB[0] = new SecondDB(fs.str());
			sDB[0]->setNumCmp();
			pf[0] = T_1_secondary;
			
			break;
		}
		
		default:{
			cerr << "illegal option";
			exit(-1);
			break;
		}
	}

	BDBFile.open();
	
	for(int i=0; i<secondNum; i++){
		sDB[i]->open(0);
		BDBFile.associate(sDB[i]->getDb(), pf[i]);
		sDB[i]->openCursor();
	}
	
	
	unsigned int dataSize;
	unsigned int dataBufSize = getDataBufSize();
	char dataBuffer[dataBufSize];
	unsigned int keyIdentify = 1;
	
#ifdef DEBUG
	ofstream debug_ofs("NSM_DEBUG");
#endif

	while(getline(inFile, buffer)){
		returnCode = 0;
		for(int i= 0; i < (int)attriNum; i++){
			end_pos = buffer.find(PAUSE);
			returnCode = insertVoidData(i, buffer.substr(0, end_pos));
			if(returnCode != 0)break;
			buffer = buffer.substr(end_pos+1);
		}
		if(returnCode != 0){
			cout << "Wrong Data type : " << buffer << endl;
			continue;
		}
		dataSize = getData(dataBuffer, dataBufSize);

#ifdef DEBUG
		debug_ofs.write((char *)dataBuffer, dataSize);
#endif

		BDBFile.writeRecord(&keyIdentify, sizeof(keyIdentify), dataBuffer, dataSize, false);
		keyIdentify += 1;
	}

	for(int i=0; i<secondNum; i++){
		sDB[i]->close();
	}
	BDBFile.close();
	inFile.close();
}



void MakeNSM::initAttriDatas(){
	for(int i=0; i < (int)attriNum; i++){
		switch(attriRec[i].dataType){
			case INT:
				attriDatas[i] = new int;	
				break;

			case LONG:
				attriDatas[i] = new long;
				break;

			case FLOAT:
				attriDatas[i] = new float;
				break;

			case DOUBLE:
				attriDatas[i] = new double;
				break;

			case FIXED_TEXT:
				attriDatas[i] = new char[attriRec[i].dataLength];
				break;

			case VARIABLE_TEXT:
				attriDatas[i] = new char[attriRec[i].dataLength + 1];
				break;

			case DATE:
				attriDatas[i] = new char[attriRec[i].dataLength];
				break;

			default:
				cout << "Error setAttribute! in MakeNSM" << endl;
				exit (1);
		}
	}
}


unsigned int MakeNSM::getDataBufSize()
{
	int size = 0;
	for(int i = 0; i < (int)attriNum; i++){
		size += attriRec[i].dataLength;
		if(attriRec[i].dataType == VARIABLE_TEXT)size++;
	}
	return size;
}


int MakeNSM::insertVoidData(int i_, string str_)
{
	
	switch(attriRec[i_].dataType){
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
			if(str_.length() < 0 || str_.length() > attriRec[i_].dataLength)
				return (EXIT_FAILURE);
			for(unsigned int j = 0; j < attriRec[i_].dataLength; j++)
				memcpy((char *)attriDatas[i_] + j, " ", 1);
			memcpy((char *)attriDatas[i_], str_.c_str(), str_.length());
			break;

		case VARIABLE_TEXT:
			if(str_.length() < 0 || str_.length() > attriRec[i_].dataLength)
				return (EXIT_FAILURE);
			strcpy((char *)attriDatas[i_],str_.c_str());
			break;

		case DATE:
			if(str_.length() < 0 || str_.length() > attriRec[i_].dataLength)
				return (EXIT_FAILURE);
			for(unsigned int j = 0; j < attriRec[i_].dataLength; j++)
				memcpy((char *)attriDatas[i_] + j, " ", 1);
			memcpy((char *)attriDatas[i_], str_.c_str(), str_.length());
			break;
			
		default:
			cout << "Error insertVoidData" << endl;
			exit (EXIT_FAILURE);
	}
	return(EXIT_SUCCESS);
}


unsigned int MakeNSM::getData(char *dataBuffer_, unsigned int dataBufSize_)
{
	unsigned int size = 0;

	for(int i = 0; i < (int)attriNum; i++){
		switch(attriRec[i].dataType){
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
				assert(size + attriRec[i].dataLength <= dataBufSize_);
				memcpy(dataBuffer_ + size, (char *)attriDatas[i], attriRec[i].dataLength);
				size += attriRec[i].dataLength;
				break;

			case VARIABLE_TEXT:
				assert(size + strlen((char *)attriDatas[i]) <= dataBufSize_);
				strcpy(dataBuffer_ + size, (char *)attriDatas[i]);
				size += strlen((char *)attriDatas[i]) + 1;
				break;

			case DATE:
				assert(size + attriRec[i].dataLength <= dataBufSize_);
				memcpy(dataBuffer_ + size, (char *)attriDatas[i], attriRec[i].dataLength);
				size += attriRec[i].dataLength;
				break;

			default:
				cout << "Error insertVoidData" << endl;
				exit (EXIT_FAILURE);
		}
	}
	return size;
}

