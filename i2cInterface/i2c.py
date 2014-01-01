
# Here is where the magic hapens,
# this program(?), script(?) will provide a way to
# comunicate the rPi with the swarm of microcontrollers
# wich is just one at the moment

import smbus
import time

bus = smbus.SMBus(0)
address = 0x04 #address of the rPi, the rest of the devices will 
               #have a sequential address starting in 0x05 


def write (value):
        bus.write_byte_data(address, 0, value)
        return -1

def read():
        input1 = bus.read_byte_data(address, 2)
        input2 = bus.read_byte_data(address, 3)
        input3 = bus.read_byte_data(address, 4)
        input4 = bus.read_byte_data(address, 5)
        input5 = (input1 << 8) +(input2 << 16) +( input3 << 24) + input4
        return input5

while True:
        write("A")                     #this is the password to be send so the arduino know what to do
        time.sleep(0.7)                
        result = read()
        print result
