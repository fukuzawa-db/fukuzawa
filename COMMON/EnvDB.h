#ifndef __ENVDB_H
#define __ENVDB_H

#include<iostream>
#include<db_cxx.h>
#include<cstdlib>
#include<cstring>
#include<cassert>
#include<fstream>

#include"CommonDataDef.h"

class EnvDB{
public:
	EnvDB();
	~EnvDB();
	
	void open(void);
	void close(void);
	DbEnv *getEnv(void);
	
private:
	DbEnv *env;
	u_int32_t env_flags;
};

#endif
