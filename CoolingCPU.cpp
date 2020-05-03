/* Cooling CPU c++ script */

#include <wiringPi.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <string.h>

include namespace std;

#define K 50

// Get Temperature
float get_cpu_temp(){

    std::string rlst;
    
    std::string get_temp_command = "vcgencmd measure_temp | egrep -o '[0-9]*\.[0-9]*'";

    FILE * stream;
    const int max_buffer = 256;
    char buffer[max_buffer];
    get_temp_command.append(" 2>&1");

    stream = popen(get_temp_command.c_str(), "r");
    if (stream) {
      while (!feof(stream))
        if (fgets(buffer, max_buffer, stream) != NULL) rlst.append(buffer);
          pclose(stream);
      }

    // Print temp
    std::string msg_to_print = "CPU Temp (ºC): " + rlst;
    std::cout << msg_to_print;

    // return as float
    return std::atof(rlst.c_str());
}


// Source Code 
int main (int main(int argc, char *argv[])){

    // Take pin where ventilator is located. Via arguments program
    int PWM_PIN = 0;

    if (argc < 2 ) {
        // If args.size < 2, exit(-1). user
        // don't put pwm pin
        exit(-1);

    }else {
        // Cast second arg to int (Pin)
        PWM_PIN = (int) argv[1];
    }

    // Set pin as pwm mode
    pinMode (PWM_PIN, PWM_OUTPUT) ; /* set PWM pin as output */

    // Inf. Loop 
    while(true){

        // Get cpu temp
        float cpu_temp = get_cpu_temp();


        // Apply action functions
        float action = cpu_temp*K;

        // Overflow to 1024 (MÁX.)
        if(action > 1024.0) action=1024;

        // Apply pwm
        pwmWrite(PWM_PIN, (int) action);

        // delay of 1 second
        usleep(1000000);

    }



}
