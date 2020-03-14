# Server script

from flask import Flask, render_template, url_for

import os
import sys

app = Flask(__name__)

# Data path (Change to 'home/pi/Desktop/LogFiles')
DataPath = r'C:\Users\Victor\Documents\GitHub\Weather_Station-\WebServer'


# -------------------- Functions for principal HTML pages ----------------- #

# Index page
@app.route('/')
def index():
    return render_template('index.html')

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

# Put in browser as string a local file
@app.route('/Data/<filename>')
def UploaData(filename):

    # Open File
    FileObject = open(os.path.join(DataPath,filename),'r')

    print(os.path.join(DataPath,filename))

    # Read it
    FileAsText = FileObject.read()

    return FileAsText


if __name__ == '__main__':
    app.run(host = '0.0.0.0', port=80, debug=True)


