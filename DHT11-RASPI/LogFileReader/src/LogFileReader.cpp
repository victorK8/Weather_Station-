/***************** Example script for reading *****************
****************** a log files of weather station *************
****************** By Victor Malumbres ************************/

#include <LogFileReader.h>


// Types
 
// Struct for stastic values
typedef struct Statistics{
  double Average;
  double Deviation;
  double Median;
};

// Struct that represent a line of the file
typedef struct DataOfALine{
  double Temperature;
  double Humidity;
  char *Timestamp;
  char *Date;
};

// Vars
Statistics Temperature;
Statistics Humidity;
DataOfALine Line;



// **** Functions ******

// Get the lines of log file
int GetNumberOfLinesOfFile(char *Filename){

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

// Convert a csv format string to struct
int ConvertLineFromStringToStruct(char *line){

  // Local vars
  char *ParsedLine;
   
  // Get first element (Temperature) and put into struct
  ParsedLine = strtok(line,",");
  Line.Temperature = atof(ParsedLine);

  // Print struct
  printf("**** Data of line ****\n");
  printf("  Temperature: %lf \n", Line.Temperature);
  printf("  Humidity: %lf \n", Line.Humidity);
  printf("  TimeStamp: %s \n", Line.Timestamp);
  printf("  Date: %s \n", Line.Date);
  printf("**** End of line **** \n");

  return 0;
}


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
