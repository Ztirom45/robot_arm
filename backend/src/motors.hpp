#pragma once

#include <Servo.h>
#include <inverse_kinematics.hpp>
#include <log.hpp>
#include <commands.hpp>


#define DEGREE_ACURACY 4

void enable_user_depositioning();
void disable_user_depositioning();
void setup_motors();
void move_arm(float x, float y, float z);
void set_arm(float x,float y, float z);
Motion get_arm_position();
void set_arm_angle(Motion goal);
bool move_arm_angle(Motion goal,int speed);

struct FeedbackServo: public Servo{
	int feedback_pin;
	int read();
	float factor_analogRead;//analogRead*factor_analogRead = angle_in_degree
	int zero_degreeanalogRead;//
	void calibration();
	FeedbackServo(int);
};

extern FeedbackServo j1;
extern FeedbackServo j2;
extern FeedbackServo j3;
extern Servo gripper;
extern bool user_depositioning_enabled;
