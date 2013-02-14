#ifndef __AXPRNODE_H
#define __AXPRNODE_H

#include<iostream>
#include<cstdlib>
#include<cassert>

#include"CommonDataDef.h"
#include"Node.h"
#include"PosVal.h"


class AxprNode : public Node{
	public:
		AxprNode(AXPR_TYPE axpr_);
		AxprNode(AXPR_TYPE axpr_, Node *leftNode_, Node *rightNode_);
		~AxprNode();

		void setAxpr(AXPR_TYPE axpr_);
		void setLeftNode(Node *leftNode_);
		void setRightNode(Node *rightNode_);
		void setNode(Node *leftNode_, Node *rightNode_);

		AXPR_TYPE getAxpr(void);
		Node *getLeftNode(void);
		Node *getRightNode(void);

		void *getValue(void);

		int returnCode;

	private:
		AXPR_TYPE axpr;
};

#endif 
