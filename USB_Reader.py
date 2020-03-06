import os, sys
import serial
import time

# Open bus 
bus = serial.Serial('/dev/ttyUSB0', 9600, timeout = 5)

# Read Bus & Show message for command line
while True:
     
     number_of_input_bytes = bus.in_waiting

     if number_of_input_bytes > 0:
        
        # Read message until '\n'char 
        message = bus.read_until()
        print(message)
