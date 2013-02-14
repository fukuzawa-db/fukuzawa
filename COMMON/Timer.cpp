#include"Timer.h"
using namespace std;

Timer::Timer(void){
	sum = 0.0;
	user = 0.0;
	sys = 0.0;
	flag = 0;
};

Timer::~Timer(){};

void Timer::start(void)
{
	if(flag == 0){
		flag = 1;
		sleep(2);
	}
		
	getrusage(RUSAGE_SELF, &usage );
	ut1 = usage.ru_utime;
	st1 = usage.ru_stime;
	gettimeofday(&s, NULL);
}

void Timer::reset(void){
	sum = 0.0;
	user = 0.0;
	sys = 0.0;
}

void Timer::stop(void){
	gettimeofday(&e, NULL);
	getrusage(RUSAGE_SELF, &usage );
	ut2 = usage.ru_utime;
	st2 = usage.ru_stime;
	sum += (e.tv_sec - s.tv_sec) + (e.tv_usec - s.tv_usec)*1.0E-6;
	user += (ut2.tv_sec - ut1.tv_sec) + (ut2.tv_usec - ut1.tv_usec)*1.0E-6;
	sys += (st2.tv_sec - st1.tv_sec) + (st2.tv_usec - st1.tv_usec)*1.0E-6;
}

void Timer::showTime(void){
	cout << "real : ";
	printf("%lf\n", sum);
	cout << "user : ";
	printf("%lf\n", user);
	cout << "sys  : ";
	printf("%lf\n", sys);
	sleep(2);
}

void Timer::showTime(char *str_){
	cout << " --- " << str_ << " --- " << endl;
	cout << "real : ";
	printf("%lf\n", sum);
	cout << "user : ";
	printf("%lf\n", user);
	cout << "sys  : ";
	printf("%lf\n", sys);
	sleep(2);
}
