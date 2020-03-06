import os, sys
import serial
import time

# Open bus 
bus = serial.Serial('/dev/ttyACM0', 9600, timeout = 5)

# Read Bus & Show message for command line
while True:

        # Read message until '\n'char 
        message = bus.readline()

        print(message.decode('utf8','strict'))

