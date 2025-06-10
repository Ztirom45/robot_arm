#include "log.hpp"
#include "motors.hpp"
#include <commands.hpp>

/*
Important: parse_and_excute returns params in reverse order
*/

size_t current_command = 0;
String args_storage_array[MAX_COMMAND_LEN];
Motion motions_storage_array[MAX_NUMBER_OF_MOTIONS];
Vector<String> args(args_storage_array);
Vector<Motion> motion_stack(motions_storage_array);


Command::Command(String command,
		void (*setup)(Vector<String>,Command*),
		void (*loop)(Command*)
):command(command),setup(setup),loop(loop),speed(10){

}


bool check_params(String function_name,size_t number_of_params_wanted,size_t number_of_params_given){
	if(number_of_params_given!=number_of_params_wanted){
	mylog(function_name);
	mylog("expected ");
	mylog(number_of_params_wanted);
	mylog(" argument, but ");
	mylog(number_of_params_given);
	mylog(" were given");
	return true;
	}
	return false;
}
enum Action{
  replace_with_input,
  add_with_input,
  add_with_orientation,
  replace_with_orientation,
  remove_it
};

void add_setup(Vector<String> args,Command *command){
      if(check_params("add(angle_x,angle_y,angle_z,gripper,position)", 6, args.size())){
	return;
      }
      Motion input_motion = Motion{
	  (int16_t)args[5].toInt(),//angle_x
	  (int16_t)args[4].toInt(),//angle_y
	  (int16_t)args[3].toInt(),//angle_z
	  (int16_t)args[2].toInt()//gripper
      };
      uint16_t position = (uint16_t)args[1].toInt();
      Action action = (Action)args[0].toInt();
      switch(action){
       case replace_with_input:
	if(position < motion_stack.size()){
	mylogln("replace_with_input");
	  motion_stack.at(position) = (input_motion);
	}else{
	  mylogln("replacing not posible given position is not in stack");
	}
	return;
       
       case add_with_input:
	mylog("add_with_input len:");
	motion_stack.push_back(input_motion);
	mylogln(motion_stack.size());
	return;
      
       case add_with_orientation:
	mylogln("add_with_orientation");
	motion_stack.push_back(get_arm_position());
	mylogln(motion_stack.size());
	return;
      
       case replace_with_orientation:
	if(position < motion_stack.size()){	
	mylogln("replace_with_orientation");
	  motion_stack.at(position) = get_arm_position();
	}else{
	  mylogln("replacing not posible given position is not in stack");
	}
	return;
    
       case remove_it:
	mylogln("remove_it");
	motion_stack.remove(position);
	return;
      }
}
void add_loop(Command *command){}

void get_setup(Vector<String> args,Command *command){
      if(check_params("get()", 0, args.size())){
	return;
      }
      mylog("`");
      for (Motion i : motion_stack) {
	mylog(i.angle_x);mylog(", ");
	mylog(i.angle_y);mylog(", ");
	mylog(i.angle_z);mylog(", ");
	mylog(i.gripper);mylog(";");
      }
      mylog("len:");
      mylog(motion_stack.size());
      mylogln("´");
}

void get_loop(Command *command){}

Command commands[COMMAND_COUNT] ={
	Command("add",&add_setup,&add_loop),    
	Command("get",&get_setup,&get_loop),    
};
void parse_and_execute_action(String action){
  if(action==""){//string is empty
      commands[current_command].loop(&commands[current_command]);
      return;
    }
    mylog(action);
    
    args.clear();
    int pos = action.lastIndexOf(" ");
    while (pos != -1) {//separates string in reverse order and pushes to args
	String token = action.substring(pos, action.length());
	
	args.push_back(token);

	action.remove(pos, pos + token.length());
	pos = action.lastIndexOf(" ");

    }
    for(int i=0;i<COMMAND_COUNT;i++){
      if(commands[i].command == action){
	commands[i].setup(args,&commands[i]);
	current_command = i;
	return;
      }

    }

}
