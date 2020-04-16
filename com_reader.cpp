/* --- usb-reader funcionality in c++ by victor malumbres --- */

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <iostream>

using namespace std;

#define PORT 8888

/* Functions */
int send_to_server(string message){

        // Local vars
        string IP = "localhost";
        int mySocket = 0;
        struct sockaddr_in Web_Address;
        string request2send = "";

        // Make request 
        request2send = "GET /CurrentData/" + message + " HTTP/1.1\r\nHost: localhost:8888  \r\n\r\n";

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
        Web_Address.sin_port = htons(PORT); 

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

/* App */
int main(int argc, char const *argv[]){

    bool run = true;

    // Loop
    while(run){

      // Send message to server
      int rlst = send_to_server("500,500,10000000"); 

      // Check result
      if(rlst!=0)
      {
          run = false;
      }
    }


    return 0;
}

