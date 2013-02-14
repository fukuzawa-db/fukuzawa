#ifndef __LONGPOSVAL_H
#define __LONGPOSVAL_H

#include<iostream>
#include<cstdlib>
#include<cassert>
#include"CommonDataDef.h"
#include"PosVal.h"


class LongPosVal : public PosVal{
	public:
		LongPosVal();
		LongPosVal(unsigned int pos_, long value_);
		LongPosVal(LongPosVal& posVal_);
		virtual ~LongPosVal();
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

  		virtual bool operator > (long);
		virtual bool operator < (long);
  		virtual bool operator >= (long);
  		virtual bool operator <= (long);
  		virtual bool operator == (long);
  		virtual bool operator != (long);

		long longValue;
};

#endif
