#include"Hash.h"

using namespace std;

unsigned int hashFunc(PosVal *pv){
	unsigned int hashVal;
	unsigned int intVal;
	switch(pv->type){
		case INT:
			intVal = *(int *)(pv->value);
			hashVal = (intVal * MUL_NUM) % HASH_SIZE;
			break;

		case LONG:
			hashVal = (unsigned long)(*(long *)pv->value * MUL_NUM) % HASH_SIZE;
			break;

		case FLOAT:
			cout << "Not Define HashFunction for FLOAR type" << endl;
			hashVal = 0;
			break;

		case DOUBLE:
			cout << "Not Define HashFunction for DOUBLE type" << endl;
			hashVal = 0;
			break;

		case FIXED_TEXT:
		case VARIABLE_TEXT:
		case DATE:
			for(int i = 0; i < pv->getSize(); i++)
				hashVal += (unsigned int)*(pv->value) * (unsigned int)pow((double)MUL_NUM, (double)(i+1));
			hashVal %= HASH_SIZE;
			break;

		default:
			cout << "ERROR NOT DEFINE TYPE" << endl;
			exit(EXIT_FAILURE);
	}
	
	return hashVal;
}

unsigned int hashFunc(unsigned int pos){
	unsigned int hashVal;

	hashVal = (pos * MUL_NUM) % HASH_SIZE;
	return hashVal;
}

