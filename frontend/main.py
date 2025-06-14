import serial

arduino = serial.Serial("/dev/ttyUSB1",timeout=1, baudrate=9600)

while True: 
    read_data = arduino.readline().decode("utf-8")
    if(read_data != ""):
        print(read_data)
