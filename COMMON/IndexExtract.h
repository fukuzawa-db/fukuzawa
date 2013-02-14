#ifndef __INDEXEXTRACT_H
#define __INDEXEXTRACT_H

#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>
#include<cassert>
#include<db_cxx.h>

#include"CommonDataDef.h"

#include"PosVal.h"
#include"IntPosVal.h"
#include"LongPosVal.h"
#include"FloatPosVal.h"
#include"DoublePosVal.h"
#include"FixStrPosVal.h"
#include"VarStrPosVal.h"
#include"DatePosVal.h"

int R_1_secondary(Db *sdbp, const Dbt*pkey, const Dbt *pdata, Dbt *skey);
int N_1_secondary(Db *sdbp, const Dbt*pkey, const Dbt *pdata, Dbt *skey);
int N_3_secondary(Db *sdbp, const Dbt*pkey, const Dbt *pdata, Dbt *skey);
int S_1_secondary(Db *sdbp, const Dbt*pkey, const Dbt *pdata, Dbt *skey);
int S_4_secondary(Db *sdbp, const Dbt*pkey, const Dbt *pdata, Dbt *skey);
int P_1_secondary(Db *sdbp, const Dbt*pkey, const Dbt *pdata, Dbt *skey);
int PS_1_secondary(Db *sdbp, const Dbt*pkey, const Dbt *pdata, Dbt *skey);
int PS_2_secondary(Db *sdbp, const Dbt*pkey, const Dbt *pdata, Dbt *skey);
int C_1_secondary(Db *sdbp, const Dbt*pkey, const Dbt *pdata, Dbt *skey);
int C_4_secondary(Db *sdbp, const Dbt*pkey, const Dbt *pdata, Dbt *skey);
int O_1_secondary(Db *sdbp, const Dbt*pkey, const Dbt *pdata, Dbt *skey);
int O_2_secondary(Db *sdbp, const Dbt*pkey, const Dbt *pdata, Dbt *skey);
int L_1_secondary(Db *sdbp, const Dbt*pkey, const Dbt *pdata, Dbt *skey);
int L_2_secondary(Db *sdbp, const Dbt*pkey, const Dbt *pdata, Dbt *skey);
int L_3_secondary(Db *sdbp, const Dbt*pkey, const Dbt *pdata, Dbt *skey);
int L_11_secondary(Db *sdbp, const Dbt*pkey, const Dbt *pdata, Dbt *skey);
int T_1_secondary(Db *sdbp, const Dbt*pkey, const Dbt *pdata, Dbt *skey);

#endif
