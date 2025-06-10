# device Device: 1027:24577
import usb.core
import usb.util

def get_devices():
    # Find all connected USB devices
    devices = usb.core.find(find_all=True)

    # Print information about each device
    input("please plug off your robot arm and press enter")
    a = []
    for device in devices: 
        a.append(f"{device.idVendor}:{device.idProduct}") 
    input("please plug in your robot arm and press enter") 
    devices = usb.core.find(find_all=True)
    for device in devices: 
        if not(f"{device.idVendor}:{device.idProduct}" in a):
            print(f"your device is: {device.idVendor}:{device.idProduct}")
            return


def send_message():
    # Find the USB device
    device = usb.core.find(idVendor=1027, idProduct=24577)

    # Set the device configuration
    device.set_configuration()

    # Send data to the device
    endpoint = device[0][(0,0)][0]
    data = b'add 0 0 0 0 0 2'
    device.write(endpoint.bEndpointAddress, data)

get_devices()
#send_message()
