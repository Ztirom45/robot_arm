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


device = usb.core.find(idVendor=0x403, idProduct=0x6001)

if device==None:
    raise ValueError("Device not found")
# Set the device configuration
device.get_active_configuration()


def send_command(cmd:bytes,endpoint):
    len_cmd = len(cmd)
    if(len_cmd > 64):
        raise OverflowError("cmd can't be longer than 64 bytes")
    global device
    cmd_64_bytes = cmd + b'\x00' * (64 - len_cmd)#raises overflow error if it is not exacly 64 bytes
    device.write(endpoint.bEndpointAddress, cmd_64_bytes)

reattach = False
if device.is_kernel_driver_active(0):
    reattach = True
    device.detach_kernel_driver(0)


endpoint = device[0][(0,0)][0]


send_command(b"add 45 45 45 45 180 1",endpoint)
send_command(b"run",endpoint)

if reattach:
    device.attach_kernel_driver(0)

#get_devices()
