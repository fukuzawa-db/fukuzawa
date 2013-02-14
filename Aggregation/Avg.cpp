#include"Avg.h"

using namespace std;

Avg::Avg(Node *root_, unsigned int refNum_){
	root = root_;
	refNum = refNum_;
	refNode = new ColumnRefNode*[refNum];
	index = 0;
	setRefNode(root);
	pv = NULL;
	attriRec.tableID = 0;
	attriRec.attributeID = 0;
	attriRec.dataType = DOUBLE;
	strcpy(attriRec.attributeName, "Avg");
	avg = 0.0;
	count = 0;
	flag = 0;
}

Avg::Avg(Node *root_, unsigned int refNum_, unsigned int *pos_, unsigned int index_){
	root = root_;
	refNum = refNum_;
	refNode = new ColumnRefNode*[refNum];
	index = 0;
	setRefNode(root);
	pv = NULL;
	attriRec.tableID = 0;
	attriRec.attributeID = 0;
	attriRec.dataType = DOUBLE;
	strcpy(attriRec.attributeName, "Avg");
	avg = 0.0;
	count = 0;
	flag = 0;
	copyPos(pos_, index_);
}



Avg::~Avg(){}


Aggregation *Avg::clone(void){
	Aggregation *newAggreOpe = new Avg(root, refNum, pos, index);
	return newAggreOpe;
}


void Avg::init(ATTRIBUTE_REC **attriRec_, unsigned int attriNum_){
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
				cout << "Error : Avg.class" << endl;
				exit(-1);
			}
		}
	}

}

void Avg::copyPos(unsigned int *pos_, unsigned int index_){
	pos = new unsigned int[index_];
	memcpy(pos, pos_, sizeof(unsigned int) * index_);
}

void Avg::setRefNode(Node *node){
	if(node->leftNode != NULL)setRefNode(node->leftNode);
	if(node->rightNode != NULL)setRefNode(node->rightNode);

	if(node->type == COLUMNREF_NODE){
		refNode[index] = (ColumnRefNode *)node;
		index++;
	}
}


void Avg::setAttriName(string attriName_){
	if(attriName_.length() > MAX_NAME_LENGTH - 1){
		cout << "Error too long AttriName : Avg.class" << endl;
		exit(-1);
	}
	strcpy(attriRec.attributeName, attriName_.c_str());
}

void Avg::inputData(PosVal **pv_, unsigned int pvNum_)
{
	for(unsigned int i = 0; i < index; i++){
		refNode[i]->setPosVal(pv_[pos[i]]);
	}
	tmpPV = (PosVal *)root->getValue();
	
	switch(flag){
		case(0):
			switch(tmpPV->type){
				case(INT):
					avg = (double)*(int *)tmpPV->value;
					flag = 1;
					break;
				case(LONG):
					avg = (double)*(long *)tmpPV->value;
					flag = 2;
					break;
				case(FLOAT):
					avg = (double)*(float *)tmpPV->value;
					flag = 3;
					break;
				case(DOUBLE):
					avg += *(double *)tmpPV->value;
					flag = 4;
					break;
				default:
					cout << "not define type : Avg.class" << endl;
					exit(-1);
					break;
			}
			break;
		case(1):
			tmpVal = (double)*(int *)tmpPV->value;
			avg = avg*count/(count+1) + tmpVal*1/(count+1);
			break;
		case(2):
			tmpVal = (double)*(long *)tmpPV->value;
			avg = avg*count/(count+1) + tmpVal*1/(count+1);
			break;
		case(3):
			tmpVal = (double)*(float *)tmpPV->value;
			avg = avg*count/(count+1) + tmpVal*1/(count+1);
			break;
		case(4):
			tmpVal = (double)*(double *)tmpPV->value;
			avg = avg*count/(count+1) + tmpVal*1/(count+1);
			break;
		default:
			cout << "Error : Avg.class" << endl;
			exit(-1);
	}
	count++;
}

PosVal *Avg::getValue(void){
	pv = new DoublePosVal(0, avg);

	return pv;
}	
