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
  dp,D3,D4        |    No connection
 
 
 */ 



#include <SevSeg.h>

SevSeg sevseg; 

int i = 0;

void setup(){
  
  byte numDigits = 2;
  byte digitPins[] = {6, 7};
  byte segmentPins[] = {8, 9, 10, 11, 14, 15, 16};
  bool resistorsOnSegments = false; // 'false' means resistors are on digit pins
  byte hardwareConfig = COMMON_ANODE; // See README.md for options
  bool updateWithDelays = false; // Default 'false' is Recommended
  bool leadingZeros = false; // Use 'true' if you'd like to keep the leading zeros
  bool disableDecPoint = true; // Use 'true' if your decimal point doesn't exist or isn't connected. Then, you only need to specify 7 segmentPins[]

  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments, updateWithDelays, leadingZeros, disableDecPoint);
  sevseg.setBrightness(90);
}

void loop(){
    i++;
    sevseg.setNumber(i, 0);
    sevseg.refreshDisplay();
    sevseg.blank();
    sevseg.refreshDisplay();

    if (i == 16)
    {
       i = 0;
    }
 }
