/***************** Example script for reading *****************
****************** a log files of weather station *************
****************** By Victor Malumbres ************************/

#include <LogFileReader.h>

// ****** Functions ******

// Get the lines of log file
int GetNumberOfLinesOfFile(char* Filename){

    // Local vars
    FILE *fp;
    int NumberOfLines = 0;
    char * Buffer;
    size_t len = 0;
    ssize_t read;

    // Open File
    fp = fopen(Filename, "r");

    // Read line by line, and count lines
    while ((read = getline(&Buffer, &len, fp)) != -1) {
       NumberOfLines ++;
    }

    // Close File
    fclose(fp); 


    return NumberOfLines;
}


int ConvertLineFromStringToStruct(){return 0;}
int CalculateAverageValues(){return 0;}
int CalculateStdValues(){return 0;}
int CalculateMedianValues(){return 0;}
int WriteStatisticFile(){return 0;}


/*
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
*/
