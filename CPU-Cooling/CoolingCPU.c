/* Cooling machine in C*/

#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_SIZE 20

/* ------- Functions ---------- */
int GetTemperatureFromCPU(float temp){

    /* ----- 1. Read the return of a command line ------ */

    // FILE object to read
    FILE * fp; 

    // Command line to run
    const char cmd[] = "vcgencmd measure_temp | egrep -o '[0-9]*\\.[0-9]*'";

    // Apply command and get the return into fp
    fp = popen(cmd, "r"); 
    
    // Read fp
    if(fp != NULL){

        // Read
        char content[MAX_SIZE];
        fgets(content,MAX_SIZE,fp);

        // Close fp
        pclose(fp);

        // Show content
        if(content != NULL) printf("CPU Temp: %s [ºC]  .\n", content);

    }else{
        printf("Error in cpu temperature request");
        return -1;
    }

    /* ---- 2. Cast content from string to float */
    temp = 50.0;

    return 0;
}




/* -------- App ------------- */

int main(int argc, char **argv){

    // Local vars
    float cpu_temp;

    while(1){

        // Read temperature from cpu
        int check = GetTemperatureFromCPU(cpu_temp);
        if(check == -1) { return -1;}

        // Calculate and apply cooling action as PWM signal

        // Sleep for 2 seconds
        sleep(2);

    }
    
    return 0;
}