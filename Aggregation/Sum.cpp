#include"Sum.h"

using namespace std;

Sum::Sum(Node *root_, unsigned int refNum_){
	root = root_;
	refNum = refNum_;
	refNode = new ColumnRefNode*[refNum];
	index = 0;
	setRefNode(root);
	pv = NULL;
	attriRec.tableID = 0;
	attriRec.attributeID = 0;
	attriRec.dataType = DOUBLE;
	type = DOUBLE;
	strcpy(attriRec.attributeName, "Sum");
	longSum = 0;
	doubleSum = 0.0;
	flag = 0;
}

Sum::Sum(Node *root_, unsigned int refNum_, DataType type_){
	root = root_;
	refNum = refNum_;
	refNode = new ColumnRefNode*[refNum];
	index = 0;
	setRefNode(root);
	pv = NULL;
	attriRec.tableID = 0;
	attriRec.attributeID = 0;
	
	type = type_;
	switch(type){
		case(INT):
		case(LONG):
			attriRec.dataType = LONG;
			break;
		case(FLOAT):
		case(DOUBLE):
			attriRec.dataType = DOUBLE;
			break;
		default:
			cout << "Error can't defined datatype : Sum.class" << endl;
			exit (1);
	}
	
	strcpy(attriRec.attributeName, "Sum");
	longSum = 0;
	doubleSum = 0.0;
	flag = 0;
}

Sum::Sum(Node *root_, unsigned int refNum_, DataType type_, unsigned int *pos_, unsigned int index_){
	root = root_;
	refNum = refNum_;
	refNode = new ColumnRefNode*[refNum];
	index = 0;
	setRefNode(root);
	pv = NULL;
	attriRec.tableID = 0;
	attriRec.attributeID = 0;
	
	type = type_;
	switch(type){
		case(INT):
		case(LONG):
			attriRec.dataType = LONG;
			break;
		case(FLOAT):
		case(DOUBLE):
			attriRec.dataType = DOUBLE;
			break;
		default:
			cout << "Error can't defined datatype : Sum.class" << endl;
			exit (1);
	}
	
	strcpy(attriRec.attributeName, "Sum");
	longSum = 0;
	doubleSum = 0.0;
	flag = 0;
	
	copyPos(pos_, index_);
}


Sum::~Sum(){}

void Sum::init(ATTRIBUTE_REC **attriRec_, unsigned int attriNum_){
	pos = new unsigned int[index];
	for(unsigned int i = 0; i < index; i++){
		if(refNode[i]->attriID == 0 && refNode[i]->tableID == 0){
			pos[i] = refNode[i]->position;
		}else{
			unsigned int j;
			for(j = 0; j < attriNum_; j++){
				if((attriRec_[j]->attributeID == refNode[i]->attriID) && (attriRec_[j]->tableID == refNode[i]->tableID)){
					pos[i] = j;
					break;
				}
			}
			if(i == attriNum_){
				cout << "Error : Sum.class" << endl;
				exit(-1);
			}
		}
	}
}

Aggregation *Sum::clone(void){
	Aggregation *newAggreOpe = new Sum(root, refNum, attriRec.dataType, pos, index);
	return newAggreOpe;
}

void Sum::copyPos(unsigned int *pos_, unsigned int index_){
	pos = new unsigned int[index_];
	memcpy(pos, pos_, sizeof(unsigned int) * index_);
}


void Sum::setRefNode(Node *node){
	if(node->leftNode != NULL)setRefNode(node->leftNode);
	if(node->rightNode != NULL)setRefNode(node->rightNode);

	if(node->type == COLUMNREF_NODE){
		refNode[index] = (ColumnRefNode *)node;
		index++;
	}
}


void Sum::setAttriName(string attriName_){
	if(attriName_.length() > MAX_NAME_LENGTH - 1){
		cout << "Error too long AttriName : Sum.class" << endl;
		exit(-1);
	}
	strcpy(attriRec.attributeName, attriName_.c_str());
}

void Sum::inputData(PosVal **pv_, unsigned int pvNum_)
{
	for(unsigned int i = 0; i < index; i++){
		refNode[i]->setPosVal(pv_[pos[i]]);
	}
	tmpPV = (PosVal *)root->getValue();
	
	switch(flag){
		case(0):
			switch(tmpPV->type){
				case(INT):
					switch(type){
						case(INT):
						case(LONG):
							longSum += *(int *)tmpPV->value;
							break;
						case(FLOAT):
						case(DOUBLE):
							doubleSum += *(int *)tmpPV->value;
							break;
						default:
							cout << "Error can't defined datatype : Sum.class" << endl;
							exit (1);	
					}					
					flag = 1;
					break;
				case(LONG):
					switch(type){
						case(INT):
						case(LONG):
							longSum += *(long *)tmpPV->value;
							break;
						case(FLOAT):
						case(DOUBLE):
							doubleSum += *(long *)tmpPV->value;
							break;
						default:
							cout << "Error can't defined datatype : Sum.class" << endl;
							exit (1);	
					}
					flag = 2;
					break;
				case(FLOAT):
					assert(type == FLOAT || type == DOUBLE);
					doubleSum += *(float *)tmpPV->value;
					flag = 3;
					break;
				case(DOUBLE):
					assert(type == FLOAT || type == DOUBLE);
					doubleSum += *(double *)tmpPV->value;
					flag = 4;
					break;
				default:
					cout << "not define type : Sum.class" << endl;
					exit(-1);
					break;
			}
			break;
		case(1):
			longSum += *(int *)tmpPV->value;
			break;
		case(2):
			longSum += *(long *)tmpPV->value;
			break;
		case(3):
			doubleSum += *(float *)tmpPV->value;
			break;
		case(4):
			doubleSum += *(double *)tmpPV->value;
			break;
		default:
			cout << "Error : Sum.class" << endl;
			exit(-1);
	}

}

PosVal *Sum::getValue(void){
	if(type == INT || type == LONG)
		pv = new LongPosVal(0, longSum);
	else if(type == FLOAT || type == DOUBLE)
		pv = new DoublePosVal(0, doubleSum);
	else{
		cout << "Error : Sum.class" << endl;
		exit(-1);
	}			
	
	return pv;
}	
