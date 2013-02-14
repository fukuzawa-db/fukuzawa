#include<iostream>
#include<string>
#include<fstream>
#include<cstdlib>
#include<ctype.h>
#include<unistd.h>
#include<getopt.h>

#include"CommonDataDef.h"
#include"TableMaker.h"
#include"IndexExtract.h"

#define DEBUG	1

int main(int argc, char *argv[]){
	int option_index;
	int result;
	Insert_Option option = NON;
	
	struct option long_options[] = {
		{"region", no_argument, NULL, 'r'},
		{"nation", no_argument, NULL, 'n'},
		{"supplier", no_argument, NULL, 's'},
		{"part", no_argument, NULL, 'p'},
		{"partsupp", no_argument, NULL, 'P'},
		{"customer", no_argument, NULL, 'c'},
		{"orders", no_argument, NULL, 'o'},
		{"lineitem", no_argument, NULL, 'l'},
		{"test", no_argument, NULL, 't'},
        {0, 0, 0, 0}
    };
    
    while((result=getopt_long(argc, argv, "rnspPcolt", long_options, &option_index))!=-1){
		switch(result){
			case 'r':
				{
					option = REGION;
					break;
				}
			case 'n':
				{
					option = NATION;
					break;
				}
			case 's':
				{
					option = SUPPLIER;
					break;
				}
			case 'p':
				{
					option = PART;
					break;
				}
			case 'P':
				{
					option = PARTSUPP;
					break;
				}
			case 'c':
				{
					option = CUSTOMER;
					break;
				}
			case 'o':
				{
					option = ORDERS;
					break;
				}
			case 'l':
				{
					option = LINEITEM;
					break;
				}
			case 't':
				{
					option = TEST;
					break;
				}
			case ':':
				{
					fprintf(stderr, "%c option need value\n" , result);
					exit(EXIT_FAILURE);

       			}
			case '?':
				{
					fprintf(stderr, "please check usage\n");
					exit(EXIT_FAILURE);
				}
		}
	}
	
	if(argc - optind != 1){
		cout << "err main" << endl;
		cout << "Usage " << argv[0] << " insertFile" << endl;
		return (EXIT_FAILURE);
	}

	string fileName = argv[optind];
	cout << fileName << endl;
	TableMaker tm = TableMaker(fileName, option);
	tm.run();
	return (EXIT_SUCCESS);
}
