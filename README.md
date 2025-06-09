# robot_arm
a robotic arm with fancy contoroll options

## features
### - inverse cinematics postion setting

### - save postions and move to them:
#### about commands 🖥️⟶ 🖥️:
- **IMPORTANT:** the whole string part can't longer than `MAX_COMMAND_LEN` (50 chars)
- at the moment only posible with copy paste a command into pio monitor

- a command is followed by parameters separatet with a space and ends with a \n
- examples: `add 10 20 30 40 0 1`,`get`

#### commands list:
- [ ] set(int angle_x,int angle_y, int angle_z, gripper,uint position,unint action)
    - [x] action == 0: replace at position with input_motion(angle_x,angle_y,angle_z,gripper)
    - [x] action == 1: add input_motion to top of position_stack
    - [ ] action == 2: add current robotic arm position at the top of the stack
    - [ ] action == 3: replace current robotic arm position at given position argument of stack
    - [ ] action == 4: remove element positon from motion_stack
- [ ] run()
    - executes motion_stack from motion_stack[0] to motions_stack[n]
- [ ] stop()
    - breacks run()
- [ ] get()
    - returns:
        - [x] motion_stack
        - [x] len(motion_stack)
        - [ ] max_len(motion_stak)
        - [ ] speed

### - TODO frontend ui for commands

