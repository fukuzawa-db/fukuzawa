#ifndef __COMMONDATADEF_H
#define __COMMONDATADEF_H

#include<unistd.h>
#include<string>
#include<string.h>
#include<db_cxx.h>

using namespace std;

/*
#include"PosVal.h"
#include"IntPosVal.h"
#include"LongPosVal.h"
#include"FloatPosVal.h"
#include"DoublePosVal.h"
#include"FixStrPosVal.h"
#include"VarStrPosVal.h"
#include"DatePosVal.h"

#include"BDBOpe.h"
*/

#define MAX_NAME_LENGTH (256)

typedef enum e_DATA_TYPE {INT = 1, LONG, FLOAT, DOUBLE, FIXED_TEXT, VARIABLE_TEXT, DATE} DataType;
typedef enum e_OUT_FLAF {STD_OUT, DB_OUT, TIME_OUT} OUT_FLAG;
typedef enum e_NODE_TYPE {ARITH_NODE, AXPR_NODE, COLUMNREF_NODE, VALUE_NODE} NODE_TYPE;
typedef enum e_AXPR_TYPE {EQ, NE, LT, GT, LE, GE, AND, OR} AXPR_TYPE;
typedef enum e_ARITH_TYPE {ADD, SUB, MUL, DIV} ARITH_TYPE;


typedef struct TABLE_REC_STRUCT{
	unsigned int tableID;
	unsigned int attriNum;
	char tableName[MAX_NAME_LENGTH];
} TABLE_REC;


typedef struct ATTRIBUTE_REC_STRUCT{
	char attributeName[MAX_NAME_LENGTH];
	unsigned int tableID;
	unsigned int attributeID;
	DataType dataType;
	unsigned short dataLength;
	bool primary;
	bool isCompress;
	bool isSort;
	bool isIndex;
} ATTRIBUTE_REC;


typedef struct OPERATION_NODE_STRUCT{
	unsigned int tableID;
	unsigned int attributeID;
	unsigned int position;
	unsigned int option;
} OPERATION_NODE;	


typedef struct JOIN_OPERATION_NODE_STRUCT{
	OPERATION_NODE rightNode, leftNode;
}JOIN_OPERATION_NODE;



typedef enum ACCESS_METHOD {BTREE, QUEUE} AccessMethod;

/** Insert Option **/

typedef enum INSERT_OPTION {NON, REGION, NATION, SUPPLIER, PART, PARTSUPP, CUSTOMER, ORDERS, LINEITEM, TEST} Insert_Option;

/** ================ **/



#define PAUSE ('|')

#define MAX_WORK_SPACE	(1024*1024*256)

#define DSM_PAGE_SIZE (4096 * 8) //(getpagesize() * 8)
#define DSM_BUFFER_SIZE (DSM_PAGE_SIZE - 256)


#define MAX_ATTRIBUTE_NUM	(256)

//#define RUN_PATH	("/raid2/singlemp/RunData")
//#define RUN_PATH	("/home/db/miyazaki/RunData")
#define RUN_PATH	("/home/singlemp/RunData")
//#define RUN_PATH	("/home/raidmp/RunData")
#define QUERY_DATA_PATH	RUN_PATH	
//#define QUERY_DATA_PATH		("/home/singlemp/RunData")
//#define QUERY_DATA_PATH		("/home/raidmp/RunData")
//("/home/fuku/DataSet/RunData")

/** BDB Parameter **/

#define ENV_HOME	(RUN_PATH)

#define ENV_CACHE_SIZE_BYTE		(0)
#define ENV_CACHE_SIZE_GBYTE	(16)

#define BDB_PAGE_SIZE			(1024 * 4)

#define BDB_CACHE_SIZE_BYTE		(0)
#define BDB_CACHE_SIZE_GBYTE	(16)


/**  HASH Parameter **/

#define HASH_SIZE	(40277)
#define MUL_NUM		(797)

#endif
