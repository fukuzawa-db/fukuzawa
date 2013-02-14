#include"TableMaker.h"

using namespace std;


TableMaker::TableMaker(string fileName_){
	fileName = fileName_;			//格納するデータファイル
	chdir(RUN_PATH);
	TableFile = new TableManager();
	AttriFile = new AttributeManager();
	option = NON;
}

TableMaker::TableMaker(string fileName_, Insert_Option option_){
	fileName = fileName_;			//格納するデータファイル
	chdir(RUN_PATH);
	TableFile = new TableManager();
	AttriFile = new AttributeManager();
	option = option_;
}

TableMaker::~TableMaker(){
	//if(TableFile != NULL)delete TableFile;
	//if(AttriFile != NULL)delete AttriFile;
}

int TableMaker::run(){

	cout << "Please enter the table name" << endl;
	cin >> tableName;			//テーブル名の入力
	while(tableName.length() >= MAX_NAME_LENGTH){
		cout << "Too long length!" << endl;
		cout << "Please enter the table name again" << endl;
		cin >> tableName;
	}
	cout << "Table name is " << tableName << endl;

	cout << "How many attributes are in this table?" << endl;
	cin >> numAttribute;		//作成するテーブルの属性の数
	if(numAttribute < 1 || numAttribute > MAX_ATTRIBUTE_NUM){
		cout << "Num Attributes must be between 1 and " << MAX_ATTRIBUTE_NUM << "." << endl;
		return EXIT_FAILURE;
	}	
	attriRecs = new ATTRIBUTE_REC[numAttribute];

	TableFile->showRecordCount();
	tableID = TableFile->getNextID();	//新規テーブルIDの取得

	int typeNum;	
	for(int i = 0; i < (int )numAttribute; i++){
		cout << "Please enter the name of Attribute: " << (i+1) << endl;	//属性名の取得
		cin >> attriRecs[i].attributeName;
/*		while(tableName.length() >= MAX_NAME_LENGTH){
			cout << "Too long length!" << endl;
			cout << "Please enter the attribute name again" << endl;
			cin >> tableName;
		}
*/
		attriRecs[i].tableID = tableID;
		attriRecs[i].attributeID = i + 1;		//属性IDの設定
		while(1){
			cout << "Which is data type of " << attriRecs[i].attributeName << " ?" << endl;	//属性のデータ型の入力
			cout << "1 : Integer" << endl;
			cout << "2 : Long Integer" << endl;
			cout << "3 : Decimal" << endl;
			cout << "4 : Big Decimal" << endl;
			cout << "5 : Fixed Text" << endl;
			cout << "6 : Variable Text" << endl;
			cout << "7 : Date" << endl;
			cout << "Please enter number : ";
			cin >> typeNum;
			if(0 < typeNum  && 	typeNum < 8) break;
			cout << "Error number! Please again." << endl;
		}

		while(1){
			cout << attriRecs[i].attributeName << " is primary key?" << endl;	//主キーかどうか
			cout << "(y,n):";
			cin >> isPrimary;
			if(isPrimary == 'y' || isPrimary == 'Y' || isPrimary == 'n' || isPrimary == 'N')
				break;
			cout << "Error input! Please again." << endl;
		}

		while(1){
			cout << attriRecs[i].attributeName << " is Compress?" << endl;		//列指向の作成時に圧縮するカラムかどうか
			cout << "(y,n):";
			cin >> isCompress;
			if(isCompress == 'y' || isCompress == 'Y' || isCompress == 'n' || isCompress == 'N')
				break;
			cout << "Error input! Please again." << endl;
		}

		while(1){
			cout << attriRecs[i].attributeName << " is Sorted?" << endl;		//既に整列されている状態かどうか
			cout << "(y,n):";
			cin >> isSort;
			if(isSort == 'y' || isSort == 'Y' || isSort == 'n' || isSort == 'N')
				break;
			cout << "Error input! Please again." << endl;
		}
		while(1){
			cout << attriRecs[i].attributeName << " is Index?" << endl;		//indexを作成するか
			cout << "(y,n):";
			cin >> isIndex;
			if(isIndex == 'y' || isIndex == 'Y' || isIndex == 'n' || isIndex == 'N')
				break;
			cout << "Error input! Please again." << endl;
		}

		setAttriInf(i, typeNum, isPrimary, isCompress, isSort, isIndex);
	}

	cout << endl << endl;
	cout << "Making  Table Record" << endl;

	strcpy(tableRec.tableName, tableName.c_str());
	tableRec.tableID = tableID;
	tableRec.attriNum = numAttribute;
	TableFile->writeRecord(&tableRec);	//新規テーブル情報の書き込み

#ifdef DEBUG
	cout << "========= DEBUG MODE =============" << endl;
	TableFile->showAllRecord();
	cout << "==================================" << endl;
#endif

	delete TableFile;
	
	for(int i=0; i < (int)numAttribute; i++)
		AttriFile->writeRecord(&attriRecs[i]); //新規属性情報の書き込み
	delete AttriFile;

	cout << endl << endl;
	//行指向データの作成
	cout << "Making NSM" << endl;
	MakeNSM nsm = MakeNSM(fileName, &tableRec, attriRecs, numAttribute, option);
	nsm.run();

	//列指向データの作成
	cout << "\nMaking DSM" << endl;
	for(int i = 0; i < (int)numAttribute ; i++){
		//列指向のための一時データファイルの作成
		char tmpColumn[512];
		sprintf(tmpColumn, "%s.%s", tableName.c_str(), attriRecs[i].attributeName);
		string s = tmpColumn;
		char exec[1024];
		//列データの抽出
		sprintf(exec, "cut -d\"|\" -f%d %s > %s", (i+1), fileName.c_str(), tmpColumn);
		system(exec);

		cout << "Making " << attriRecs[i].attributeName << " DSM" << endl;
		MakeDSM dsm = MakeDSM(s, &attriRecs[i]);
		dsm.run();

		sprintf(exec, "rm %s", tmpColumn);
		system(exec);
	}
	return EXIT_SUCCESS;
}


