/*
 Pin-out of arduino with the LED display is as follows. Refer the attached image to see the LED display's pinout
   LEd display    |        Arduino
   ________________________________
                  |
       D1         |    6
       D2         |    7
        a         |    8
        b         |    9
        c         |    10
        d         |    11
        e         |    14
        f         |    15
        g         |    16
  D3,D4,dp        |    No connection
 
 
 */ 



#include <SevSeg.h>

SevSeg sevseg; 

void setup(){
  byte numDigits = 2;
  byte digitPins[] = {6,7};
  byte segmentPins[] = {8,9,10,11,14,15,16,17};

  bool resistorsOnSegments = true; 
  bool updateWithDelaysIn = true;
  byte hardwareConfig = COMMON_ANODE; 
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments);
  sevseg.setBrightness(90);
}

void loop(){
    sevseg.setNumber(1, 0);
    sevseg.refreshDisplay();
    delay(500);
    clearled();
    sevseg.refreshDisplay();
    
    sevseg.setNumber(2, 0);
    sevseg.refreshDisplay();
    delay(500);
    clearled();
    sevseg.refreshDisplay();
    
    sevseg.setNumber(3, 0);
    sevseg.refreshDisplay();
    delay(500);
    clearled();
    sevseg.refreshDisplay();
    
    sevseg.setNumber(4, 0);
    sevseg.refreshDisplay();
    delay(500);
    clearled();
    sevseg.refreshDisplay();
    
    sevseg.setNumber(5, 0);
    sevseg.refreshDisplay();
    delay(500);
    clearled();
    sevseg.refreshDisplay();
    
    sevseg.setNumber(6, 0);
    sevseg.refreshDisplay();
    delay(500);
    clearled();
    sevseg.refreshDisplay();
    
    sevseg.setNumber(7, 0);
    sevseg.refreshDisplay();
    delay(500);
    clearled();
    sevseg.refreshDisplay();
    
    sevseg.setNumber(8, 0);
    sevseg.refreshDisplay();
    delay(500);
    clearled();
    sevseg.refreshDisplay();
    
    sevseg.setNumber(9, 0);
    sevseg.refreshDisplay();
    delay(500);
    clearled();
    sevseg.refreshDisplay();
    
    sevseg.setNumber(10, 0);
    sevseg.refreshDisplay();
    delay(500);
    clearled();
    sevseg.refreshDisplay();
    
    sevseg.setNumber(11, 0);
    sevseg.refreshDisplay();
    delay(500);
    clearled();
    sevseg.refreshDisplay();
    
    sevseg.setNumber(12, 0);
    sevseg.refreshDisplay();
    delay(500);
    clearled();
    sevseg.refreshDisplay();
    
    sevseg.setNumber(13, 0);
    sevseg.refreshDisplay();
    delay(500);
    clearled();
    sevseg.refreshDisplay();
    
    sevseg.setNumber(14, 0);
    sevseg.refreshDisplay();
    delay(500);
    clearled()
    sevseg.refreshDisplay();
    
    sevseg.setNumber(15, 0);
    sevseg.refreshDisplay();
    delay(500);
    clearled();
    sevseg.refreshDisplay();
    
    sevseg.setNumber(16, 0);
    sevseg.refreshDisplay();
    delay(500);
    clearled();
    sevseg.refreshDisplay();
 }

void clearled(){

    digitalWrite(8,HIGH);
    digitalWrite(9,HIGH);
    digitalWrite(10,HIGH);
    digitalWrite(11,HIGH);
    digitalWrite(14,HIGH);
    digitalWrite(15,HIGH);
    digitalWrite(16,HIGH);
    digitalWrite(17,HIGH);
   
  }
