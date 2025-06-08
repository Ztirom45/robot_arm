# robot_arm
a robotic arm with fancy contoroll options

## features
### - inverse cinematics postion setting

### - save postions and move to them
#### about commands 🖥️⟶ 🖥️:
- **IMPORTANT:** the whole string part can't longer than `MAX_COMMAND_LEN` (50 chars)
- at the moment only posible with copy paste a command into pio monitor

- a command is followed by parameters separatet with a space and ends with a \n
- example: `add 10 20 30 40 0`

#### commands list:
- [ ] set(int angle_x,int angle_y, int angle_z, gripper,position)
    - positon >= 0: replace position_stack[position]
    - position == -1: add to top of position_stack
    - position == -2: add current position at the top of the stack
    - angle_x > 360: remove positon from motion_stack
- [ ] run()
    - executes motion_stack from motion_stack[0] to motions_stack[n]
- [ ] stop()
    - breacks run()
- [ ] get()
    - returns
        - [ ] motion_stack
        - [ ] len(motion_stack)
        - [ ] max_len(motion_stak)
        - [ ] speed

### - TODO frontend ui for commands

