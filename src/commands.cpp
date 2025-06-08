#include "log.hpp"
#include <commands.hpp>

/*
Important: parse_and_excute returns params in reverse order
*/

Command::Command(String command,
		void (*setup)(Vector<String>,Command*),
		void (*loop)(Command*)
):command(command),setup(setup),loop(loop),speed(0),stack(Vector.new()){

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
      int16_t angle_x = args[5].toInt();
      int16_t angle_y = args[4].toInt();
      int16_t angle_z = args[3].toInt();
      int16_t gripper = args[2].toInt();
      uint16_t position = (uint16_t)args[1].toInt();
      Action action = (uint16_t)args[0].toInt();
      if(action == replace_with_input){
	mylogln("replace_with_input");
      }
      if(action == add_with_input){
	mylogln("add_with_input");
      }
      if(action == add_with_orientation){
	mylogln("add_with_orientation");
      }
      if(action == replace_with_orientation){
	mylogln("replace_with_orientation");
      }
      if(action == remove_it){
	mylogln("remove_it");
      }
      mylog("add pos with params:");
      mylog(angle_x);mylog(", ");
      mylog(angle_y);mylog(", ");
      mylog(angle_z);mylog(", ");
      mylog(gripper);mylog(", ");
      mylogln(position);
}
void add_loop(Command *command){}


Command commands[COMMAND_COUNT] ={
	Command("add",&add_setup,&add_loop),    
};

size_t current_command = 0;
String storage_array[MAX_COMMAND_LEN];
Vector<String> args(storage_array);

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
