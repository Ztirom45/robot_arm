# robot_arm
a robotic arm with fancy contoroll options

## features
- inverse cinematics postion setting
### [ ] save postions and move to them
- commands:
[ ] set(int angle_x,int angle_y, int angle_z, gripper,position)
- positon >= 0: replace position_stack[position]
- position == -1: add to top of position_stack
- angle_y > 360: remove positon from motion_stack
[ ] run()
- executes motion_stack from motion_stack[0] to motions_stack[n]
[] stop()
- breacks run()
[ ] get()
- returns
    [ ] motion_stack
    [ ] len(motion_stack)
    [ ] max_len(motion_stak)
    [ ] speed

### [ ] frontend ui for commands

