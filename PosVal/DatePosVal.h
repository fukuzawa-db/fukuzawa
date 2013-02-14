#ifndef __DATEPOSVAL_H
#define __DATEPOSVAL_H

#include<iostream>
#include<cstdlib>
#include<string>
#include<cstring>
#include<cassert>
#include"CommonDataDef.h"
#include"PosVal.h"


class DatePosVal : public PosVal{
	public:
		DatePosVal();
		DatePosVal(unsigned int pos_, unsigned char *value_);
		DatePosVal(DatePosVal& posVal_);
		virtual ~DatePosVal();
		virtual PosVal* clone();
		
		virtual void set(unsigned char *value_);
		virtual void set(unsigned int pos_, unsigned char *value_);
		virtual void set(DataType dataType_, unsigned int pos_, unsigned char *value_);
		virtual void printVal();
		virtual unsigned short getSize();
		
		void filterYear(void);
		void filterMonth(void);
		void filterDay(void);
		
		virtual PosVal &operator= (const PosVal&);
		virtual bool operator> (PosVal *);
		virtual bool operator< (PosVal *);
		virtual bool operator>= (PosVal *);
		virtual bool operator<= (PosVal *);
		virtual bool operator== (PosVal *);
		virtual bool operator!= (PosVal *);
/*
  		virtual bool operator > (unsigned int);
		virtual bool operator < (unsigned int);
  		virtual bool operator >= (unsigned int);
  		virtual bool operator <= (unsigned int);
  		virtual bool operator == (unsigned int);
  		virtual bool operator != (unsigned int);
*/
};

#endif
