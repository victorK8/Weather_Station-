/* Firmware of Weather Station*/
/* By victorK8 */


float temperature = 25.0; // In Celsius Degrees [ºC]
float humidity = 55.6; // In [%]


/* --- Functions --- */

double GetTemp(){
  unsigned int wADC;
  double t;

  // The internal temperature has to be used
  // with the internal reference of 1.1V.
  // Channel 8 can not be selected with
  // the analogRead function yet.

  // Set the internal reference and mux.
  ADMUX = (_BV(REFS1) | _BV(REFS0) | _BV(MUX3));
  ADCSRA |= _BV(ADEN);  // enable the ADC

  delay(20);            // wait for voltages to become stable.

  ADCSRA |= _BV(ADSC);  // Start the ADC

  // Detect end-of-conversion
  while (bit_is_set(ADCSRA,ADSC));

  // Reading register "ADCW" takes care of how to read ADCL and ADCH.
  wADC = ADCW;

  // The offset of 324.31 could be wrong. It is just an indication.
  t = (wADC - 324.31 ) / 1.22;

  // The returned temperature is in degrees Celsius.
  return (t);
}



/* MAIN */

void setup() {
  
  /* Set up UART communication */
  Serial.begin(9600);
  
}


void loop() {

  /* Get measures */

  temperature = (float) GetTemp();
  /* ... */

  /*Create JSON messge */
  String message_as_string = "{\"Temperature\": " + String(temperature)+ ", \"Humidity\": " + String(humidity) + "}\n";
  int message_size = message_as_string.length();
  
  /* String to char[]*/
  char message_to_send[message_size];
  message_as_string.toCharArray(message_to_send,message_size + 1);

   /* Send message via UART */
  Serial.write(message_to_send);

  /* Timer */
  delay(500);
}
