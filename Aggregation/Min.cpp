#include"Min.h"

using namespace std;

Min::Min(Node *root_, unsigned int refNum_, DataType type_){
	root = root_;
	refNum = refNum_;
	refNode = new ColumnRefNode*[refNum];
	index = 0;
	setRefNode(root);
	pv = NULL;
	attriRec.tableID = 0;
	attriRec.attributeID = 0;
	attriRec.dataType = type_;
	strcpy(attriRec.attributeName, "Min");
}

Min::Min(Node *root_, unsigned int refNum_, DataType type_,  unsigned int *pos_, unsigned int index_){
	root = root_;
	refNum = refNum_;
	refNode = new ColumnRefNode*[refNum];
	index = 0;
	setRefNode(root);
	pv = NULL;
	attriRec.tableID = 0;
	attriRec.attributeID = 0;
	attriRec.dataType = type_;
	strcpy(attriRec.attributeName, "Min");
	
	copyPos(pos_, index_);
}


Min::~Min(){}

void Min::init(ATTRIBUTE_REC **attriRec_, unsigned int attriNum_){
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

void Min::copyPos(unsigned int *pos_, unsigned int index_){
	pos = new unsigned int[index_];
	memcpy(pos, pos_, sizeof(unsigned int) * index_);
}

Aggregation *Min::clone(void){
	Aggregation *newAggreOpe = new Min(root, refNum, attriRec.dataType, pos, index);
	return newAggreOpe;
}

void Min::setRefNode(Node *node){
	if(node->leftNode != NULL)setRefNode(node->leftNode);
	if(node->rightNode != NULL)setRefNode(node->rightNode);

	if(node->type == COLUMNREF_NODE){
		refNode[index] = (ColumnRefNode *)node;
		index++;
	}
}


void Min::setAttriName(string attriName_){
	if(attriName_.length() > MAX_NAME_LENGTH - 1){
		cout << "Error too long AttriName : Min.class" << endl;
		exit(-1);
	}
	strcpy(attriRec.attributeName, attriName_.c_str());
}

void Min::inputData(PosVal **pv_, unsigned int pvNum_)
{
	for(unsigned int i = 0; i < index; i++){
		refNode[i]->setPosVal(pv_[pos[i]]);
	}
	tmpPV = (PosVal *)root->getValue();
	assert(tmpPV->type == attriRec.dataType);
	if(pv == NULL){
		pv = tmpPV->clone();
	}else{
		if(*pv > tmpPV){
			delete pv;
			pv = tmpPV->clone();
		}
	}
}		

