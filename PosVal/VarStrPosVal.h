#ifndef __VARSTRPOSVAL_H
#define __VARSTRPOSVAL_H

#include<iostream>
#include<string>
#include<cstring>
#include<cstdlib>
#include<cassert>
#include"CommonDataDef.h"
#include"PosVal.h"

//#define StrNCmp(a,b,c) strncmp((char *)a, (char *)b, c)

class VarStrPosVal : public PosVal{
	public:
		VarStrPosVal();
		VarStrPosVal(unsigned int pos_, unsigned short maxLen_);
		VarStrPosVal(VarStrPosVal& posVal_);
		virtual ~VarStrPosVal();
		virtual PosVal* clone();
		
		virtual void set(unsigned char *value_);
		virtual void set(unsigned int pos_, unsigned char *value_);
		virtual void set(DataType dataType_, unsigned int pos_, unsigned char *value_);
		virtual void printVal();
		virtual unsigned short getSize();

//		void setStr(string str_);
//		void setStr(unsigned int pos_, string str_);
		void setLength(unsigned short maxLen_);

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
		unsigned short maxLen;
		unsigned short valLen;
};

#endif
