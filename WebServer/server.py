# Server script

from flask import Flask, render_template, url_for

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
DataPath = r'C:\Users\Victor\Documents\GitHub\Weather_Station-\WebServer'

# Web server with Flask
WebServer = Flask(__name__)

##### Dashboard Dash App & Layout #####
DashboardApp = dash.Dash(__name__, server=WebServer, routes_pathname_prefix='/Dashboard/')

# Change page title
DashboardApp.title = " Weather Station "

# Current week data as json
CurrentWeekData = {'data':[
    {'x':[0,1,2,3,4,5,6],'y':[23,23,23,23.5,24,24],'type':'line','name':'Temp. [ºC]'},
    {'x':[0,1,2,3,4,5,6],'y':[46,46,46,46,46,46.5,47],'type':'line','name':'Hum. [%]'}]
    ,'layout':{'title': ' DataViz'}}

#Layout
DashboardApp.layout = html.Div(children=[
    #Tabs
    dcc.Tabs(
        id = 'tabs',
        children = [

            # Tab for week's data
            dcc.Tab(id='tab-1', label='DATAVIZ', children=[
                # Chart 
                dcc.Graph(
                    id = "DatavizChart",
                    figure = CurrentWeekData
                )
            ]),

            # Tab for hystorical data
            dcc.Tab(id='tab-2', label='HISTORICAL', children=[
                dcc.Graph(id="HistoChart")
            ]),

            # Tab for statistics
            dcc.Tab(id='tab-3', label='STATISTICS', children=[
                dcc.Graph(id="StatChart")
            ]),

    ], className = 'row')

], className = 'row')

##### Location Dash App #####
LocationApp = dash.Dash(__name__, server=WebServer, routes_pathname_prefix='/Location/')

# Change page title
LocationApp.title = " Weather Station "

# MapFig
import plotly.express as px

df = px.data.gapminder().query("year==2007")
fig = px.scatter_geo(df, locations="iso_alpha", color="continent",
                     hover_name="country", size="pop",
                     projection="natural earth")

# Layout
LocationApp.layout = html.Div(children=[
    dcc.Graph(
        id="map",
        figure = fig
    )
], className = 'row')



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
@WebServer.route('/Downloads')
def downloads():
    return 'Downloads (Not yet)'

# About page
@WebServer.route('/about.html')
def about():
    return render_template('about.html')

# Music page
@WebServer.route('/music.html')
def music():
       return render_template('music.html')

# --------------------- API -------------------------- # 


# Url for get current measure
@WebServer.route('/Data/<measure>')
def GetCurrentData(measure):
    ReturnedString = ''

    global CurrentData

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
    WebServer.run(host = '0.0.0.0', port=80, debug=True)


