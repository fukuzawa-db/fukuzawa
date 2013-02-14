#ifndef __FIXSTRPOSVAL_H
#define __FIXSTRPOSVAL_H

#include<iostream>
#include<string>
#include<cstring>
#include<cstdlib>
#include<cassert>
#include"CommonDataDef.h"
#include"PosVal.h"

using namespace std;

#define StrNCmp(a,b,c) strncmp((char *)a, (char *)b, c)

class FixStrPosVal : public PosVal{
	public:
		FixStrPosVal();
		FixStrPosVal(unsigned int pos_, unsigned short vallLen_);
		FixStrPosVal(FixStrPosVal& posVal_);
		virtual ~FixStrPosVal();
		virtual PosVal* clone();
		
		virtual void set(unsigned char *value_);
		virtual void set(unsigned int pos_, unsigned char *value_);
		virtual void set(DataType dataType_, unsigned int pos_, unsigned char *value_);
		virtual void printVal();
		virtual unsigned short getSize();

		void setStr(string str_);
		void setStr(unsigned int pos_, string str_);
		void setLength(unsigned short valLen_);
		void setNull(void);

		virtual PosVal &operator= (const PosVal&);
		virtual bool operator> (PosVal *);
		virtual bool operator< (PosVal *);
		virtual bool operator>= (PosVal *);
		virtual bool operator<= (PosVal *);
		virtual bool operator== (PosVal *);
		virtual bool operator!= (PosVal *);

/*
  		virtual bool operator > (string);
		virtual bool operator < (string);
  		virtual bool operator >= (string);
  		virtual bool operator <= (string);
  		virtual bool operator == (string);
  		virtual bool operator != (string);
*/
		unsigned short valLen;
};

#endif
