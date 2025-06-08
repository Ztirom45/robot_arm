/*
this is the library for all commands that can be send via mqtt
TODO smartpointer
*/

#pragma once


#include <Arduino.h>
#include <log.hpp>
#include <Vector.h>

#define MAX_COMMAND_LEN 50


struct Command{
	String command;
	void (*setup)(Vector<String>,Command*);
	void (*loop)(Command*);
	int speed;//for looped motor functions
	Vector<int[4]> stack;
	Command(
		String command,
		void (*setup)(Vector<String>,Command*),
		void (*loop)(Command *command)
	);
	
	
};
void init_commands();

void add_setup(Vector<String> args,Command *command);
void add_loop(Command *command);

#define COMMAND_COUNT 1

extern Command commands[COMMAND_COUNT];

void parse_and_execute_action(String action);
	
