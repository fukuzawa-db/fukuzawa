#ifndef __VALUENODE_H
#define __VALUENODE_H

#include<iostream>

#include"CommonDataDef.h"
#include"PosVal.h"
#include"Node.h"


class ValueNode : public Node{
	public:
		ValueNode();
		ValueNode(PosVal *pv_);
		~ValueNode();
		
		void setPosVal(PosVal *pv_);
		void *getValue(void);

		PosVal *pv;
};
#endif
