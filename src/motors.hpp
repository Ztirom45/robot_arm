#pragma once

#include <Servo.h>
#include <inverse_kinematics.hpp>
#include <log.hpp>
#include <commands.hpp>

void enable_user_depositioning();
void disable_user_depositioning();
void setup_motors();
void move_arm(float x, float y, float z);
void set_arm(float x,float y, float z);
Motion get_arm_position();


extern Servo j1;
extern Servo j2;
extern Servo j3;
extern Servo gripper;
extern bool user_depositioning_enabled;
