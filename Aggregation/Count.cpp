#include"Count.h"

using namespace std;

Count::Count(Node *root_, unsigned int refNum_){
	root = root_;
	refNum = refNum_;
	refNode = new ColumnRefNode*[refNum];
	index = 0;
	setRefNode(root);
	pv = NULL;
	attriRec.tableID = 0;
	attriRec.attributeID = 0;
	attriRec.dataType = LONG;
	strcpy(attriRec.attributeName, "Count");
	count = 0;
}


Count::~Count(){}

Aggregation *Count::clone(void){
	Aggregation *newAggreOpe = new Count(root, refNum);
	return newAggreOpe;
}

void Count::init(ATTRIBUTE_REC **attriRec_, unsigned int attriNum_){
}


void Count::setRefNode(Node *node){
	if(node->leftNode != NULL)setRefNode(node->leftNode);
	if(node->rightNode != NULL)setRefNode(node->rightNode);

	if(node->type == COLUMNREF_NODE){
		refNode[index] = (ColumnRefNode *)node;
		index++;
	}
}


void Count::setAttriName(string attriName_){
	if(attriName_.length() > MAX_NAME_LENGTH - 1){
		cout << "Error too long AttriName : Count.class" << endl;
		exit(-1);
	}
	strcpy(attriRec.attributeName, attriName_.c_str());
}

void Count::inputData(PosVal **pv_, unsigned int pvNum_)
{
	count++;
}

PosVal *Count::getValue(void){
	pv = new LongPosVal(0, count);
	return pv;
}	
