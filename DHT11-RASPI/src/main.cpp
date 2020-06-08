/*********** Script for getting measures *******************
************ of temperature & humidity *********************
************ by using dht11 in raspberry pi 4 **************
************ By Víctor Malumbres ***************************/

#include <dht11.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

// Handling time
#include <time.h>

// Handling serial coms
#include <termios.h>
#include <fcntl.h>

// Handling sockets in c
#include <sys/socket.h>
#include <netdb.h> 
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 80
#define HOST_IP "127.0.0.1"

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
const char filename[] = "RaspiOfMalum_LogFile.csv";

// APP
int main(void){
    // Local vars
    time_t TimeStamp;
    char Message2SendToWeb[250];
    

    // Storage file handling
    char FullPathToFile[250];
    FILE *fp;
    
    // Full path to log file
    sprintf(FullPathToFile, "%s/%s",PATH_TO_EXT_DISK,filename);

    // Write Header
    fp = fopen(FullPathToFile,"w");
    fprintf(fp,"Temperature,Humidity,TimeStamp,Date \n");
    fclose(fp);

    // Create dht11 object
    dht11 SensorObj;

    // Set pin
    SensorObj.setPin(30);
	
    // Set-up obj sensor
    if(SensorObj.setup()<0){
      printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
      exit(-1);
    }

    while(1){

     // Get time
     time(&TimeStamp);

     // Take measure
     if(SensorObj.read_dht11_v2()==0){
      	// Print in console
     	printf("Date:%sTemperature: %f [ºC] Humidity: %f [PerCento] \n",ctime(&TimeStamp), SensorObj.getTemperature(), SensorObj.getHumidity());
        printf("\n");
        // Create message to send to webserver
        sprintf(Message2SendToWeb, "POST /CurrentData/%f,%f,%ld HTTP/1.1\r\nHost: %s\r\nContent-Type: text/plain\r\n\r\n", SensorObj.getTemperature(), SensorObj.getHumidity(), TimeStamp, HOST_IP);
	
        // Send to server
        if(SendMessageToWeb(Message2SendToWeb) < 0) {
		printf("Error handling socket");
 	}
	
        // Storage into file
        FILE *fp;

    	// Full path to log file
    	sprintf(FullPathToFile, "%s/%s",PATH_TO_EXT_DISK,filename);

    	// Write data
    	fp = fopen(FullPathToFile,"a");
    	fprintf(fp,"%f,%f,%ld,%s",SensorObj.getTemperature(), SensorObj.getHumidity(), TimeStamp, ctime(&TimeStamp));
	fclose(fp);

     }

     //Wait 5 seconds
     usleep(5000000);
	
    }
    return 0;
}
