#ifndef __POSVAL_H
#define __POSVAL_H

#include<iostream>

#include"CommonDataDef.h"



class PosVal{
	public:
		PosVal();
		virtual ~PosVal();
		virtual PosVal* clone()=0;
		
		virtual void set(unsigned char *value_)=0;
		virtual void set(unsigned int pos_, unsigned char *value_)=0;
		virtual void set(DataType dataType_, unsigned int pos_, unsigned char *value_)=0;
		virtual void printVal()=0;
		virtual unsigned short getSize()=0;
		virtual void setPos(unsigned int pos_){position = pos_; }

		virtual PosVal &operator= (const PosVal &)=0;
		virtual bool operator> (PosVal *)=0;
		virtual bool operator< (PosVal *)=0;
		virtual bool operator>= (PosVal *)=0;
		virtual bool operator<= (PosVal *)=0;
		virtual bool operator== (PosVal *)=0;
		virtual bool operator!= (PosVal *)=0;

		DataType type;
		unsigned int position;
		unsigned char* value;

};

#endif
