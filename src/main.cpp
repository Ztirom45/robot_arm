/*
It works !!!!
make sure to install the right lib:
arduino-libraries/Servo@^1.2.2
*/

#include "HardwareSerial.h"
#include <Arduino.h>
#include <Servo.h>
#include <inverse_kinematics.hpp>
#include <log.hpp>
#include <commands.hpp>

Servo j1;
Servo j2;
Servo j3;
Servo gripper;

/*
Still work in progress
not reverseble
=> robot can't get controll easely back
*/


String recived;

void enable_user_depositioning(){
    j1.detach();
    j2.detach();
    j3.detach();
    gripper.detach();
}

void setup() {
    Serial.begin(9600);
    j1.attach(6);
    j2.attach(5);
    j3.attach(3);
    gripper.attach(9);
    j1.write(90);
    j2.write(90);
    j3.write(90);
    delay(500);
    gripper.write(0);
    delay(2000);
    gripper.write(180); 
    delay(2000);
    enable_user_depositioning();
}

void set_arm(float x,float y, float z){
    float j1_a = J1_R(x, y);
    float j2_a = J2_R(HL(x,y), -z);
    float j3_a = J3_R(HL(x,y), -z);
    j1.write(j1_a);
    j2.write(j2_a);
    j3.write(j3_a);
    mylog(j1_a);
    mylog(", ");
    mylog(j2_a);
    mylog(", ");
    mylogln(j3_a);
}

void move_arm(float x, float y, float z){
    set_arm(x,y,z);
    delay(2000);
    float a_j1 = degree_2_radian(j1.read());
    float a_j2 = degree_2_radian(j2.read());
    float a_j3 = degree_2_radian(j3.read());
    mylog("set to ");
    mylog(a_j1);Serial.print(" ");
    mylog(a_j2);Serial.print(" ");
    mylog(a_j3);Serial.print(" ");
    mylogln(" ");
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

