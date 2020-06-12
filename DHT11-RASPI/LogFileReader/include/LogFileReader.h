/************ Library to parser log files  *******************
************* From Weather Station Project *******************
************* By Victor Malumbres Talles   ******************/

#ifndef LOGFILEREADER_H
#define LOGFILEREADER_H

// Include basic modules

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

// ****** Varaibles ******

// Path To Log File
char PathToLogFile[] = "/media/DISK_1TB/Log_Files/RaspiOfMalum-1591623748.csv";

// Struct for stastic value of temperature
struct TemperatureSts{
  double average;
  double deviation;
  double median;
}

// Struct for stastic value of humidity
struct HumiditySts{
  double average;
  double deviation;
  double median;
}


// Struct that represent a line of the file
struct Line{
  double temperature;
  double humidity;
  char *timestamp;
  char *date;
};



// ****** Functions ******
int GetNumberOfLinesOfFile();
int ConvertLineFromStringToStruct();
int CalculateAverageValues();
int CalculateStdValues();
int CalculateMedianValues();
int WriteStatisticFile();








#endif
