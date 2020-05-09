
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
char Path_To_Storage_LogFiles[] = "/home/raspi-of-malum/Desktop/Log_Files/Raspi_Log_File_";

// Header
char Header[] = "Temperature,Humidity,Timestamp,Date \n";

// Ext.
char Ext[] = ".csv";

// time_stamp struct
time_t TimeStamp;
char TimeStampAsSrt[] = "";


/* ----------- App ------------ */

int main(int argc, char *argv[]){

    // Request timestamp 
    time(&TimeStamp);
   
    // Convert timestamp in to string format

    // Concat to filename all strings 
    char *Filename = Path_To_Storage_LogFiles;
    strcat(Filename, &TimeStampAsSrt);
    strcat(Filename, &Ext);

    // Write header.
    FILE *fp;
    const char mode = 'w';

    // Open file
    fp = fopen(Filename, &mode);

    // Write file
    if(fprintf(fp, &Header) < 0){
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