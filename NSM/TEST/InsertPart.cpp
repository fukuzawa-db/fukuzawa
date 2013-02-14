#include <iostream>
#include <fstream>
#include <assert.h>
#include <string>

typedef struct PART_STRUCT{
	int P_PARTKEY;
	string P_NAME;
	char P_MFGR[25];
	char P_BRAND[10];
	string P_TYPE;
	int P_SIZE;
	char P_CONTAINER[10];
	float P_RETAILPRICE;
	string P_COMMENT;
} PART;

char Pause = '|';

#define PART_BUFFER_SIZE (sizeof(PART))
int main()
{
	string buffer;
	string file_name = "part.tbl";
	int start_pos,end_pos;

	std::ifstream part_tbl(file_name.c_str());
	if(part_tbl.fail()){
		std::cerr << "Error: Could not open " << file_name << endl;
		exit(1);
	}

	//std::cout << "sizeof BUFFER " << PART_BUFFER_SIZE << endl;
	//std::cout << sizeof(string) << endl;

	while(getline(part_tbl, buffer)){
		start_pos = 0;
		while(buffer.length() !=  0){
			end_pos = buffer.find(Pause);
			std::cout << buffer.substr(0, end_pos) << Pause;
			buffer = buffer.substr(end_pos+1);
		}
		std::cout << endl;
	}
	void* a;
	a = new int;
	*(int *)a = 1;
	part_tbl.close();
	return 0;
}
	
