import serial

arduino = serial.Serial("/dev/ttyUSB1",timeout=1, baudrate=9600)

while True: 
	print(arduino.readline().decode("utf-8"))
