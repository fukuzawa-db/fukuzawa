#ifndef __DOUBLEPOSVAL_H
#define __DOUBLEPOSVAL_H

#include<iostream>
#include<cstdlib>
#include<cassert>
#include"CommonDataDef.h"
#include"PosVal.h"


class DoublePosVal : public PosVal{
	public:
		DoublePosVal();
		DoublePosVal(unsigned int pos_, double value_);
		DoublePosVal(DoublePosVal& posVal_);
		virtual ~DoublePosVal();
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

  		virtual bool operator > (double);
		virtual bool operator < (double);
  		virtual bool operator >= (double);
  		virtual bool operator <= (double);
  		virtual bool operator == (double);
  		virtual bool operator != (double);

		double doubleValue;
};

#endif
