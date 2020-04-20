/* Firmware of Weather Station*/
/* By victorK8 */
  
 

float temperature = 25.0; // In Celsius Degrees [ºC]
float humidity = 55.6; // In [%]


/* --- Functions --- */

float GetTemp(){

  // The internal temperature has to be used
  // with the internal reference of 1.1V.
  // Channel 8 can not be selected with
  // the analogRead function yet.

  // Set the internal reference and mux 8.
  ADMUX = 0b11001000;

  // Enable ADC
  ADCSRA |= _BV(ADEN);  // enable the ADC

  delay(20);            // wait for voltages to become stable.

  ADCSRA |= _BV(ADSC);  // Start the ADC

  // Detect end-of-conversion
  while (bit_is_set(ADCSRA,ADSC));

  // Implement ADCL*4 - 260.45.
  float result = ADCL;
  result *= 4;
  result -= 260.45;

  // The returned temperature is in degrees Celsius.
  return result;
}



/* MAIN */

void setup() {
  
  /* Set up UART communication */
  Serial.begin(9600);
  
}


void loop() {

  /* Get measures */

  temperature =  GetTemp();
  /* ... */

  /*Create JSON messge */
  String message_as_string = "{\"Temperature\": " + String(temperature) + ", \"Humidity\": " + String(humidity) + "}\n";
  int message_size = message_as_string.length();
  
  /* String to char[]*/
  char message_to_send[message_size];
  message_as_string.toCharArray(message_to_send,message_size + 1);

   /* Send message via UART */
  Serial.write(message_to_send);

  /* Timer */
  delay(500);
}
