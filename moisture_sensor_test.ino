/*
 Pin-out of moisture sensor:
 connect the electrodes which are immersed in soil to theend of the module having two pins.
 From the other end, connect GND, VCC to arduino GND, VCC and connect AO pin to the Arduino A0 pin
*/
const int sensor_pin = A0;  // Soil moisture sensor O/P pin 

void setup() {
  Serial.begin(9600); //Define baud rate for serial communication 
}

void loop() {
  float moisture_percentage;
  int sensor_analog;
  sensor_analog = analogRead(sensor_pin);
  moisture_percentage = ( 100 - ( (sensor_analog/1023.00) * 100 ) );
  Serial.print("Moisture Percentage = ");
  Serial.print(moisture_percentage);
  Serial.println("%");
  delay(1000);
 }
