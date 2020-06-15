/***************** Example script for reading *****************
****************** a log files of weather station *************
****************** By Victor Malumbres ************************/


#include <LogFileReader.h>

// ******** Variables ********

// Path to a Log_File example
char LogFileExample[] = "/media/DISK_1TB/Log_Files/RaspiOfMalum-1591623748.csv";

// ******** App **************

int main(void){

   // Print number of lines of file
   int NumberOfLines = GetNumberOfLinesOfFile(LogFileExample);
   printf("%d lines in file \n ", NumberOfLines);

   return 0;
}
