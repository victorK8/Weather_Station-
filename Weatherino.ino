/* Firmware of Weather Station*/
/* By victorK8 */


float temperature = 25.0; // In Celsius Degrees [ºC]
float humidity = 55.6; // In [%]

void setup() {
  
  /* Set up UART communication */
  Serial.begin(9600);
  
}

void loop() {

  /* Get measures */
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
