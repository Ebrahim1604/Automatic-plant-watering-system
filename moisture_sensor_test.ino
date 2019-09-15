#include "wiring_private.h"
#include "pins_arduino.h"

/*
 Pin-out of moisture sensor:
 connect the electrodes which are immersed in soil to theend of the module having two pins.
 From the other end, connect GND, VCC to arduino GND, VCC and connect AO pin to the Arduino A0 pin
*/
const int sensor_pin = A0;  // Soil moisture sensor O/P pin 

uint8_t analog_reference = DEFAULT;

void setup() {
  Serial.begin(9600); //Define baud rate for serial communication 
}

void loop() {
  float moisture_percentage;
  int sensor_analog;
  sensor_analog = read_analog_pin(sensor_pin);
  moisture_percentage = ( 100 - ( (sensor_analog/1023.00) * 100 ) );
  Serial.print("Moisture Percentage = ");
  Serial.print(moisture_percentage);
  Serial.println("%");
  delay(1000);
 }

void analogReference(uint8_t mode)
{
  // can't actually set the register here because the default setting
  // will connect AVCC and the AREF pin, which would cause a short if
  // there's something connected to AREF.
  analog_reference = mode;
}

int read_analog_pin(uint8_t pin)
{
  uint8_t low, high;
  
  if (pin >= 54) pin -= 54; // allow for channel or pin numbers

#if defined(ADCSRB) && defined(MUX5)
  // the MUX5 bit of ADCSRB selects whether we're reading from channels
  // 0 to 7 (MUX5 low) or 8 to 15 (MUX5 high).
  ADCSRB = (ADCSRB & ~(1 << MUX5)) | (((pin >> 3) & 0x01) << MUX5);
#endif
  
  // set the analog reference (high two bits of ADMUX) and select the
  // channel (low 4 bits).  this also sets ADLAR (left-adjust result)
  // to 0 (the default).
#if defined(ADMUX)

  ADMUX = (analog_reference << 6) | (pin & 0x07);

#endif

  // without a delay, we seem to read from the wrong channel
  //delay(1);

#if defined(ADCSRA) && defined(ADCL)
  // start the conversion
  sbi(ADCSRA, ADSC);

  // ADSC is cleared when the conversion finishes
  while (bit_is_set(ADCSRA, ADSC));

  // we have to read ADCL first; doing so locks both ADCL
  // and ADCH until ADCH is read.  reading ADCL second would
  // cause the results of each conversion to be discarded,
  // as ADCL and ADCH would be locked when it completed.
  low  = ADCL;
  high = ADCH;
#else
  // we dont have an ADC, return 0
  low  = 0;
  high = 0;
#endif

  // combine the two bytes
  return (high << 8) | low;
}
