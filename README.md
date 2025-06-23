# robot_arm
a robotic arm with fancy control options

<img src="https://github.com/Ztirom45/robot_arm/blob/main/rsc/arm.jpg"/>


## usage
- upload the code by: `make` in backend directory
- run frontend: `python3 main.py` in frontend directory
    - make sure to install `wxpython` and `serial`
    - it could take a while for the UI to load because it waits, until calibration is done
    - maybe you need to manually reset the robot arm via a reset button

## Features
- setting position via hand and adding them to an instruction chain, that can be played
- ⚙️inverse kinematics (implemented, but not used)
- 🔧control via command system over USB
- 🖥️frontend UI:
<img src="https://github.com/Ztirom45/robot_arm/blob/main/rsc/ui.png"/>


## Documentation

### - save positions and move to them:
#### about commands 🖥️⟶ 🖥️:
- **IMPORTANT:** the whole string part can't longer than `MAX_COMMAND_LEN` (50 chars)
- maybe you need to copy paste a command into pio monitor, if you want to don't want to use the ui

- A command is followed by parameters seperatet with a space and ends with a \n
- examples: `add 20 20 30 40 0 2`,`get`

#### commands list:
- [x] set(int angle_x,int angle_y, int angle_z, gripper,uint position,unint action)
    - [x] action == 0: replace at position with input_motion(angle_x,angle_y,angle_z,gripper)
    - [x] action == 1: add input_motion to top of position_stack
    - [x] action == 2: add current robotic arm position at the top of the stack
    - [x] action == 3: replace current robotic arm position at given position argument of stack
    - [x] action == 4: remove element position from motion_stack
- [x] run()
    - executes motion_stack from motion_stack[0] to motions_stack[n]
- [x] stop()
    - breaks run()
- [x] get()
    - returns:
        - [x] motion_stack
        - [x] len(motion_stack)
        - [x] max_len(motion_stak)


### - TODO: add gripper feedback and implement proper control

## Hardware:
- basic 9g servos like the SG92R
- The Servos are moded to read the Setvo positions, as it can be seen here:
    - https://www.youtube.com/watch?v=S7aVcis3ntk
    - https://www.instructables.com/Servo-Feedback-Hack-free/
