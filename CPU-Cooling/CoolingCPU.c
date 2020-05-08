/* Cooling machine in C*/

#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wiringPi.h>
#include <time.h>

#define MAX_SIZE 6

const float MAX_CPU_TEMP = 70.0;
const float PWM_SCALER = 1204.0;

/* ------- Functions ---------- */
int GetTemperatureFromCPU(float temp){

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
        
        // Cast string to float
        temp = atof(content);

    }else{
        printf("Error in cpu temperature request");
        return -1;
    }



    return 0;
}




/* -------- App ------------- */

int main(int argc, char **argv){

    // Local vars
    float cpu_temp;
    time_t * stamp;

    // Settings gpio as PWM
    pinMode(1,PWM_OUTPUT);

    while(1){

        // Read temperature from cpu
        int check = GetTemperatureFromCPU(cpu_temp);
        if(check == -1) { return -1;}

        // Get stamp
        time(stamp);

        // Calculate action (control P)
        float action = cpu_temp * (MAX_CPU_TEMP/PWM_SCALER);

        // Execute action as pwm
        pwmWrite(1,(int)action);

        //Show raspi statement
        printf(" -- RASPI COOLING STATEMENT -- \n ");
        printf("    --> %s   \n ", ctime(stamp));
        printf("    --> CPU Temp: %f [ºC] \n", cpu_temp);
        printf("    --> PWM Action: %d [10-bit] \n", (int)action);

        // Sleep for 2 seconds
        sleep(2);

    }
    
    return 0;
}