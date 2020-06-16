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
  double Maximum;
  double Minimum;
  long int Max_Time;
  long int Min_Time;
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
 
   // Loop for maximum, minumin and max_time, min_time
   // Init max and min values
   Temperature.Maximum = 0.0;
   Humidity.Maximum = 0.0;
   Temperature.Minimum = 1000.0;
   Humidity.Minimum = 1000.0;

   while ((read = getline(&Buffer, &len, fp)) != -1) {
      // Convert to struct line
      if(ConvertLineFromStringToStruct(Buffer) != 0 ) return -1;
    
      // For temperature
      if(Line.Temperature > Temperature.Maximum){
        Temperature.Maximum = Line.Temperature;
        Temperature.Max_Time = Line.Timestamp;	
      }
      if(Line.Temperature < Temperature.Minimum){
        Temperature.Minimum = Line.Temperature;
        Temperature.Min_Time = Line.Timestamp;
      }

      // For humidity
      if(Line.Humidity > Humidity.Maximum){
        Humidity.Maximum = Line.Humidity;
        Humidity.Max_Time = Line.Timestamp;
      }
      if(Line.Humidity < Humidity.Minimum){
        Humidity.Minimum = Line.Humidity;
        Humidity.Min_Time = Line.Timestamp;
      }
 
   }
   // Loop for median calculation
   // Need to implement   
 
   // Close Log File
   fclose(fp);

   // Print (Uncomment for debug)
   printf("**** Statistics **** \n");
   printf("Average of Temperature: %lf \n", Temperature.Average);
   printf("Average of Humidity: %lf \n", Humidity.Average);
   printf("Deviation of Temperature: %lf \n", Temperature.Deviation);
   printf("Deviation of Humidity: %lf \n", Humidity.Deviation);
   printf("Median of Temperature: %lf \n", Temperature.Median);
   printf("Median of Humidity: %lf \n", Humidity.Median);
   printf("Max. of Temperature: %lf at %ld stamp \n", Temperature.Maximum, Temperature.Max_Time);
   printf("Max. of Humidity: %lf at %ld stamp \n", Humidity.Maximum, Humidity.Max_Time);
   printf("Min. of Temperature: %lf at %ld stamp \n", Temperature.Minimum, Temperature.Min_Time);
   printf("Min. of Humidity: %lf at %ld stamp \n", Humidity.Minimum, Humidity.Min_Time);
   printf("**** End **** \n");


   // Filename handling Local vars
   // NewFilename is like "....../RaspiOfMalum_[Timestamp]_Analysis.csv"
   char NewFilename[120];
   char OnlyNewName[50];
   const char PathToDisk[] = "/media/DISK_1TB/Statistics_Files/";

   // Log (Uncomment for debug)
   //printf("\n");
   //printf("Old Path: %s \n", Filename);
  
   // Generate new name for file
   sprintf(OnlyNewName, "RaspiofMalum_Analytics_%ld.json",Line.Timestamp); 
  
   // Generate all path to file
   // Copy path to disk
   strcpy(NewFilename,PathToDisk);
   // Add Name and Extension
   strcat(NewFilename,OnlyNewName);

   // Log (Uncomment for debug)
   //printf("\n"); 
   //printf("New Path: %s \n", NewFilename);

   FILE *fp2;

   // Open analysis file
   fp2 = fopen(NewFilename, "w");

   // Write statistics as json
   fprintf(fp2, "{\"LineTimestamp\":%ld, \"Temperature\":{\"Average\": %lf, \"Deviation\": %lf, \"Max\": %lf, \"MaxStamp\": %ld, \"Min\": %lf, \"MinStamp\": %ld, \"Median\": %lf}, \"Humidity\":{\"Average\": %lf, \"Deviation\": %lf, \"Max\": %lf, \"MaxStamp\": %ld, \"Min\": %lf, \"MinStamp\": %ld,\"Median\": %lf}}", Line.Timestamp, Temperature.Average, Temperature.Deviation,Temperature.Maximum,Temperature.Max_Time,Temperature.Minimum,Temperature.Min_Time, Temperature.Median, Humidity.Average, Humidity.Deviation, Humidity.Maximum, Humidity.Max_Time, Humidity.Minimum, Humidity.Min_Time, Humidity.Deviation);
   
   // Close analysis file
   fclose(fp2);
 
   return 0;
}
