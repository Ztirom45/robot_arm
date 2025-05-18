/*
It works !!!!
make sure to install the right lib:
arduino-libraries/Servo@^1.2.2
*/

#include <Arduino.h>
#include <Servo.h>
#include <inverse_kinematics.hpp>


Servo j1;
Servo j2;
Servo j3;
Servo gripper;

/*
Still work in progress
not reverseble
=> robot can't get controll easely back
*/
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
    Serial.print(j1_a);
    Serial.print(", ");
    Serial.print(j2_a);
    Serial.print(", ");
    Serial.println(j3_a);
}

void move_arm(float x, float y, float z){
    set_arm(x,y,z);
    delay(2000);
    float a_j1 = degree_2_radian(j1.read());
    float a_j2 = degree_2_radian(j2.read());
    float a_j3 = degree_2_radian(j3.read());
    Serial.print("set to ");
    Serial.print(a_j1);Serial.print(" ");
    Serial.print(a_j2);Serial.print(" ");
    Serial.print(a_j3);Serial.print(" ");
    Serial.println(" ");
}

void loop() {
    /*
    set_arm(0,2*4.9,0);
    set_arm(0,4.9,-4.9);
    set_arm(0,0,2*4.9);
    set_arm(0,-2*4.9,0);
    set_arm(0,-4.9,-4.9);
    */
    /*
    move_arm(5,5,0);
    move_arm(-5,5,0);
    move_arm(-5,-5,0);
    move_arm(5,-5,0);
    */
    //move_arm(0,17.9,0);
    //move_arm(0,0,17.9);
    //move_arm(17.9,0,0);
}

