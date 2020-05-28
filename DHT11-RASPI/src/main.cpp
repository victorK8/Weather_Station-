/* ********* Script for getting measures by using dht11 in raspberry pi 4 ************************ 
************* By víctor *********************************
*/


#include <../dht11/dht11.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>


// APP
int main(void){

    // Create dht11 object
    dht11 SensorObj;

    // Set pin
    SensorObj.setPin(17);
	
    // Set-up obj sensor
    if(SensorObj.setup()<0){
      printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
      exit(-1);
    }

    while(true){
     
     // Take measure
     int MeasureFlag = SensorObj.read_dht11();
	
     // Print in console
     printf("Temperature: %f [ºC] Humidity: %f [PerCento]",SensorObj.getTemperature(), SensorObj.getHumidity());
    }
    return 0;
}
