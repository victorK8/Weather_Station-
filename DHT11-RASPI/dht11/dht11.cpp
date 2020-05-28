/*  DHT11 Temperature & Humidity Sensor
*	
*	Weather Station Project v.01
*
*
*	By Víctor Malumbres Talles
*/

#include "dht11.h"


// Ask for a measure
int ask_measure(int pin){

	// wait 1 second
	delay(1000);

	// Pin as output
	pinMode(pin, OUTPUT);

	// Low 
	digitalWrite(pin, LOW);

	delay(Ask_Measure_T);

	// High
	digitalWrite(pin, HIGH);

	// Some us delay ()
	delayMicroseconds(40);

	// Pin as input
	pinMode(pin, INPUT);

	return DHTLIB_OK;
}

// Set-up
int dht11::setup(){
   return wiringPiSetup();
}

// Set pin
int dht11::setPin(int number){
   pin = number;
   return 0;
}

// Get pin
int dht11::getPin(){
  return pin;
}

// Get temp. measure
float dht11::getTemperature(){
  return temperature;
}

// Get hum. measure
float dht11::getHumidity(){
 return humidity;
}


// Read data from dht11 Sensor
int dht11::read_dht11()
{
	// Data format: 8bit integral RH data + 8bit decimal RH data + 8bit integral T data + 8bit decimal T data + 8bit check sum. 

	// Buffer 
	uint8_t data[N_Bytes];


	// Ask for measures
	int rlst = ask_measure(pin); 

    // Check sensor response signal
	uint8_t check_time = 0;

	// Check for low state
	while(digitalRead(pin) == LOW){

		check_time ++;
		delayMicroseconds(1);

		if(check_time > Response_Signal_T) return DHTLIB_ERROR_TIMEOUT;
	}

	// Check for high state
	check_time = 0;
	while(digitalRead(pin) == HIGH){

		check_time ++;
		delayMicroseconds(1);

		if(check_time > Response_Signal_T) return DHTLIB_ERROR_TIMEOUT;
	}


	// Start data transmission

	uint8_t ReadBytes = 0;
	uint8_t ByteOfBits[8];

	for (int i=0; i < N_Bytes; i++)
	{
		// Read a byte
		for(int read_bits=0; read_bits<8;read_bits++){

			// Wait for start transmission bit
			check_time = 0;
			while(digitalRead(pin) == LOW){

				check_time ++;
				delayMicroseconds(1);

				if(check_time > Start_Transmission_Bit_T) return DHTLIB_ERROR_TIMEOUT;
			}

			// Data bit (26/28 us is 0, 70 us is)
			check_time = 0;
			while(digitalRead(pin) == HIGH){
				check_time ++;
				delayMicroseconds(1);
			}

			// Determine if bit is 0 or 1. Add to ByteOfBits buffer
			if(check_time>30){
				// Bit is one
				data[i]+= pow(2,(8-read_bits));
			}

		}

	}

	// Reading is finished

	// Check sum
	if ((data[0]+data[1]+data[2]+data[3]) == data[N_Bytes-1]){

		// Get Humidity
		humidity = data[0];
		humidity += ((float)data[1])/1000;

		// Get Tempereature
		temperature = data[2];
		temperature += ((float)data[3])/1000;

	} else{
		return DHTLIB_ERROR_CHECKSUM;
	}


	return DHTLIB_OK;


}
