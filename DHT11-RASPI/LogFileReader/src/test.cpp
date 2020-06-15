/***************** Example script for reading *****************
****************** a log files of weather station *************
****************** By Victor Malumbres ************************/


#include <LogFileReader.h>

// ******** Variables ********

// Path to a Log_File example
char LogFileExample[] = "/media/DISK_1TB/Log_Files/RaspiOfMalum_1591623748.csv";

// String as csv format to test library
char ExampleLine[] = "24.000000,44.000000,1591623751,Mon Jun  8 15:42:31 2020";

// ******** App **************

int main(void){

   // Check number of lines of file. Print number of lines of file
   int NumberOfLines = GetNumberOfLinesOfFile(LogFileExample);
   printf("%d lines in file \n ", NumberOfLines);

   printf(" \n");
   printf(" \n");

   // Check parser of csv line. Print struct Line
   int ResultFlag = ConvertLineFromStringToStruct(ExampleLine);

   printf(" \n");
   printf(" \n");

   // Create statistics file
   int ResultFlag_2 = WriteStatisticFile(LogFileExample);


   return 0;
}
