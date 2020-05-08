import os
import sys
import serial
import datetime
import time
import json
import socket
from pydrive.auth import GoogleAuth
from pydrive.drive import GoogleDrive

# Login To Google Account
login = GoogleAuth()
login.LoadCredentialsFile("mycreds.txt")

# Google Drive User
DriveUser = GoogleDrive(login)


# Function to send string to web server by using GET Request
def SendDataToWebServer(MessageAsString):

        # Server data
        IP = 'localhost'
        PORT = '8888'

        # Get request as string
        RequestAsString = 'GET /CurrentData/' + MessageAsString + ' HTTP/1.1\r\nHost: ' + IP + ':' + PORT + '\r\n\r\n'
        
        try:
                # Open TCP/IP Socket        
                s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)                 

                # Connect to Web Server
                s.connect((IP,80))

                # Send Request 
                s.sendall(RequestAsString.encode())

                # Close Socket
                s.close
        except:
                print('Error sending current measure')

# Function to upload data to google drive (Cloud Storage)
def UploadFileToGoogleDrive(PathToLogFile, filename):

        # Properties of file to upload in json format
        File2Upload_Properties = {'title':filename}

        # Object to upload a log file (check propertires)
        File2Upload_Obj = DriveUser.CreateFile(File2Upload_Properties)  

        # Set content of the file from log-file path
        File2Upload_Obj.SetContentFile(PathToLogFile) 

        # Upload
        File2Upload_Obj.Upload()



# File's Handling variables
Path_To_Storage_LogFiles = '/home/raspi-of-malum/Desktop/Log_Files'
LogFilename = 'Raspi_Log_File_' + str(int(time.time())) + '.csv'
Header = 'Temperature,Humidity,Timestamp,Date \n'

# Create first log file and write header
LogFile = open(os.path.join(Path_To_Storage_LogFiles,LogFilename),'w')
LogFile.write(Header)
LogFile.close()

# 24 hours timer
time_0 = time.time()
DAY_STAMP = 24*3600 



# Open bus 
bus = serial.Serial('/dev/ttyACM0', 9600, timeout = 5)

# Read Bus & Show message for command line
while True:

        # Change LogFilename, if a day passed 
        if (time.time()-time_0) > DAY_STAMP:
                
                # Upload to google drive 
                UploadFileToGoogleDrive(os.path.join(Path_To_Storage_LogFiles,LogFilename), LogFilename)

                # Remove for local storage
                os.remove(os.path.join(Path_To_Storage_LogFiles,LogFilename)) 

                # New filename
                LogFilename = 'Raspi_Log_File_' + str(int(time.time())) + '.csv'

                # Write header
                LogFile = open(os.path.join(Path_To_Storage_LogFiles,LogFilename),'w')
                LogFile.write(Header)
                LogFile.close()
                
                # Update time_0
                time_0 = time.time()


        # any message?
        ThereIsMessage = bus.in_waiting > 30

        if ThereIsMessage:

                # Get time as timestamp and date form
                current_time = time.time()
                date = time.ctime()
                        
                # Get raw message 
                raw_message = bus.readline()
                print(raw_message)

                # Decode message (Quit 'b' char and '\n')
                decoded_message = raw_message.decode('utf8')
                decoded_message = decoded_message.rstrip()
                print(decoded_message)

                try:
                        # convert json to dict object. 
                        msgAsDict = json.loads(decoded_message)

                        # Send data to web sever (temperature, humidity, timestamp)
                        SendDataToWebServer(str(msgAsDict['Temperature']) + ',' + str(msgAsDict['Humidity']) + ',' + str(current_time))

                        # Append data to log files (as csv format)
                        LogMessage = str(msgAsDict['Temperature']) + ',' + str(msgAsDict['Humidity']) + ',' + str(current_time) + ',' + date + '\n'
                        print(LogMessage)

                        # Write data into current log_file
                        LogFile = open(os.path.join(Path_To_Storage_LogFiles,LogFilename),'a')
                        LogFile.write(LogMessage)
                        LogFile.close()
                except:
                        # Clean port
                        bus.flush()




