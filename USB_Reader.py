import os
import sys
import serial
import time
import json

# File's Handling variables
Path_To_Storage_LogFiles = '/home/pi/Desktop/Log_Files'
LogFilename = 'RaspiWeatherStation_Log_' + str(time.time()) + '.csv'
Header = 'Temperature, Humidity, Timestamp, Date \n'

# Create first log file and write header
LogFile = open(os.path.join(Path_To_Storage_LogFiles,LogFilename),'w')
LogFile.write(Header)
LogFile.close()

# 24 hours timer
time_0 = time.time()
DAY = 24*3600 

# Open bus 
bus = serial.Serial('/dev/ttyACM0', 9600, timeout = 5)

# Read Bus & Show message for command line
while True:

        # Change LogFilename, if a day passed 
        if (time.time()-time_0) > DAY:

                # New filename
                LogFilename = 'RaspiWeatherStation_Log_' + str(time.time()) + '.csv'

                # Write header
                LogFile = open(os.path.join(Path_To_Storage_LogFiles,LogFilename),'w')
                LogFile.write(Header)
                LogFile.close()


        # any message?
        ThereIsMessage = bus.in_waiting > 0

        if ThereIsMessage:

                # Get time as timestamp and date form
                current_time = time.time()
                date = time.ctime()
                        
                # Get bus message 
                message = bus.readline()

                # Decode message
                decoded_message = message.decode('utf8')

                # Log message  ==>> decoded_message.rstrip() that functio quit \n
                LogMessage = decoded_message.rstrip() + ', ' + str(current_time) + ', ' + date + '\n'

                # Write data into current log_file
                LogFile = open(os.path.join(Path_To_Storage_LogFiles,LogFilename),'a')
                LogFile.write(LogMessage)
                LogFile.close()
                




