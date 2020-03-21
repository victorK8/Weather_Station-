# Server script

from flask import Flask, render_template, url_for

import json
import os
import sys

# const
GoogleAPIKey = 'AIzaSyChnxLzQNUy52aO4hcj387y6aa895nWB3E'


# Global Variables
CurrentDataAsString = '{"Timestamp":2,"Date":"21/03/2020","Temperature": 30, "Humidity": 55}'

app = Flask(__name__)

# Data path (Change to 'home/pi/Desktop/LogFiles')
DataPath = r'C:\Users\Victor\Documents\GitHub\Weather_Station-\WebServer'

# -------------------- WEB BACKEND ----------------- #

# Index page
@app.route('/')
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

# Dashboard page
@app.route('/dashboard.html')
def dashboard():
    return render_template('dashboard.html')

# Download page
@app.route('/Downloads')
def downloads():
    return 'Downloads (Not yet)'

# About page
@app.route('/about.html')
def about():
    return render_template('about.html')

# Location page
@app.route('/location.html')
def location():
    return render_template('location.html')


# --------------------- API -------------------------- # 


# Url for get current measure
@app.route('/Data/<measure>')
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
@app.route('/CurrentData/<JsonObject>')
def UploadCurrentData(JsonObject):

    global CurrentDataAsString 

    # Upload Current Data Variable   
    CurrentDataAsString = JsonObject

    return 'ok' 


# Url for download a log file by name
@app.route('/DownloadLogFile/<filename>')
def UploadFileToBrowser(filename):

    # Open File
    FileObject = open(os.path.join(DataPath,filename),'r')

    print(os.path.join(DataPath,filename))

    # Read it
    FileAsText = FileObject.read()

    return FileAsText


# Run tha server
if __name__ == '__main__':
    app.run(host = '0.0.0.0', port=80, debug=True)


