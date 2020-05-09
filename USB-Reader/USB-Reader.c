
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


#define BAUDRATE 9600
#define COM '/dev/ttyACM0' // COM PORT FOR ARDUINO
#define DAY_STAMP 86400 // DAY IN SECONDS 



/* ----- Functions ---------- */


/* -------- Global variables ----- */

// Path to storage log files
const char Path_To_Storage_LogFiles[] = "/home/raspi-of-malum/Desktop/Log_Files/";

// Pre header of filename
const char Filename[] = "Raspi_Log_File_";

// Header
const char Header[] = "Temperature,Humidity,Timestamp,Date \n";

// time_stamp struct
time_t TimeStamp_0;


/* ----------- App ------------ */

int main(int argc, char *argv[]){
    
    // Some vars
    FILE * fp; // File Handling
    char Path[1024]; // Full Path of current log file
    time_t TimeStamp; // Timer 

    // Request timestamp 
    time(&TimeStamp_0);
   
    // Concat to filename to Path[]
    sprintf(Path, "%s%s%ld%s", Path_To_Storage_LogFiles, Filename, TimeStamp_0, ".csv");

    // Write header
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

    // Loop
    while(1){


        // Get curren time
        time(&TimeStamp);

        // Check last of a day
        if(((int)difftime(TimeStamp, TimeStamp_0)) > DAY_STAMP){

            // Update stamp marker
            TimeStamp_0 = TimeStamp;

            // Update Filename
            sprintf(Path, "%s%s%ld%s", Path_To_Storage_LogFiles, Filename, TimeStamp_0, ".csv");

            // Write header
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
        }

        // Something in COM ?
        // Read it 
        // Append to log file
        // Send to web via TCP/IP

    }

    return 0;
}