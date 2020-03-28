# Server script

from flask import Flask, render_template, url_for

import dash
import dash_core_components as dcc
import dash_html_components as html

import json
import os
import sys


#### Global Variables ####

# Current data 
CurrentDataAsString = '{"Timestamp":2,"Date":"21/03/2020","Temperature": 30, "Humidity": 55}'

# Data path (Change to 'home/pi/Desktop/LogFiles')
DataPath = r'C:\Users\Victor\Documents\GitHub\Weather_Station-\WebServer'

# Web server with Flask
WebServer = Flask(__name__)

# Dashboard Dash App
DashboardApp = dash.Dash(__name__, server=WebServer, routes_pathname_prefix='/Dashbord')

# Location Dash App
LocationApp = dash.Dash(__name__, server=WebServer, routes_pathname_prefix='/Dashbord')


# -------------------- WEB BACKEND ----------------- #

# Index page
@WebServer.route('/')
def index():

    # Get current measure
    global CurrentDataAsString

    try:

        # Convert to json
        CurrentDataAsJsonObject = json.loads(CurrentDataAsString)

        # Prepare string to show in web html
        DateString = CurrentDataAsJsonObject[Date]
        TemperatureString = 'Temperature : ' + str(CurrentDataAsJsonObject[Temperature]) + ' [ºC]'
        HumidityString = 'Humidity : ' + str(CurrentDataAsJsonObject[Humidity]) + ' [%]'

    except:
        DateString = '-- / -- / --'
        TemperatureString = 'Temperature : -- [ºC]'
        HumidityString = 'Humidity : -- [%]' 


    return render_template('index.html', date = DateString, temperature = TemperatureString, humidity = HumidityString)

# Download page
@WebServer.route('/Downloads')
def downloads():
    return 'Downloads (Not yet)'

# About page
@WebServer.route('/about.html')
def about():
    return render_template('about.html')


# --------------------- API -------------------------- # 


# Url for get current measure
@WebServer.route('/Data/<measure>')
def GetCurrentData(measure):
    ReturnedString = ''

    # As json object
    CurrentDataAsJson = json.load(CurrentDataAsString)

    if measure == 'Temperature':
        ReturnedString = str(CurrentDataAsJson['Temperature'])
    elif measure == 'Humidity':
        ReturnedString = str(CurrentDataAsJson['Humidity'])
    else:
        ReturnedString = '' 

    return ReturnedString




# ---------------------  Other utilities   -------------------------- #


# Url for upload current data as json by IoT device
@WebServer.route('/CurrentData/<JsonObject>')
def UploadCurrentData(JsonObject):

    global CurrentDataAsString 

    # Upload Current Data Variable   
    CurrentDataAsString = JsonObject

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
    WebServer.run(host = '0.0.0.0', port=80, debug=True)


