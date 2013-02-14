#ifndef __INTPOSVAL_H
#define __INTPOSVAL_H

#include<iostream>
#include<cstdlib>
#include<cassert>
#include"CommonDataDef.h"
#include"PosVal.h"

class IntPosVal : public PosVal{
	public:
		IntPosVal();
		IntPosVal(unsigned int pos_, int value_);
		IntPosVal(IntPosVal& posVal_);
		virtual ~IntPosVal();
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

  		virtual bool operator > (int);
		virtual bool operator < (int);
  		virtual bool operator >= (int);
  		virtual bool operator <= (int);
  		virtual bool operator == (int);
  		virtual bool operator != (int);

		int intValue;
};

#endif
