/*
  Pinout of ky-018 module:
  - sign pin--> GND
  middle--> A1
  left pin--> VCC
 */

int sensorPin = A1; //define analog pin 1
int value; 
float light_percentage;

void setup() {
  Serial.begin(9600); 
} 

void loop() {
  value = analogRead(sensorPin);
  light_percentage = (value*100.0)/1023.0;
  Serial.print("light Percentage = ");
  Serial.print(light_percentage);
  Serial.println("%");
  delay(100); 
}
