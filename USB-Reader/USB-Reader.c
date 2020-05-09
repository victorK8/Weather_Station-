
// For general purpose, handling files
#include <float.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

// Handling time
#include <time.h>

// Handling serial coms
#include <termios.h>
#include <fcntl.h>

// Handling sockets in c
#include <sys/socket.h>

// Handling errors
#include <errno.h>


#define BAUD_RATE 9600
#define COM '/dev/ttyACM0'



/* ----- Functions ---------- */


/* -------- Global variables ----- */

// Path to storage log files
const char Path_To_Storage_LogFiles[] = "/home/raspi-of-malum/Desktop/Log_Files/";

// Pre header of filename
const char Filename[] = "Raspi_Log_File_";

// Header
const char Header[] = "Temperature,Humidity,Timestamp,Date \n";

// Ext.
const char Ext[] = ".csv";

// time_stamp struct
time_t TimeStamp;



/* ----------- App ------------ */

int main(int argc, char *argv[]){

    // Request timestamp 
    time(&TimeStamp);
   

    // Concat to filename to Path[]
    char Path[1024];
    sprintf(Path, "%s%s%ld%s", Path_To_Storage_LogFiles,Filename,TimeStamp,Ext);

    // Write header.
    FILE *fp;

    // Open file
    fp = fopen(Path, "w");

    // Write file
    if(fprintf(fp, Header) < 0){
        printf("Error writing in Log-File");
        exit(-1);
    }

    // Close file
    if(fclose(fp) != 0) {
        printf("Error closing in Log-File");
        exit(-1);
    }

    // loop
    while(1){

    }

    return 0;
}