/*属性データの設定*/
void TableMaker::setAttriInf(int i_, int typeNum_, char isPrimary_, char isCompress_, char isSort_, char isIndex_){
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

	switch(isCompress_){
		case 'y':
		case 'Y':
			attriRecs[i_].isCompress = true;
			break;

		case 'n':
		case 'N':
			attriRecs[i_].isCompress = false;
			break;

		default:
			cout << "Error setAttribute!" << endl;
			exit (1);
	}

	switch(isSort_){
		case 'y':
		case 'Y':
			attriRecs[i_].isSort = true;
			break;

		case 'n':
		case 'N':
			attriRecs[i_].isSort = false;
			break;

		default:
			cout << "Error setAttribute!" << endl;
			exit (1);
	}
	
	switch(isIndex_){
		case 'y':
		case 'Y':
			attriRecs[i_].isIndex = true;
			break;

		case 'n':
		case 'N':
			attriRecs[i_].isIndex = false;
			break;

		default:
			cout << "Error setAttribute!" << endl;
			exit (1);
	}

	switch(typeNum_){
		case 1:
			attriRecs[i_].dataType = INT;
			attriRecs[i_].dataLength = sizeof(int);
			break;

		case 2:
			attriRecs[i_].dataType = LONG;
			attriRecs[i_].dataLength = sizeof(long);
			break;

		case 3:
			attriRecs[i_].dataType = FLOAT;
			attriRecs[i_].dataLength = sizeof(float);
			break;

		case 4:
			attriRecs[i_].dataType = DOUBLE;
			attriRecs[i_].dataLength = sizeof(double);
			break;

		case 5:
			{
				attriRecs[i_].dataType = FIXED_TEXT;
				unsigned int textSize = 0;
				while(1){
					cout << "Please enter fixed text size of " << attriRecs[i_].attributeName << ":";
					cin >> textSize;
					if(0 < textSize && textSize < UINT_MAX)break;
					cout << "Error number! Please enter again.";
				}
				assert(0 < textSize && textSize < UINT_MAX);
				attriRecs[i_].dataLength = textSize;
				break;
			}
		case 6:
			{
				attriRecs[i_].dataType = VARIABLE_TEXT;
				unsigned int textSize = 0;
				while(1){
					cout << "Please enter variable text size of " << attriRecs[i_].attributeName << ":";
					cin >> textSize;
					if(0 < textSize && textSize < UINT_MAX)break;
					cout << "Error number! Please enter again.";
				}
				assert(0 < textSize && textSize < UINT_MAX);
				attriRecs[i_].dataLength = textSize;
				break;
			}
		case 7:
			attriRecs[i_].dataType = DATE;
			attriRecs[i_].dataLength = 10;
			break;

		default:
			cout << "Error setAttribute! setAttriInf" << endl;
			exit (1);
	}
}
