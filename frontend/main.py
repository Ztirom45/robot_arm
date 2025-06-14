import wx
import serial

class MyPanel(wx.Panel):
    def __init__(self, parent):
        wx.Panel.__init__(self, parent)        
        self.parrent_sizer = wx.BoxSizer(wx.VERTICAL)
        
        self.motions = wx.GridSizer(10, 5, 1, 1)     
        self.parrent_sizer.Add(self.motions, 10, 0, 0)
        
        my_sizer = wx.GridSizer(2, 5, 1, 1)     
        self.parrent_sizer.Add(my_sizer)

        self.text_ctrl_j1 = wx.TextCtrl(self)
        self.text_ctrl_j2 = wx.TextCtrl(self)
        self.text_ctrl_j3 = wx.TextCtrl(self)
        self.text_ctrl_gripper = wx.TextCtrl(self)
        
        add_given_position_button = wx.Button(self, label='add current position')
        add_given_position_button.Bind(wx.EVT_BUTTON, self.add_given_position)
        
        my_sizer.Add(self.text_ctrl_j1, 0, wx.ALL, 5)        
        my_sizer.Add(self.text_ctrl_j2, 0, wx.ALL, 5)        
        my_sizer.Add(self.text_ctrl_j3, 0, wx.ALL, 5)        
        my_sizer.Add(self.text_ctrl_gripper, 0, wx.ALL, 5)        
        
        my_sizer.Add(add_given_position_button, 0, wx.ALL | wx.CENTER, 5)        

        add_current_position_button = wx.Button(self, label='add current position')
        add_current_position_button.Bind(wx.EVT_BUTTON, self.add_current_position)
        my_sizer.Add(add_current_position_button, 0, wx.ALL | wx.CENTER, 5)        
        
        self.SetSizer(self.parrent_sizer)        
    
    def add_given_position(self, event):
        j1 = self.text_ctrl_j1.GetValue()
        j2 = self.text_ctrl_j2.GetValue()
        j3 = self.text_ctrl_j3.GetValue()
        gripper = self.text_ctrl_gripper.GetValue()
        if not j1 or not j2 or not j3 or not gripper:
            print("You didn't enter anything in on textbox!")
            return
        print(f"add {j1} {j2} {j3} {gripper} 0 1".encode("utf-8"))
        new_btn = wx.Button(self, label="test")
        self.parrent_sizer.Add(new_btn, 0, wx.ALL, 5)         
        #self.motions.Layout()
        self.parrent_sizer.Layout()

    def add_current_position(self, event):
        print(b"add 0 0 0 0 0 2")
        new_btn = wx.Button(self, label="test")
        self.motions.Add(new_btn, 0, wx.ALL, 5)         
        self.motions.Layout()
        self.parrent_sizer.Layout()


class MyFrame(wx.Frame):    
    def __init__(self):
        super().__init__(parent=None, title='Robot arm controll')
        self.panel = MyPanel(self)  
        self.Show()

if __name__ == '__main__':
    app = wx.App()
    frame = MyFrame()
    app.MainLoop()

#arduino = serial.Serial("/dev/ttyUSB1",timeout=1, baudrate=9600)

# wait until robot arm is ready
#while True: 
#    read_data = arduino.readline().decode("utf-8")
#    if(read_data != ""):
#        print(read_data)
#        if "ready" in read_data: break

#arduino.write(b"add 20 20 30 40 0 2")
#while True: 
#    read_data = arduino.readline().decode("utf-8")
#    if(read_data != ""):
#        print(read_data)
#
#arduino.close()
