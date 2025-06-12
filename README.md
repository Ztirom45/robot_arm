# robot_arm
a robotic arm with fancy contoroll options

## features
### - inverse cinematics postion setting

### - save postions and move to them:
#### about commands 🖥️⟶ 🖥️:
- **IMPORTANT:** the whole string part can't longer than `MAX_COMMAND_LEN` (50 chars)
- at the moment only posible with copy paste a command into pio monitor

- a command is followed by parameters separatet with a space and ends with a \n
- examples: `add 20 20 30 40 0 2`,`get`

#### commands list:
- [x] set(int angle_x,int angle_y, int angle_z, gripper,uint position,unint action)
    - [x] action == 0: replace at position with input_motion(angle_x,angle_y,angle_z,gripper)
    - [x] action == 1: add input_motion to top of position_stack
    - [x] action == 2: add current robotic arm position at the top of the stack (does not work with the harware)
    - [x] action == 3: replace current robotic arm position at given position argument of stack (does not work with the harware)
    - [x] action == 4: remove element positon from motion_stack
- [ ] run()
    - executes motion_stack from motion_stack[0] to motions_stack[n]
- [ ] stop()
    - breacks run()
- [x] get()
    - returns:
        - [x] motion_stack
        - [x] len(motion_stack)
        - [x] max_len(motion_stak)
        - [ ] speed

## - TODO add gripper feedback

### - TODO frontend ui for commands


## Hardware:
- basic 9g servos like the SG92R
- The Servos are moded to read position as it can be seen here:
    - https://www.youtube.com/watch?v=S7aVcis3ntk
    - https://www.instructables.com/Servo-Feedback-Hack-free/
