/*
Pinout of Relay with Arduino
relay-->Arduino
VCC --> 5v
GND --> GND
IN --> A8

Pinout of Relay with Pump
 relay --> Pump
 Common --> Positive of power supply/ Battery
 NO --> Positive of Pump
 
Note:  Negative of pump ---> Negative of power supply/ Battery

Connect analog pin A3 to GND to start and stop pump operations. Observe Serial monitor.

*/



const int trigger = A3;
const int relay = A8;

void setup() {
  // put your setup code here, to run once:
  pinMode(trigger,INPUT_PULLUP);
  pinMode(relay,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
   if(digitalRead(trigger)==LOW){
   
      Serial.println("Pumping for 10 secs");
      digitalWrite(relay,HIGH);
      delay(10000);
      digitalWrite(relay,LOW);

      Serial.println("1 second delay");
      delay(1000);

      Serial.println("Pumping for 5 secs");
      digitalWrite(relay,HIGH);
      delay(5000);
      digitalWrite(relay,LOW);

      Serial.println("1 second delay");
      delay(1000);

      Serial.println("Pumping for 2 secs");
      digitalWrite(relay,HIGH);
      delay(2000);
      digitalWrite(relay,LOW);

      Serial.println("1 second delay");
      delay(1000);

      
    }

}
