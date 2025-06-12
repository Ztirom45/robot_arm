/*
TODO fix depositioning
*/
#include "Arduino.h"
#include "Servo.h"
#include "commands.hpp"
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
    while(!move_arm_angle(Motion{90,90,90,180}, ANGULAR_VELOCITY)){};
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

bool move_arm_angle(Motion goal,int speed){//return true if its done
  Motion position = get_arm_position();
  Motion way_to_go = goal-position;
  Motion step = Motion{
    way_to_go.angle_x > speed ? speed : (way_to_go.angle_x < -speed ? -speed: way_to_go.angle_x),
    way_to_go.angle_y > speed ? speed : (way_to_go.angle_y < -speed ? -speed: way_to_go.angle_y),
    way_to_go.angle_z > speed ? speed : (way_to_go.angle_z < -speed ? -speed: way_to_go.angle_z),
    180//way_to_go.gripper > speed ? speed : (way_to_go.gripper < -speed ? -speed: way_to_go.gripper)
  };
  Motion motion{
    position.angle_x+step.angle_x,
    position.angle_y+step.angle_y,
    position.angle_z+step.angle_z,
    position.gripper+step.gripper
  };
  mylog(position.angle_x);
  mylog(", ");
  mylog(position.angle_y);
  mylog(", ");
  mylog(position.angle_z);
  mylog(":\t");
  mylog(way_to_go.angle_x);
  mylog(", ");
  mylog(way_to_go.angle_y);
  mylog(", ");
  mylog(way_to_go.angle_z);
  mylog(":\t");
  mylog(step.angle_x);
  mylog(", ");
  mylog(step.angle_y);
  mylog(", ");
  mylog(step.angle_z);
  mylog(":\t");
  mylog(motion.angle_x);
  mylog(", ");
  mylog(motion.angle_y);
  mylog(", ");
  mylogln(motion.angle_z);

  if(abs(step.angle_x)<min(DEGREE_ACURACY,speed)
  &&abs(step.angle_y)<min(DEGREE_ACURACY,speed)
  &&abs(step.angle_z)<min(DEGREE_ACURACY,speed)
  /*&&abs(step.gripper)<min(DEGREE_ACURACY,speed()*/){//implement gripper later if proper motor
    return true;
  }
  //set_arm_angle(position+step);
  for(int i=0;i<10;i++){//hope to conter the buggy hardware wich couse random motion in wrong direction
    set_arm_angle(motion);
    delay(10);
  }
  return false;
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
