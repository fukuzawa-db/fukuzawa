#ifndef __TIMER_H_
#define __TIMER_H_


#include<iostream>
#include<stdio.h>
#include<string>
#include<sys/time.h>
#include <sys/resource.h>

class Timer{
public:
	Timer(void);
	~Timer(void);
	
	void start(void);
	void stop(void);
	void reset(void);
	void showTime(void);
	void showTime(char *str_);
private:
	struct rusage usage;
	struct timeval s, e;
	struct timeval ut1, ut2;
	struct timeval st1, st2;
	int flag;
	double sum;
	double user,sys;
};


#endif
