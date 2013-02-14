#include"Encode.h" 

void Encode::initVal(void)
{
	switch(dataType){
		case INT:
			val = new int;
			break;

		case LONG:
			val = new long;
			break;

		case FLOAT:
			val = new float;
			break;

		case DOUBLE:
			val = new double;
			break;

		case FIXED_TEXT:
			val = new char[dataLength];
			break;

		case VARIABLE_TEXT:
			val = new char[dataLength+10];
			break;

		case DATE:
			val = new char[dataLength];
			break;

		default:
			cout << "ERROR : illegal DataType ; BareEncode" << endl;
			exit(EXIT_FAILURE);
			break;
	}
}

void Encode::getVal(void)
{

	switch(dataType){
		case INT:
			ifs >> *(int *)val;
			break;

		case LONG:
			ifs >> *(long *)val;
			break;

		case FLOAT:
			ifs >> *(float *)val;
			break;

		case DOUBLE:
			ifs >> *(double *)val;
			break;

		case FIXED_TEXT:
			{
			char buf[dataLength + 10];
			ifs.getline(buf, dataLength + 10);
			memset((char *)val, ' ', dataLength);
			assert(strlen(buf) <= dataLength);
			memcpy((char *)val, buf, strlen(buf));
			break;
			}

		case VARIABLE_TEXT:
			memset((char *)val, 0, dataLength);
			ifs.getline((char *)val, dataLength + 10);
///*debug*/	cout << "size = " << strlen((char *)val) << endl; 		
			break;

		case DATE:
			{char buf[dataLength + 10];
			ifs.getline(buf, dataLength + 10);
			memset((char *)val, 0, dataLength);
			assert(strlen(buf) <= dataLength);
			memcpy((char *)val, buf, strlen(buf));
			break;}

		default:
			cout << "ERROR : illegal DataType ; BareEncode" << endl;
			exit(EXIT_FAILURE);
			break;
	}
}


void Encode::freeVal(void)
{

	switch(dataType){
		case INT:
			if((int *)val != NULL)delete (int *)val;
			break;

		case LONG:
			if((long *)val != NULL)delete (long *)val;
			break;

		case FLOAT:
			if((float *)val != NULL)delete (float *)val;
			break;

		case DOUBLE:
			if((double *)val != NULL)delete (double *)val;
			break;

		case FIXED_TEXT:
			if((char *)val != NULL)delete (char *)val;
			break;

		case VARIABLE_TEXT:
			if((char *)val != NULL)delete (char *)val;
			break;

		case DATE:
			if((char *)val != NULL)delete (char *)val;
			break;

		default:
			cout << "ERROR : illegal DataType ; BareEncode" << endl;
			exit(EXIT_FAILURE);
			break;
	}
}
