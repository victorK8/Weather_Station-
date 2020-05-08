/* Cooling machine in C*/

#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_SIZE 20

/* ------- Functions ---------- */
/* ------- Variables ---------- */

int main(int argc, char **argv){

    /* -----  Read the return of a command line ------ */

    // FILE object to read
    FILE * fp; 

    // Command line to run
    const char cmd[] = "sensors";  
    //const chart cmd[] = "vcgencmd measure_temp";

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
        if(content != NULL) printf("File is : %s .\n", content);

    }else{
        printf("Error in cpu temperature request");
        return -1;
    }



    
    return 0;
}