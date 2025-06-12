/*
TODO fix depositioning
*/
#include "Arduino.h"
#include "Servo.h"
#include "log.hpp"
#include <motors.hpp>
void enable_user_depositioning(){ 
    mylogln((int)user_depositioning_enabled);
    if(user_depositioning_enabled){
      return;
    }
    j1.detach();
    j2.detach();
    j3.detach();
    gripper.detach();
    user_depositioning_enabled = true;
}
void disable_user_depositioning(){
  if(!user_depositioning_enabled){
    return;
  }
  j1.attach(6);  
  j2.attach(5);
  j3.attach(3);
  gripper.attach(9);
  user_depositioning_enabled = false;

}

void setup_motors(){
    disable_user_depositioning();
    j1.write(90);
    delay(500);
    j2.write(90);
    delay(500);
    j3.write(90);
    delay(500);
    gripper.write(0);
    delay(2000);
    gripper.write(180); 
    delay(2000);
    enable_user_depositioning();

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


Motion get_arm_position(){ 
  Motion arm_position = Motion{
    j1.read(),
    j2.read(),
    j3.read(),
    gripper.read()
  };

  return arm_position;
}

void set_arm_angle(Motion goal){
  j1.write(goal.angle_x);
  j2.write(goal.angle_y);
  j3.write(goal.angle_z);
  gripper.write(goal.gripper);
}

int FeedbackServo::read(){//conversion to voltage devided by PIv (at 180°) multiplied by 180°
                          //
    return analogRead(this->feedback_pin)/ 1023.0*5.0/PI*180.0;
}

FeedbackServo::FeedbackServo(int feedback_pin) : Servo(){
  this->feedback_pin = feedback_pin;
  pinMode(feedback_pin, INPUT);
}


FeedbackServo j1 = FeedbackServo(A2);
FeedbackServo j2 = FeedbackServo(A1);
FeedbackServo j3 = FeedbackServo(A0);
Servo gripper;
bool user_depositioning_enabled = true;
