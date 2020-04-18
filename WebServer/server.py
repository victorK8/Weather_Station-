# Server script

from flask import Flask, render_template, request, jsonify

import dash
import dash_core_components as dcc
import dash_html_components as html
import plotly.graph_objects as go

import json
import os
import sys
import datetime


#### Global Variables ####

# Current data 
CurrentData = {"Timestamp":2,"Date":"21/03/2020","Temperature": 30, "Humidity": 55}

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

    global CurrentData

    # Check Measure request args
    if 'Measure' in request.args:
        measure = request.args['Measure']
    else:
        return 404

    ## Introduce code after here ##


    return 'Not-Yet-'


# ---------------------  Other utilities   -------------------------- #


# Url for upload current data as csv format by IoT device
@WebServer.route('/CurrentData/<CSVObject>')
def UploadCurrentData(CSVObject):

    global CurrentData 

    # CSVObject: temp_value, hum_value, timestamp, date
    ListOfSplittedStrings = CSVObject.split(',')
    print(ListOfSplittedStrings)

    # Upload Current Data Variable   
    CurrentData['Temperature'] = float(ListOfSplittedStrings[0])
    CurrentData['Humidity'] = float(ListOfSplittedStrings[1])
    CurrentData['Timestamp'] = float(ListOfSplittedStrings[2])
    CurrentData['Date'] = datetime.datetime.fromtimestamp(float(ListOfSplittedStrings[2]))

    return 'ok' 


# Url for download a log file by name
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
    WebServer.run(host = '0.0.0.0', port=8888, debug=True)


