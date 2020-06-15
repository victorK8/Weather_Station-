/***************** Example script for reading *****************
****************** a log files of weather station *************
****************** By Victor Malumbres ************************/

#include <LogFileReader.h>
#define MAX_SIZE 100
#define MAX_SIZE_FOR_PATH 500
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
  //printf("**** Data of line ****\n");
  //printf("Temperature: %lf \n", Line.Temperature);
  //printf("Humidity: %lf \n", Line.Humidity);
  //printf("TimeStamp: %ld \n", Line.Timestamp);
  //printf("Date: %s \n", Line.Date);
  //printf("**** End of line **** \n");

  return 0;
}

// Create a statistic file with average, deviation and median per file
int WriteStatisticFile(char *Filename){

   // Filename handling Local vars
   // NewFilename is like "....../RaspiOfMalum_[Timestamp]_Analysis.csv"  
   char ExtensionOfLogFile[] = ".csv";
   char *NewFilename = strtok(Filename,ExtensionOfLogFile);
   strcat(NewFilename, "_Analysis.json");
   

   // Read Line by line
   FILE *fp;
   char * Buffer;
   size_t len = 0;   
   ssize_t read;

   int NumberOfLines = 0;

   // Open Log File
   fp = fopen(Filename, "r");


   // Loop for average calculation
   // Read line by line. Counting lines and accumulating value for avg and deviation
   while ((read = getline(&Buffer, &len, fp)) != -1) {

      // Convert to struct line
      if(ConvertLineFromStringToStruct(Buffer) != 0 ){return -1;}
 
      // Increment statistics for temperature
      Temperature.Average += Line.Temperature;

      // Increment statistics for humidity
      Humidity.Average += Line.Humidity;
      
      // Increment counter of lines
      NumberOfLines ++;
   }

   // Divide average values by number of lines counter
   Temperature.Average = Temperature.Average/NumberOfLines;
   Humidity.Average = Humidity.Average/NumberOfLines;

   // Loop for deviation calculation
   // Read line by line. Counting lines and accumulating value for avg and deviation
   while ((read = getline(&Buffer, &len, fp)) != -1) {

      // Convert to struct line
      if(ConvertLineFromStringToStruct(Buffer) != 0 ){return -1;}

      // Increment statistics for temperature
      Temperature.Deviation += (Line.Temperature - Temperature.Average)*(Line.Temperature - Temperature.Average);

      // Increment statistics for humidity
      Humidity.Deviation += (Line.Humidity - Humidity.Average)*(Line.Humidity - Humidity.Average);

   }

   // Divide average values by number of lines counter
   Temperature.Deviation = sqrt(Temperature.Deviation/(NumberOfLines-1));
   Humidity.Deviation = sqrt(Humidity.Deviation/(NumberOfLines-1));

   // Print (Uncomment for debug)
   printf("**** Statistics **** \n");
   printf("Average of Temperature: %lf \n", Temperature.Average);
   printf("Average of Humidity: %lf \n", Humidity.Average);
   printf("Deviation of Temperature: %lf \n", Temperature.Deviation);
   printf("Deviation of Humidity: %lf \n", Humidity.Deviation);
   printf("**** End **** \n");

   // Close Log File
   fclose(fp);

   // Open analysis file
   fp = fopen(NewFilename, "r");

   // Write statistics as json
   fwrite(fp, "{\"Temperature\":{\"Average\": %lf, \"Deviation\": %lf, \"Median\": 0.00}, \"Humidity\":{\"Average\": %lf, \"Deviation\": %lf, \"Median\": 0.00}}", Temperature.Average, Temperature.Deviation, Humidity.Average, Humidity.Deviation);
   
   // Close analysis file
   fclose(fp);
 
   return 0;
}
