import wx
import serial

COMMAND_COUNT = 10
ELEMENTS_IN_A_ROW_MOTION_GRID = 6


class MyPanel(wx.Panel):
    def __init__(self, parent):

        wx.Panel.__init__(self, parent)        
        
        # makes sure, that only one row is edited at the time and that only not edit mode ui can execute run
        self.edit_mode = False
        
        self.edit_row_functions = [lambda event,row=i: self.edit_row(event,row) for i in range(COMMAND_COUNT)]
        self.replace_current_position_functions = [lambda event,row=i: self.replace_current_position(event,row) for i in range(COMMAND_COUNT)]
        self.replace_given_position_functions = [lambda event,row=i: self.replace_given_position(event,row) for i in range(COMMAND_COUNT)]
        
        self.parrent_sizer = wx.BoxSizer(wx.VERTICAL)
       
        self.number_of_motions = 0


        self.motions = wx.GridSizer(COMMAND_COUNT, ELEMENTS_IN_A_ROW_MOTION_GRID, 1, 1)     
        self.parrent_sizer.Add(self.motions, COMMAND_COUNT, 0, 0)
        self.motions.Layout()
        
        my_sizer = wx.GridSizer(2, 5, 1, 1)     
        self.parrent_sizer.Add(my_sizer)
        
        self.text_ctrl_j1 = wx.TextCtrl(self)
        self.text_ctrl_j2 = wx.TextCtrl(self)
        self.text_ctrl_j3 = wx.TextCtrl(self)
        self.text_ctrl_gripper = wx.TextCtrl(self)
        
        add_given_position_button = wx.Button(self, label='add given position')
        add_given_position_button.Bind(wx.EVT_BUTTON, self.add_given_position)
        
        add_current_position_button = wx.Button(self, label='add current position')
        add_current_position_button.Bind(wx.EVT_BUTTON, self.add_current_position)
       
        run_button = wx.Button(self, label='run')
        run_button.Bind(wx.EVT_BUTTON, self.run_motions)        

        stop_button = wx.Button(self, label='stop')
        stop_button.Bind(wx.EVT_BUTTON, self.stop_motions)        

        my_sizer.Add(self.text_ctrl_j1, 0, wx.ALL, 5)        
        my_sizer.Add(self.text_ctrl_j2, 0, wx.ALL, 5)        
        my_sizer.Add(self.text_ctrl_j3, 0, wx.ALL, 5)        
        my_sizer.Add(self.text_ctrl_gripper, 0, wx.ALL, 5)        
        my_sizer.Add(add_given_position_button, 0, wx.ALL | wx.CENTER, 5)        
        
        my_sizer.Add(add_current_position_button, 0, wx.ALL | wx.CENTER, 5)        
        my_sizer.Add(run_button, 0, wx.ALL | wx.CENTER, 5)        
        my_sizer.Add(stop_button, 0, wx.ALL | wx.CENTER, 5)        


        self.motions_array = [wx.StaticText(self, -1, "no motions are configured")]
        self.motions.Add(self.motions_array[0], 0, wx.ALL, 5)

        self.SetSizer(self.parrent_sizer)
        
        self.robot_arm = serial.Serial("/dev/ttyUSB0",timeout=1, baudrate=9600)
        #wait until robot arm is ready
        while True: 
            read_data = self.robot_arm.readline().decode("utf-8")
            if(read_data != ""):
                print(read_data)
                if "ready" in read_data: break
    
    def update_motions(self):
        #clear motions
        self.motions.Clear()
        
        for i in self.motions_array:
            i.Destroy()
        del(self.motions_array[:])

        #parse new motions
        self.robot_arm.write(b"get")
        while True:
            read_data = self.robot_arm.readline().decode("utf-8")
            if "`" in read_data:
                motions_strings = read_data[read_data.find("`")+1:read_data.find("(")-1].split(";")   
                for i,motion in enumerate(motions_strings):
                    for angle in motion.split(","):
                        self.motions_array.append(wx.StaticText(self, -1, angle))         
                   
                    bnt_edit = wx.Button(self, label="edit")
                    
                    bnt_edit.Bind(wx.EVT_BUTTON, self.edit_row_functions[i])
                    self.motions_array.append(bnt_edit)
                    
                    bnt_delete = wx.Button(self, label="delete")
                    bnt_delete.Bind(wx.EVT_BUTTON, self.delete_row)
                    self.motions_array.append(bnt_delete)

                break


        for i in self.motions_array:
            self.motions.Add(i, 0, wx.ALL, 5)         
        
        self.motions.Layout()
        self.parrent_sizer.Layout()


    def add_given_position(self, event):
        try:
             j1 = str(int(self.text_ctrl_j1.GetValue()))
             j2 = str(int(self.text_ctrl_j2.GetValue()))
             j3 = str(int(self.text_ctrl_j3.GetValue()))
             gripper = str(int(self.text_ctrl_gripper.GetValue()))
        except:
             print("these are not valid ints")
             return;
        if not j1 or not j2 or not j3 or not gripper:
            print("You didn't enter anything in on textbox!")
            return
        self.send_command(f"add {j1} {j2} {j3} {gripper} 0 1".encode("utf-8"))
        self.update_motions()

    def add_current_position(self, event):
        self.send_command(b"add 0 0 0 0 0 2")
        self.update_motions()
    
    def run_motions(self,event):
        self.send_command(b"run")
    
    def stop_motions(self,event):
        self.send_command(b"stop")
    
    def edit_row(self,event,row):# Work in Progress
        print(row)
        
        #clear motions
        self.motions.Clear()
        index = row*ELEMENTS_IN_A_ROW_MOTION_GRID
        for i in range(index,index+4):
            label = self.motions_array[i].GetLabel()
            self.motions_array[i].Destroy()
            self.motions_array[i] = wx.TextCtrl(self,value=label)
        
        self.motions_array[index+4].Destroy()
        self.motions_array[index+4] = wx.Button(self,label="current position")
        self.motions_array[index+4].Bind(wx.EVT_BUTTON, self.replace_current_position_functions[row])

        self.motions_array[index+5].Destroy()
        self.motions_array[index+5] = wx.Button(self,label="done")
        self.motions_array[index+5].Bind(wx.EVT_BUTTON, self.replace_given_position_functions[row])


        for i in self.motions_array:
            self.motions.Add(i, 0, wx.ALL, 5)         
        
        self.motions.Layout()
        self.parrent_sizer.Layout()
        
    def delete_row(self,event):
        print("delete")
    
    def replace_current_position(self,event,row):
        self.motions.Clear()
        self.send_command(f"add 0 0 0 0 {row} 3".encode())
        self.update_motions()

    def replace_given_position(self,event,row):
         index = row*ELEMENTS_IN_A_ROW_MOTION_GRID
         try:
             j1 = str(int(self.motions_array[index+0].GetValue()))
             j2 = str(int(self.motions_array[index+1].GetValue()))
             j3 = str(int(self.motions_array[index+2].GetValue()))
             gripper = str(int(self.motions_array[index+3].GetValue()))
         except:
             print("these are not valid ints")
             return;
         if not j1 or not j2 or not j3 or not gripper:
            print("You didn't enter anything in on textbox!")
            return

         self.send_command(f"add {j1} {j2} {j3} {gripper} {row} 0".encode())
         self.update_motions()

    def send_command(self,cmd:bytes):
        self.robot_arm.write(cmd)
        print(cmd)
        while True:
            read_data = self.robot_arm.readline().decode("utf-8")
            if read_data != "":
                print(read_data)
                return

    def __del__(self):
        self.robot_arm.close()
        super().Destroy()

class MyFrame(wx.Frame):    
    def __init__(self):
        super().__init__(parent=None, title='Robot arm controll')
        self.SetSize(1024,720)
        self.panel = MyPanel(self)
        self.Show()

if __name__ == '__main__':
    app = wx.App()
    frame = MyFrame()

    app.MainLoop()



#arduino.write(b"add 20 20 30 40 0 2")

