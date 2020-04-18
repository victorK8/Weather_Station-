/* --- usb-reader funcionality in c++ by victor malumbres --- */

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <chrono> 
#include <fstream>

using namespace std;


/* --- Global vars ---*/

const string Path_To_Storage_LogFiles = "~/Desktop/Log_Files";
const string Filename_Name = "RaspiWeatherStation_Log_";
const string Header = "Temperature,Humidity,Timestamp,Date \n ";

/* --- Weather structure --- */

struct weather{
    float temperature;
    float humidity;
};



/* --- Functions --- */


// Send message to the web server
// As input get a string message with 
// weather magnitudes in csv format
int send_to_server(string message){

        // Local vars
        int mySocket = 0;
        struct sockaddr_in Web_Address;
        string request2send = "";

        // Make request 
        request2send = "GET /CurrentData/" + message + " HTTP/1.1\r\nHost: localhost:80  \r\n\r\n";

        // convert to char*
        char ptr_request[request2send.length() + 1]; 
        strcpy(ptr_request, request2send.c_str()); 
        
        // Create the socket
         mySocket = socket(AF_INET, SOCK_STREAM, 0);
        
        // Check socket 
        if(mySocket<0)
        { 
            cout << " Error in socket creation";
            return -1;
        }

        // Set web server properties
        Web_Address.sin_family = AF_INET; 
        Web_Address.sin_port = htons(80); 

        // Convert IP addresses from text to binary form 
        if(inet_pton(AF_INET, "127.0.0.1", &Web_Address.sin_addr)<=0) 
        { 
            printf("\nInvalid address/ Address not supported \n"); 
            return -1; 
        } 

        // Connect sockets
        if (connect(mySocket, (struct sockaddr *)&Web_Address, sizeof(Web_Address)) < 0) 
        { 
            printf("\nConnection Failed \n"); 
            return -1; 
        } 

        // Send request
        send(mySocket , ptr_request , sizeof(ptr_request), 0 );

        return 0;
}

/* ------ APP  -----*/
int main(int argc, char const *argv[]){

    // Local vars
    weather magnitudes;

    // Loop
    while(true){

      string message_from_usb = "{\"Temperature\": 22, \"Humidity\": 55}\n";

      // Send message to server
      int rlst = send_to_server("500,500,10000000"); 


    }


    return 0;
}

