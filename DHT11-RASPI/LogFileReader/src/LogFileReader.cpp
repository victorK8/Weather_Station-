/***************** Example script for reading *****************
****************** a log files of weather station *************
****************** By Victor Malumbres ************************/


#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

// ******** Variables ********

// Struct for reading rows of log_file
struct Row{
  double temperature;
  double humidity;
  char *timestamp;
  char *date;
};

// Path to a Log_File example
const char LogFileExample[] = "/media/DISK_1TB/Log_Files/RaspiOfMalum-1591623748.csv";
// ********* Functions ********


// ******** App **************

int main(void){
  	
    // Open file in reading mode
    FILE * fp;
    fp = fopen(LogFileExample,"r");
 
    // Local vars for reading file line by line
    char * Buffer;
    size_t len = 0;
    ssize_t read;
    char * SplittedBuffer;
	
    // Read line by line
    //while ((read = getline(&Buffer, &len, fp)) != -1) {
        read = getline(&Buffer, &len, fp);
        read = getline(&Buffer, &len, fp);
	SplittedBuffer = strtok(Buffer,",");
	printf(SplittedBuffer);
    //}

    // Close file
    fclose(fp);


    return 0;

}
