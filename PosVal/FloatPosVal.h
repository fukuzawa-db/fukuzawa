#ifndef __FLOATPOSVAL_H
#define __FLOATPOSVAL_H

#include<iostream>
#include<cstdlib>
#include<cassert>
#include"CommonDataDef.h"
#include"PosVal.h"


class FloatPosVal : public PosVal{
	public:
		FloatPosVal();
		FloatPosVal(unsigned int pos_, float value_);
		FloatPosVal(FloatPosVal& posVal_);
		virtual ~FloatPosVal();
		virtual PosVal* clone();
		
		virtual void set(unsigned char *value_);
		virtual void set(unsigned int pos_, unsigned char *value_);
		virtual void set(DataType dataType_, unsigned int pos_, unsigned char *value_);
		virtual void printVal();
		virtual unsigned short getSize();

		virtual PosVal &operator= (const PosVal&);
		virtual bool operator> (PosVal *);
		virtual bool operator< (PosVal *);
		virtual bool operator>= (PosVal *);
		virtual bool operator<= (PosVal *);
		virtual bool operator== (PosVal *);
		virtual bool operator!= (PosVal *);

  		virtual bool operator > (float);
		virtual bool operator < (float);
  		virtual bool operator >= (float);
  		virtual bool operator <= (float);
  		virtual bool operator == (float);
  		virtual bool operator != (float);

		float floatValue;
};

#endif
