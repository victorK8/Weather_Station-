
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

int WriteToLogFile(char *FilePath[], char *StringToAdd[], char mode){
    /* ----------------------
     *
     * FilePath is a string that points directory of filename
     * StringToAdd is a string that append to file
     * mode is "w" or "a" 
     * --------------------------
     */

    FILE *fp;

    // Open file
    fp = fopen(FilePath, &mode);

    // Write file
    if(fprintf(fp, StringToAdd) < 0) return -1;

    // Close file
    if(fclose(fp) != 0) return -1;

    return 0;
}

/* -------- Global variables ----- */

// Path to storage log files
char Path_To_Storage_LogFiles[] = "/home/raspi-of-malum/Desktop/Log_Files";

// Filename
char LogFilename[] = "Raspi_Log_File_";

// Extension
char Extension[] = ".csv";

// Header
char Header[] = "Temperature,Humidity,Timestamp,Date \n";

// time_stamp struct
time_t TimeStamp;
char  TimeStampAsSrt[] = "";


/* ----------- App ------------ */

int main(int argc, char *argv[]){

    // Request timestamp 
    time(&TimeStamp);
   
    // Convert timestamp in to string format

    // Concat filename
    strcat(&LogFilename, &TimeStampAsSrt);
    strcat(&LogFilename, &Extension);

    // Write header.
    if(WriteToLogFile(&LogFilename, &Header, "w")!= 0){
        // Log errror
        printf(" Error writing header ");
        // Go out
        exit(-1);
    }


    // loop
    while(1){

    }

    return 0;
}