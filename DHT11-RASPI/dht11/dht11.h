/*  DHT11 Temperature & Humidity Sensor
*	
*	Weather Station Project v.01
*
*
*	By Víctor Malumbres Talles
*/
#include <wiringPi.h>

#ifndef dht11_h
#define dht11_h

#include <Arduino.h>

#define DHTLIB_VERSION "v.01"

#define DHTLIB_OK				0
#define DHTLIB_ERROR_CHECKSUM	-1
#define DHTLIB_ERROR_TIMEOUT	-2

#define N_Bytes 5
#define N_Bits 40

#define Start_Transmission_Bit_T 50 // in us
#define Response_Signal_T 80 // in us
#define Ask_Measure_T 18// in us

// dht11 sensor class
class dht11{

	public:

		/*  ------  variables  ------ */

		// Magnitude variables
		float temperature; 
		float humidity;

		// Number of pin connected with dht11 sensor
		int pin;

		/*  ------ Functions ------*/

		// Read magnitudes from dht11 sensors	
		int read_dht11();

}

