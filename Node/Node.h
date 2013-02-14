#ifndef __NODE_H
#define __NODE_H

#include"CommonDataDef.h"

class Node{
	public:
		Node(){};
		virtual ~Node(){};

		virtual void *getValue(void) = 0;

		NODE_TYPE type;
	
		Node *leftNode;
		Node *rightNode;
		
		
};

#endif
