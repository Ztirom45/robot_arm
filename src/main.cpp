/*
It works !!!!
make sure to install the right lib:
arduino-libraries/Servo@^1.2.2
*/

#include "HardwareSerial.h"
#include <Arduino.h>
#include <log.hpp>
#include <commands.hpp>
#include <motors.hpp>
/*
Still work in progress
not reverseble
=> robot can't get controll easely back
*/


String recived;

void setup() {
    Serial.begin(9600);
    setup_motors();
}

String read_message(){
	if(Serial.available()<=0){

	  return "";
	}
	recived = Serial.readString();
        mylogln(recived);
	return recived;
}

void loop() {
    String action = read_message();
    parse_and_execute_action(action);
}

