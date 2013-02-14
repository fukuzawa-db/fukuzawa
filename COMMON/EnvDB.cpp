#include"EnvDB.h"

EnvDB::EnvDB(){
	env = new DbEnv(0);
	env_flags = DB_CREATE | DB_INIT_MPOOL | DB_PRIVATE;
	env->set_cachesize(ENV_CACHE_SIZE_GBYTE, ENV_CACHE_SIZE_BYTE, 1);
}

EnvDB::~EnvDB(){}

void EnvDB::open(){
	try{
		env->open(ENV_HOME, env_flags, 0);
	}catch(DbException &e){
		std::cerr 	<< "Error opening database environment: " << ENV_HOME;
		std::cerr << e.what() <<endl;
		exit(1);
	}catch(std::exception &e){
		std::cerr 	<< "Error opening database environment: " << ENV_HOME;
		std::cerr << e.what() <<endl;
		exit(1);
	}
}
		
void EnvDB::close(){
	try{
		if(env != NULL){
			env->close(0);
		}
	}catch(DbException &e){
		std::cerr 	<< "Error opening database environment: " << ENV_HOME;
		std::cerr << e.what() <<endl;
		exit(1);
	}catch(std::exception &e){
		std::cerr 	<< "Error opening database environment: " << ENV_HOME;
		std::cerr << e.what() <<endl;
		exit(1);
	}
}

DbEnv *EnvDB::getEnv(){
	return env;
}
