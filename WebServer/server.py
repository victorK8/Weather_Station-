# Server script

from flask import Flask, render_template, url_for

import json
import os
import sys

# Global Variables
CurrentDataAsString = '{"Timestamp":2,"Date":"21/03/2020","Temperature": 30, "Humidity": 55}'

app = Flask(__name__)

# Data path (Change to 'home/pi/Desktop/LogFiles')
DataPath = r'C:\Users\Victor\Documents\GitHub\Weather_Station-\WebServer'

# -------------------- Functions for  HTML pages ----------------- #

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

# --------------------- Functions for another utilities  -------------------------- # 

# Upload current data as json format
@app.route('/CurrentData/<JsonObject>')
def UploadCurrentData(JsonObject):

    global CurrentDataAsString 

    # Upload Current Data Variable   
    CurrentDataAsString = JsonObject

    return JsonObject 


# Put in browser as string a local file
@app.route('/Data/<filename>')
def UploadFileToBrowser(filename):

    # Open File
    FileObject = open(os.path.join(DataPath,filename),'r')

    print(os.path.join(DataPath,filename))

    # Read it
    FileAsText = FileObject.read()

    return FileAsText


if __name__ == '__main__':
    app.run(host = '0.0.0.0', port=80, debug=True)


