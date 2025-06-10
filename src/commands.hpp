/*
this is the library for all commands that can be send via mqtt
TODO smartpointer
*/

#pragma once


#include <Arduino.h>
#include <log.hpp>
#include <Vector.h>

#define MAX_COMMAND_LEN 50
#define MAX_NUMBER_OF_MOTIONS 10
#define COMMAND_COUNT 4
#define ANGULAR_VELOCITY 5//°/s

struct Motion{
	int16_t angle_x;
	int16_t angle_y;
	int16_t angle_z;
	int16_t gripper;
};

struct Command{
	String command;
	void (*setup)(Vector<String>,Command*);
	void (*loop)(Command*);
	Motion position_goal;
	Command(
		String command,
		void (*setup)(Vector<String>,Command*),
		void (*loop)(Command *command)
	);
	
	
};
void init_commands();

void add_setup(Vector<String> args,Command *command);
void add_loop(Command *command);

void get_setup(Vector<String> args,Command *command);
void get_loop(Command *command);

void run_setup(Vector<String> args,Command *command);
void run_loop(Command *command);

void stop_setup(Vector<String> args,Command *command);
void stop_loop(Command *command);





extern Command commands[COMMAND_COUNT];

void parse_and_execute_action(String action);
	
