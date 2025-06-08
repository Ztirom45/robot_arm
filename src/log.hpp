#pragma once
//#define DEBUG

#ifndef DEBUG
	#include <Arduino.h>
	void mylog(String);
	void mylog(float);
	void mylog(int);
	void mylog(size_t);

	void mylogln(String);
	void mylogln(float);
	void mylogln(int);
	void mylogln(size_t);
	
#endif // !DEBUG

#ifdef DEBUG
	//TODO properly implement debug mylogln
	#include <avr8-stub.h>
	void mylog(String);
	void mylog(float);
	void mylog(int);
	void mylog(size_t);
	void mylogln(String);
	void mylogln(float);
	void mylogln(int);
	void mylogln(size_t);

#endif 

