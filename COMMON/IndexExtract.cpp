#include"IndexExtract.h"

int R_1_secondary(Db *sdbp, const Dbt*pkey, const Dbt *pdata, Dbt *skey){
	skey->set_data((int *)pdata->get_data());
	skey->set_size(sizeof(int));
	return 0;
}

int N_1_secondary(Db *sdbp, const Dbt*pkey, const Dbt *pdata, Dbt *skey){
	skey->set_data((int *)pdata->get_data());
	skey->set_size(sizeof(int));
	return 0;
}

int N_3_secondary(Db *sdbp, const Dbt*pkey, const Dbt *pdata, Dbt *skey){
	int pos = sizeof(int) + 25;
	skey->set_data((int *)((char *)pdata->get_data() + pos));
	skey->set_size(sizeof(int));
	return 0;
}

int S_1_secondary(Db *sdbp, const Dbt*pkey, const Dbt *pdata, Dbt *skey){
	skey->set_data((int *)pdata->get_data());
	skey->set_size(sizeof(int));
	return 0;
}

int S_4_secondary(Db *sdbp, const Dbt*pkey, const Dbt *pdata, Dbt *skey){
	int pos = sizeof(int) + 25;
	while(1){
		if(*((char *)pdata->get_data() + pos) == '\0'){
			pos++;
			break;
		}
		pos++;
	}
	skey->set_data((int *)((char *)pdata->get_data() + pos));
	skey->set_size(sizeof(int));
	return 0;
}

int P_1_secondary(Db *sdbp, const Dbt*pkey, const Dbt *pdata, Dbt *skey){
	skey->set_data((int *)pdata->get_data());
	skey->set_size(sizeof(int));
	return 0;
}

int PS_1_secondary(Db *sdbp, const Dbt*pkey, const Dbt *pdata, Dbt *skey){
	skey->set_data((int *)((char *)pdata->get_data() + 0));
	skey->set_size(sizeof(int));
	return 0;
}

int PS_2_secondary(Db *sdbp, const Dbt*pkey, const Dbt *pdata, Dbt *skey){
	skey->set_data((int *)((char *)pdata->get_data() + sizeof(int)));
	skey->set_size(sizeof(int));
	return 0;
}

int C_1_secondary(Db *sdbp, const Dbt*pkey, const Dbt *pdata, Dbt *skey){
	skey->set_data((int *)pdata->get_data());
	skey->set_size(sizeof(int));
	return 0;
}

int C_4_secondary(Db *sdbp, const Dbt*pkey, const Dbt *pdata, Dbt *skey){
	int pos = sizeof(int);
	while(1){
		if(*((char *)pdata->get_data() + pos) == '\0'){
			pos++;
			break;
		}
		pos++;
	}
	while(1){
		if(*((char *)pdata->get_data() + pos) == '\0'){
			pos++;
			break;
		}
		pos++;
	}
	skey->set_data((int *)((char *)pdata->get_data() + pos));
	skey->set_size(sizeof(int));
	return 0;
}

int O_1_secondary(Db *sdbp, const Dbt*pkey, const Dbt *pdata, Dbt *skey){
	skey->set_data((int *)pdata->get_data());
	skey->set_size(sizeof(int));
	return 0;
}

int O_2_secondary(Db *sdbp, const Dbt*pkey, const Dbt *pdata, Dbt *skey){
	skey->set_data((int *)((char *)pdata->get_data() + sizeof(int)));
	skey->set_size(sizeof(int));
	return 0;
}

int L_1_secondary(Db *sdbp, const Dbt*pkey, const Dbt *pdata, Dbt *skey){
	skey->set_data((int *)pdata->get_data());
	skey->set_size(sizeof(int));
	return 0;
}

int L_2_secondary(Db *sdbp, const Dbt*pkey, const Dbt *pdata, Dbt *skey){
	skey->set_data((int *)((char *)pdata->get_data() + sizeof(int)));
	skey->set_size(sizeof(int));
	return 0;
}

int L_3_secondary(Db *sdbp, const Dbt*pkey, const Dbt *pdata, Dbt *skey){
	skey->set_data((int *)((char *)pdata->get_data() + sizeof(int)*2));
	skey->set_size(sizeof(int));
	return 0;
}

int L_11_secondary(Db *sdbp, const Dbt*pkey, const Dbt *pdata, Dbt *skey){
	skey->set_data((char *)((char *)pdata->get_data() + (sizeof(int)*4 + sizeof(float)*4 + sizeof(char)*2)));
	skey->set_size(10);
	return 0;
}

int T_1_secondary(Db *sdbp, const Dbt*pkey, const Dbt *pdata, Dbt *skey){
	skey->set_data((int *)pdata->get_data());
	skey->set_size(sizeof(int));
	return 0;
}
