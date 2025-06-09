#pragma once

#include <Servo.h>
#include <inverse_kinematics.hpp>
#include <log.hpp>

void enable_user_depositioning();
void setup_motors();
void move_arm(float x, float y, float z);
void set_arm(float x,float y, float z);

extern Servo j1;
extern Servo j2;
extern Servo j3;
extern Servo gripper;
