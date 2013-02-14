#ifndef __RLEELEMENT_H
#define __RLEELEMENT_H

#include<cassert>

#include"PosVal.h" 
#include"CommonDataDef.h"

class RLEElement{
	public:
		RLEElement();
		RLEElement(PosVal *val_, unsigned int pos_, unsigned int rep_);
		RLEElement(const RLEElement &element_);
		~RLEElement();

		void setElement(PosVal *val_, int pos_, int rep_);
		void setElement(RLEElement *element_);
		void setNull();
		bool isNull();


		PosVal *value;
		unsigned int startPos;
		unsigned int repeat;

};

#endif
