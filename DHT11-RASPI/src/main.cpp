/*********** Script for getting measures *******************
************ of temperature & humidity *********************
************ by using dht11 in raspberry pi 4 **************
************ By Victor Malumbres ***************************/

// Basic libraries
#include <dht11.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

// Handling time
#include <time.h>

// Handling sockets in c
#include <sys/socket.h>
#include <netdb.h> 
#include <netinet/in.h>
#include <arpa/inet.h>

// For handlings log file and statistics
#include <LogFileReader.h>

// Web Servers Host Settings
#define PORT 80
#define HOST_IP "127.0.0.1"

// Day in seconds
#define DAY_IN_SECONDS 86400

/****** Functions ******/

// Send data to web via tcp/ip socket
int SendMessageToWeb(char *MessageAsStr){

    int SocketStatus; // fp for socket status
    int ComStatus; // fp for connection status with host
    int MsgStatus; // fp for sended message status
    struct sockaddr_in host_settings; // Info. About host server

    // Host settings
    host_settings.sin_family = AF_INET;
    host_settings.sin_port = htons(PORT);
    host_settings.sin_addr.s_addr = inet_addr(HOST_IP);

    // Create TCP/IP socket, checking possible errors
    if((SocketStatus = socket(AF_INET, SOCK_STREAM, 0))<0){
        printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
        return -1;
    }

    // Connect to host
    if((ComStatus = connect(SocketStatus,(struct sockaddr *)&host_settings,sizeof(host_settings)))<0){
        printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
        return -1;
    }

    // Send Message to host
    if((MsgStatus=send(SocketStatus,MessageAsStr,strlen(MessageAsStr),0))<0){
        printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
        return -1;
    }
    // Close socket
    close(SocketStatus);

    return 0;
}


/****** Consts and global variables ******/

// Path to different external storage device
const char PATH_TO_EXT_DISK[] = "/media/DISK_1TB/Log_Files";
const char PATH_TO_EXT_USB[] = "/media/USB_16GB/Log_Files";
const char filename[] = "RaspiOfMalum";

// APP
int main(void){

    // Local vars
    time_t TimeStamp0;
    time_t TimeStamp;
    char Message2SendToWeb[250];

    // Get timestamps
    time(&TimeStamp);
    time(&TimeStamp0);
    
    // Storage file handling
    char FullPathToFile[250];
    FILE *fp;
    
    // Full path to log file
    sprintf(FullPathToFile, "%s/%s-%ld.csv",PATH_TO_EXT_DISK,filename,TimeStamp);

    // Write Header
    fp = fopen(FullPathToFile,"w");
    fprintf(fp,"Temperature,Humidity,TimeStamp,Date \n");
    fclose(fp);

    // Create dht11 sensor object
    dht11 SensorObj;

    // Set pin where sensor is connected
    SensorObj.setPin(30);
	
    // Set-up obj sensor
    if(SensorObj.setup()<0){
      printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
      exit(-1);
    }

    while(1){

     // Get time
     time(&TimeStamp);

     // Check if a day have been passed
     if(difftime(TimeStamp,TimeStamp0) >= DAY_IN_SECONDS){

	// Calculate statistics files
        if(WriteStatisticFile(FullPathToFile)!=0) return -1;

        // Update the path to a new log-file
	sprintf(FullPathToFile, "%s/%s_%ld.csv",PATH_TO_EXT_DISK,filename,TimeStamp);
	
	// Create the new log-file and write the header
    	FILE *fp;
		
    	// Write Header
    	fp = fopen(FullPathToFile,"w");
    	fprintf(fp,"Temperature,Humidity,TimeStamp,Date \n");
        fclose(fp);

	// Update timestamp marker
        time(&TimeStamp0);
 
     }

     // Take measure of temperature and humidity
     if(SensorObj.read_dht11_v2()==0){

      	// Create message to send to web-server
        sprintf(Message2SendToWeb, "POST /CurrentData/%f,%f,%ld HTTP/1.1\r\nHost: %s\r\nContent-Type: text/plain\r\n\r\n", SensorObj.getTemperature(), SensorObj.getHumidity(), TimeStamp, HOST_IP);
	
        // POST message to web-server
        if(SendMessageToWeb(Message2SendToWeb) < 0){printf("Error handling socket");}
	
        // Storage measure into log-file
        FILE *fp;
    	fp = fopen(FullPathToFile,"a");
    	fprintf(fp,"%f,%f,%ld,%s",SensorObj.getTemperature(), SensorObj.getHumidity(), TimeStamp, ctime(&TimeStamp));
	fclose(fp);

	// Log measure in console
	printf("Date:%sTemperature: %f [C] Humidity: %f [%s] \n",ctime(&TimeStamp), SensorObj.getTemperature(), SensorObj.getHumidity(), "%");
        printf("\n");
     }

     //Wait 5 seconds
     usleep(5000000);
	
    }
    return 0;
}
