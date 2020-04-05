# Weather Station Project

## Project Brief (Project's State in progress, not finished yet)

This Github repository storages software for Weather Station Project.

The Station platform is based in open-hardware. Boards like Arduino Uno (Atmel Processor (8-bit CPU)) and 
Raspberri Pi Model 4 (Broadcom BCM2711, Quad core Cortex-A72 (ARM v8) 64-bit SoC @ 1.5GHz).

The main goal of project is making a Weather Station based on Arduino Uno with ambient sensors such as temperature, humidity (another magnitudes in progress). In order to add the project acces to Internet (World), Raspberry Pi is used as Gateway. The idea is creating two individual modules that together, can increase their services.

Arduino Board and Raspberry are connected via USB. Check the next pic.


<img src="https://comohacer.eu/wp-content/uploads/2013/10/raspberry-pi+arduino.jpg"
     alt="Connections"
     style="float: left; margin-right: 10px;" />


Ambient Sensors and Arduino Uno connections are in progress 

## Software

**wetherino.ino** is Weather Station Firmware for Arduino Uno in C++ (Only communications via Usb with Raspi, not sensor added because it's in progress).

**USB_Reader.py** is low-level software of Raspberry Pi. Get the arrived data (json format) from Arduino Board via Usb and parse data in order to storage data in Raspberry as CSV Format. Also, it does calls to high-level (WebServer) in order to share arrived data as csv format too (Finished).

**WebServer** contains software of high-level software of Raspberri Pi. Web-Server is based on Flask Module as backend in Python (check server.py script). As front-end, basic Html,CSS and Javascript script are used (Check template folder). Web-Server provides the services of data visualization, weather station geolocation, music (only for entertainment purposes). Its state is in progress (Geo-Location is finished).


## How do I use your code, bro?

The first step is downloading my repository into your Raspberry Pi.

``` git clone https://github.com/victorK8/Weather_Station-.git ```

You need to boot Weatherino.ino in Arduino Uno board (use Arduino Uno IDE). After that, Station is fine.

For Raspberry Pi, you can run WebServer and USB_Reader, one by one, in same or different linux terminal. Using the next commands (Remember that you need to be in file directory path in command line terminal).

``` sudo python3 USB_Reader.py ``` for launch low-level softare.

``` sudo python3 server.py ``` for launch web-server.

Previously, you need to install some Python modules via ``` sudo pip3 install [Package-Module Name] ```  .

Modules like *flask*, *pyserial* .

A linux script (*.sh* file) is in progress, in order to launch of Raspberry Pi software.



