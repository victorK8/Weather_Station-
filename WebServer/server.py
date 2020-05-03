# Server script

from flask import Flask, render_template, request, jsonify


import json
import os
import sys
import time
import datetime
import getpass as gp
from pydrive.auth import GoogleAuth
from pydrive.drive import GoogleDrive

# Take arguments
if len(sys.argv) >= 2:
    PORT = sys.argv[1]
else:
    PORT = 8888


# Google Drive Account
UserName = gp.getuser()
login = GoogleAuth()

if UserName == 'maluma':

    # If run server with my own pc 
    login.LoadCredentialsFile("home/maluma/Escritorio/Projects/Weather_Station-/mycreds.txt")

elif UserName == 'raspi-of-malum':
    # If run server with raspberry pi 
    login.LoadCredentialsFile("home/raspi-of-malum/Desktop/Weather_Station-/mycreds.txt") 

else:
    # No run with another user or device
    print("Not allow")
    exit(-1)

# Google Drive User
DriveUser = GoogleDrive(login)


#### Global Variables ####

# Current data 
CurrentData = {"Timestamp":2,"Date":"21/03/2020 10:10:10","Temperature": 30, "Humidity": 55}

# Data path (Change to 'home/pi/Desktop/LogFiles')
DataPath = '~/Desktop/LogFiles'

# Web server with Flask
WebServer = Flask(__name__)



# -------------------- WEB BACKEND ----------------- #

# Index page
@WebServer.route('/')
def index():

    # Get current measure
    global CurrentData

    try:
        # Prepare string to show in web html
        DateString = CurrentData['Date']
        TemperatureString = 'Temperature : ' + str(CurrentData['Temperature']) + ' [ºC]'
        HumidityString = 'Humidity : ' + str(CurrentData['Humidity']) + ' [%]'

    except:
        DateString = '-- / -- / --'
        TemperatureString = 'Temperature : -- [ºC]'
        HumidityString = 'Humidity : -- [%]' 


    return render_template('index.html', date = DateString, temperature = TemperatureString, humidity = HumidityString)

# Download page
@WebServer.route('/downloads.html')
def downloads():
    return render_template('downloads.html')

# Dashboard
@WebServer.route('/dashboard.html')
def dashboard():
    return render_template('dashboard.html')

# About page
@WebServer.route('/about.html')
def about():
    return render_template('about.html')

# Music page
@WebServer.route('/music.html')
def music():
       return render_template('music.html')


# Location page
@WebServer.route('/location.html')
def location():
       return render_template('location.html')


# --------------------- API -------------------------- # 

### Current Data

# Url for get current measure
@WebServer.route('/Data/Current/All', methods=['GET'])
def GetAllCurrentData():    

    global CurrentData
    print(CurrentData)
    return json.dumps(CurrentData) 


# Url for get current measure
@WebServer.route('/Data/Current', methods=['GET'])
def GetCurrentData():

    global CurrentData

    # Check Measure request args
    if 'Measure' in request.args:
        measure = request.args['Measure']
    else:
        return 404

    ReturnedString = ''

    if measure == 'Temperature':
        ReturnedString = str(CurrentData['Temperature'])
    elif measure == 'Humidity':
        ReturnedString = str(CurrentData['Humidity'])
    elif measure == 'Timestamp':
        ReturnedString = str(CurrentData['Timestamp'])
    elif measure == 'Date':
        ReturnedString = CurrentData['Date']
    elif measure == 'All':
        ReturnedString = json.dumps(CurrentData) 
    else:
        ReturnedString = '' 

    return ReturnedString



### Historical Data

# Url for get historical measure
@WebServer.route('/Data/Historical', methods=['GET'])
def GetHistoData():

    #URI: /Data/Historical?Measure=<value>&FirstDate=<value>&LastDate=<value>

    # Check Measures args
    if 'Measure' in request.args:
        measure = request.args['Measure']
        pass
    else:
        return 404

    # Check FirstDate args
    if 'FirstDate' in request.args:
        first_date = request.args['Measure']
        pass
    else:
        return 404

    # Check DateEnd args
    if 'LastDate' in request.args:
        last_date = request.args['Measure']
        pass
    else:
        return 404
    
    # Check first time args
    if 'FirstTime' in request.args:
        first_t = request.args['Measure']
        pass
    else:
        first_t = '00-00-00'
        return 404

    # Check last time args
    if 'LastTime' in request.args:
        last_t = request.args['Measure']
        pass
    else:
        last_t = '00-00-00'
        return 404


    ## Algorithm :

    # 1.Get a list of file of Google Drive that start with "Log_File_" and has .csv extension
    ListOfFilesInGoogleDrive = []

    # 2. Conversion init and end dates(in format 'dd-mm-yyyy hh-mm-ss') to timestamp format
    InitDateAsTimestamp = time.mktime(datetime.datetime.strptime(first_date + ' ' + first_t,'%d-%m-%Y %HH-%MM-%SS').timetuple())
    LastDateAsTimestamp = time.mktime(datetime.datetime.strptime(last_date + ' ' + last_t,'%d-%m-%Y %HH-%MM-%SS').timetuple())


    # Based on measure id return 
    if measure == 'All':
        return 'Not-Yet'
    elif measure == 'Temperature':
        return 'Not-Yet'
    elif measure == 'Humidity':
        return 'Not-Yet'
    else:
        return 404

    return 'ok'


# ---------------------  Other utilities   -------------------------- #


# Url for upload current data as csv format by IoT device
@WebServer.route('/CurrentData/<CSVObject>')
def UploadCurrentData(CSVObject):

    global CurrentData 

    # CSVObject: temp_value, hum_value, timestamp, date
    ListOfSplittedStrings = CSVObject.split(',')
    print(ListOfSplittedStrings)

    DateAsDatetime = datetime.datetime.fromtimestamp(float(ListOfSplittedStrings[2]))

    # Upload Current Data Variable   
    CurrentData['Temperature'] = float(ListOfSplittedStrings[0])
    CurrentData['Humidity'] = float(ListOfSplittedStrings[1])
    CurrentData['Timestamp'] = float(ListOfSplittedStrings[2])
    CurrentData['Date'] = DateAsDatetime.strftime("%d/%m/%Y, %H:%M:%S")

    return 'ok' 


# Url for download a log file by name (Some changes here)
@WebServer.route('/DownloadLogFile/<filename>')
def UploadFileToBrowser(filename):

    # Open File
    FileObject = open(os.path.join(DataPath,filename),'r')

    print(os.path.join(DataPath,filename))

    # Read it
    FileAsText = FileObject.read()

    return FileAsText


# Run tha server
if __name__ == '__main__':
    WebServer.run(host = '0.0.0.0', port=PORT, debug=True)


