#include<iostream>
#include<string>
#include"CommonDataDef.h"
#include"TableManager.h"
#include"AttributeManager.h"
#include"EnvDB.h"

int main(){
	chdir(QUERY_DATA_PATH);

	std::cout << "======= DBs info =========" << std::endl;
	TableManager *tm = new TableManager();
	tm->showAllRecord();

	std::cout << "======= Tables info =========" << std::endl;
	AttributeManager *am = new AttributeManager();
	am->showAllRecord();
}
