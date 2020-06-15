/***************** Example script for reading *****************
****************** a log files of weather station *************
****************** By Victor Malumbres ************************/

#include <LogFileReader.h>
#define MAX_SIZE 100

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
  long int Timestamp;
  char Date[MAX_SIZE];
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
  int ItemCounter = 0;
  const int NumberOfItems = 4;

  // Get first element (Temperature) and put into struct
  ParsedLine = strtok(line,",");
  Line.Temperature = atof(ParsedLine);
  ItemCounter ++;
  
  // Loop for the rest of items
  while(ItemCounter<NumberOfItems){
     // Get Item
     ParsedLine = strtok(NULL,",");
   
     // Put value of specific item
     if(ItemCounter == 1){
     	Line.Humidity = atof(ParsedLine);
     }else if(ItemCounter == 2){
        Line.Timestamp = atol(ParsedLine);
     }else if(ItemCounter == 3){
        strcpy(Line.Date, ParsedLine);
     }

     // increment counter of items
     ItemCounter ++;
  }

  // Print struct (uncomment for debug)
  printf("**** Data of line ****\n");
  printf("Temperature: %lf \n", Line.Temperature);
  printf("Humidity: %lf \n", Line.Humidity);
  printf("TimeStamp: %ld \n", Line.Timestamp);
  printf("Date: %s \n", Line.Date);
  printf("**** End of line **** \n");

  return 0;
}


int CalculateAverageValues(){return 0;}
int CalculateStdValues(){return 0;}
int CalculateMedianValues(){return 0;}
int WriteStatisticFile(){return 0;}
