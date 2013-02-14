#ifndef __JOININDEX_DEF_H
#define __JOININDEX_DEF_H

#include<iostream>
#include<string>
#include<cstdlib>
#include<cassert>
#include<db_cxx.h>

#include"CommonDataDef.h"
#include"BDBOpe.h"
#include"JoinIndexDef.h"
#include"Hash.h"
#include"Operator.h"
#include"PosVal.h"
#include"IntPosVal.h"
#include"LongPosVal.h"
#include"FloatPosVal.h"
#include"DoublePosVal.h"
#include"FixStrPosVal.h"
#include"VarStrPosVal.h"
#include"DatePosVal.h"
#include"ScanJoinIndex.h"

typedef struct JOIN_INDEX_STRUCT{
	string dbName;
	BDBOpe	*db;
	ScanJoinIndex *ScanNode;
}JOIN_INDEX;

#endif
