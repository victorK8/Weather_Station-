
// For general purpose, handling files
#include <float.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

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

// Handling errors
#include <errno.h>

// Handling json files 
#include <json-c/json.h>



#define DAY_STAMP 86400 // DAY IN SECONDS 
#define PORT 80
#define HOST_IP "127.0.0.1"



/* ----- Functions ---------- */

//Storage file into external disk (1TB)
int StorageFileIntoExtDisk(char *PathToFileToStorage){
 
  // Local Vars
  char cmd2execure[50]; 
  FILE * fp;



	



   return 0;
}

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



/* --------  Structs ------ */
struct json_object *ParsedMessage;
struct json_object *Temperature;
struct json_object *Humidity;

/* -------- Global variables ----- */

// Path to storage log files
const char Path_To_Storage_LogFiles[] = "/home/raspi-of-malum/Desktop/Log_Files/";

// Pre header of filename
const char Filename[] = "Raspi_Log_File_";

// Header
const char Header[] = "Temperature,Humidity,Timestamp,Date \n";

// time_stamp struct
time_t TimeStamp_0;


/* ----------- App ------------ */

int main(int argc, char *argv[]){
    
    // Some vars
    FILE * fp; // File Handling
    char Path[1024]; // Full Path of current log file
    time_t TimeStamp; // Timer 
    char Message2SendToWeb[100];
    char Message2Storage[100];

    // Request timestamp 
    time(&TimeStamp_0);
   
    // Concat to filename to Path[]
    sprintf(Path, "%s%s%ld%s", Path_To_Storage_LogFiles, Filename, TimeStamp_0, ".csv");

    // Open file
    fp = fopen(Path, "w");

    // Write file
    if(fprintf(fp, Header) < 0){
        printf("Error writing in Log-File \n");
        exit(-1);
    }

    // Close file
    if(fclose(fp) != 0) {
        printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
        exit(-1);
    }

    // Open Serial COM
    int bus = open("/dev/ttyACM0", O_RDWR);

    // Check errors 
    if (bus < 0) {
        printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
        exit(-1);
    }

    // Config PORT (A lot of stuff here)
    // Create new termios struc, we call it 'tty' for convention
    struct termios tty;
    memset(&tty, 0, sizeof tty);

    // Read in existing settings, and handle any error
    if(tcgetattr(bus, &tty) != 0) {
        printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
        exit(-1);
    }

    tty.c_cflag &= ~PARENB; // Clear parity bit, disabling parity (most common)
    tty.c_cflag &= ~CSTOPB; // Clear stop field, only one stop bit used in communication (most common)
    tty.c_cflag |= CS8; // 8 bits per byte (most common)
    tty.c_cflag &= ~020000000000; // Disable RTS/CTS hardware flow control (most common)
    tty.c_cflag |= CREAD | CLOCAL; // Turn on READ & ignore ctrl lines (CLOCAL = 1)

    tty.c_lflag &= ~ICANON;
    tty.c_lflag &= ~ECHO; // Disable echo
    tty.c_lflag &= ~ECHOE; // Disable erasure
    tty.c_lflag &= ~ECHONL; // Disable new-line echo
    tty.c_lflag &= ~ISIG; // Disable interpretation of INTR, QUIT and SUSP
    tty.c_iflag &= ~(IXON | IXOFF | IXANY); // Turn off s/w flow ctrl
    tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL); // Disable any special handling of received bytes

    tty.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
    tty.c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed

    tty.c_cc[VTIME] = 12;    // Wait for up to 1.2s (12 deciseconds), returning as soon as any data is received. Arduino send data each second
    tty.c_cc[VMIN] = 0;

    // Set in/out baud rate to be 9600
    cfsetispeed(&tty, B9600);
    cfsetospeed(&tty, B9600);

    // Save tty settings, also checking for error
    if (tcsetattr(bus, TCSANOW, &tty) != 0) {
        printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
        exit(-1);
    }

    // Loop
    while(1){

        // Get curren time
        time(&TimeStamp);

        // Check last of a day
        if(((int)difftime(TimeStamp, TimeStamp_0)) > DAY_STAMP){

            // Storage log file into external disk
            // ....

            // Remove log file
            // ...

            // Update stamp marker
            TimeStamp_0 = TimeStamp;

            // Update Filename
            sprintf(Path, "%s%s%ld%s", Path_To_Storage_LogFiles, Filename, TimeStamp_0, ".csv");

            // Open file
            fp = fopen(Path, "w");

            // Write file
            if(fprintf(fp, "Temperature,Humidity,Timestamp,Date \n") < 0){
                printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
                exit(-1);
            }

            // Close file
            if(fclose(fp) != 0) {
                printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
                exit(-1);
            }
        }

        // Something in COM ?
        // Read it 
        char buffer[256];
        memset(&buffer, '\0', sizeof(buffer));

        // Read bytes.
        int n = read(bus, &buffer, sizeof(buffer));

        // Parse json message
        ParsedMessage = json_tokener_parse(buffer);

        // Update temperature and humidity
        json_object_object_get_ex(ParsedMessage, "Temperature", &Temperature);
        json_object_object_get_ex(ParsedMessage, "Humidity", &Humidity);


        // Change message to send to web
        sprintf(Message2SendToWeb, "%s,%s,%ld", json_object_get_string(Temperature), json_object_get_string(Humidity), TimeStamp);

        // Append to log file
        fp = fopen(Path, "a");

        // Write file
        if(fprintf(fp, "%s,%s,%ld,%s \n", json_object_get_string(Temperature), json_object_get_string(Humidity), TimeStamp,  ctime(&TimeStamp)) < 0){
           printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
           exit(-1);
        }

        // Close file
        if(fclose(fp) != 0) {
            printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
            exit(-1);
        }
        
        // Send to web via TCP/IP
        if(SendMessageToWeb(Message2SendToWeb) < 0) exit(-1);

        // Log measures
        printf("%s \n Temperature: %s [ºC] \n Humidity: %s [/100] \n", ctime(&TimeStamp), json_object_get_string(Temperature), json_object_get_string(Humidity));


    }

    // Close Bus 
    close(bus);

    return 0;
}
