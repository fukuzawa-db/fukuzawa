#ifndef __HASH_H
#define __HASH_H

#include<iostream>
#include<cstdlib>
#include<string>
#include<math.h>

#include"CommonDataDef.h"
#include"Hash.h"
#include"BDBOpe.h"
#include"InMemDB.h"
#include"Operator.h"
#include"PosVal.h"
#include"IntPosVal.h"
#include"LongPosVal.h"
#include"FloatPosVal.h"
#include"DoublePosVal.h"
#include"FixStrPosVal.h"
#include"VarStrPosVal.h"
#include"DatePosVal.h"
#include"ScanHash.h"
#include"ScanInMemHash.h"

typedef struct ONESIDE_HASH_NODE_STRUCT{
	string dbName;
	BDBOpe	*db;
	ScanHash	*ScanNode;
} ONESIDE_HASH_NODE;

typedef struct ONESIDE_INMEM_HASH_NODE_STRUCT{
	string dbName;
	InMemDB *db;
	ScanInMemHash	*ScanNode;
} ONESIDE_INMEM_HASH_NODE;


unsigned int hashFunc(PosVal *pv);
unsigned int hashFunc(unsigned int pos);

#endif

