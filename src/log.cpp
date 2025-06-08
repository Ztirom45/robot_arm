#include "HardwareSerial.h"
#include <log.hpp>
#ifdef DEBUG
void mylog(String a){
	debug_message(a.c_str());
}

void mylog(int a){
	char result[8];
	dtostrf(a, 6, 2, result); // Leave room for too large numbers!
	debug_message(result);
}

void mylog(float a){
	char result[8];
	dtostrf(a, 6, 2, result); // Leave room for too large numbers!
	debug_message(result);
}
void mylog(size_t a){
	char result[8];
	dtostrf(a, 6, 2, result); // Leave room for too large numbers!
	debug_message(result);
}

//TODO properly implement debug mylogln
void mylogln(int a){mylog(a);}
void mylogln(float a){mylog(a);}
void mylogln(String a){mylog(a);}
void mylogln(size_t a){mylog(a);}
#endif
#ifndef DEBUG

void mylog(int a){
	Serial.print(a);
}
void mylog(String a){
	Serial.print(a);
}
void mylog(size_t a){
	Serial.print(a);
}
void mylog(float a){
	Serial.print(a);
}

void mylogln(int a){
	Serial.println(a);
}
void mylogln(String a){
	Serial.println(a);
}
void mylogln(size_t a){
	Serial.println(a);
}
void mylogln(float a){
	Serial.println(a);
}
#endif
