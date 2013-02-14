#ifndef __COLUMNREFNODE_H
#define __COLUMNREFNODE_H

#include<iostream>

#include"CommonDataDef.h"
#include"Node.h"
#include"PosVal.h"


class ColumnRefNode : public Node{
	public:
		ColumnRefNode();
		~ColumnRefNode();

		virtual void *getValue(void);
		void setPosVal(PosVal *pv);

		PosVal *pv;
		unsigned int tableID;
		unsigned int attriID;
		unsigned int position;
};



#endif
