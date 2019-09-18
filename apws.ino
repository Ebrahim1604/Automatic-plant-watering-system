/*

 Connections:
 Sensor/actuator-------->Arduino
 1)moisture sensor------> A0
 2)photoresistor--------> A1
 3)Temp&humidity sensor--> A2
 4)relay for pump--------> 12

    LEd display-1  |        Arduino
   ________________________________
                   |
     D1/Common     |    2
        a1         |    4
        b1         |    4
        c1         |    5
        d1         |    7
        e1         |    8
        f1         |    9
        g1         |    10
        dp1        |    No connection

    LEd display-2  |        Arduino
   ________________________________
                   |
     D2/Common     |    3
        a2         |    14
        b2         |    15
        c2         |    16
        d2         |    17
        e2         |    22
        f2         |    24
        g2         |    26
        dp2        |    No connection

 */

#define ARDUINO_MAIN
#include "wiring_private.h"
#include "pins_arduino.h"
#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include "DHT.h"

uint8_t analog_reference = DEFAULT;

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
  //wait_in_millis(1);

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

static void nothing(void) {
  }
  
  static volatile voidFuncPtr intFunc[EXTERNAL_NUM_INTERRUPTS] = {
  #if EXTERNAL_NUM_INTERRUPTS > 8
      #warning There are more than 8 external interrupts. Some callbacks may not be initialized.
      nothing,
  #endif
  #if EXTERNAL_NUM_INTERRUPTS > 7
      nothing,
  #endif
  #if EXTERNAL_NUM_INTERRUPTS > 6
      nothing,
  #endif
  #if EXTERNAL_NUM_INTERRUPTS > 5
      nothing,
  #endif
  #if EXTERNAL_NUM_INTERRUPTS > 4
      nothing,
  #endif
  #if EXTERNAL_NUM_INTERRUPTS > 3
      nothing,
  #endif
  #if EXTERNAL_NUM_INTERRUPTS > 2
      nothing,
  #endif
  #if EXTERNAL_NUM_INTERRUPTS > 1
      nothing,
  #endif
  #if EXTERNAL_NUM_INTERRUPTS > 0
      nothing,
  #endif
  };
  
  #define IMPLEMENT_ISR(vect, interrupt) \
    ISR(vect) { \
      intFunc[interrupt](); \
    }
  
  #if defined(EICRA) && defined(EICRB)
  
  IMPLEMENT_ISR(INT0_vect, EXTERNAL_INT_2)
  IMPLEMENT_ISR(INT1_vect, EXTERNAL_INT_3)
  IMPLEMENT_ISR(INT2_vect, EXTERNAL_INT_4)
  IMPLEMENT_ISR(INT3_vect, EXTERNAL_INT_5)
  IMPLEMENT_ISR(INT4_vect, EXTERNAL_INT_0)
  IMPLEMENT_ISR(INT5_vect, EXTERNAL_INT_1)
  IMPLEMENT_ISR(INT6_vect, EXTERNAL_INT_6)
  IMPLEMENT_ISR(INT7_vect, EXTERNAL_INT_7)
  
  #else
  
  IMPLEMENT_ISR(INT0_vect, EXTERNAL_INT_0)
  IMPLEMENT_ISR(INT1_vect, EXTERNAL_INT_1)
  
  #if defined(EICRA) && defined(ISC20)
  IMPLEMENT_ISR(INT2_vect, EXTERNAL_INT_2)
  #endif
  
  #endif
  
  void attach_interrupt_pin(uint8_t interruptNum, void (*userFunc)(void), int mode) 
  {
    if(interruptNum < EXTERNAL_NUM_INTERRUPTS) 
    {
      intFunc[interruptNum] = userFunc;
      
      // Configure the interrupt mode (trigger on low input, any change, rising
      // edge, or falling edge).  The mode constants were chosen to correspond
      // to the configuration bits in the hardware register, so we simply shift
      // the mode into place.
        
      // Enable the interrupt.
        
      switch (interruptNum) {
  #if defined(EICRA) && defined(EICRB) && defined(EIMSK)
      case 2:
        EICRA = (EICRA & ~((1 << ISC00) | (1 << ISC01))) | (mode << ISC00);
        EIMSK |= (1 << INT0);
        break;
      case 3:
        EICRA = (EICRA & ~((1 << ISC10) | (1 << ISC11))) | (mode << ISC10);
        EIMSK |= (1 << INT1);
        break;
      case 4:
        EICRA = (EICRA & ~((1 << ISC20) | (1 << ISC21))) | (mode << ISC20);
        EIMSK |= (1 << INT2);
        break;
      case 5:
        EICRA = (EICRA & ~((1 << ISC30) | (1 << ISC31))) | (mode << ISC30);
        EIMSK |= (1 << INT3);
        break;
      case 0:
        EICRB = (EICRB & ~((1 << ISC40) | (1 << ISC41))) | (mode << ISC40);
        EIMSK |= (1 << INT4);
        break;
      case 1:
        EICRB = (EICRB & ~((1 << ISC50) | (1 << ISC51))) | (mode << ISC50);
        EIMSK |= (1 << INT5);
        break;
      case 6:
        EICRB = (EICRB & ~((1 << ISC60) | (1 << ISC61))) | (mode << ISC60);
        EIMSK |= (1 << INT6);
        break;
      case 7:
        EICRB = (EICRB & ~((1 << ISC70) | (1 << ISC71))) | (mode << ISC70);
        EIMSK |= (1 << INT7);
        break;
  #else   
      case 0:
      #if defined(EICRA) && defined(ISC00) && defined(EIMSK)
        EICRA = (EICRA & ~((1 << ISC00) | (1 << ISC01))) | (mode << ISC00);
        EIMSK |= (1 << INT0);
      #elif defined(MCUCR) && defined(ISC00) && defined(GICR)
        MCUCR = (MCUCR & ~((1 << ISC00) | (1 << ISC01))) | (mode << ISC00);
        GICR |= (1 << INT0);
      #elif defined(MCUCR) && defined(ISC00) && defined(GIMSK)
        MCUCR = (MCUCR & ~((1 << ISC00) | (1 << ISC01))) | (mode << ISC00);
        GIMSK |= (1 << INT0);
      #else
        #error attach_interrupt_pin not finished for this CPU (case 0)
      #endif
        break;
  
      case 1:
      #if defined(EICRA) && defined(ISC10) && defined(ISC11) && defined(EIMSK)
        EICRA = (EICRA & ~((1 << ISC10) | (1 << ISC11))) | (mode << ISC10);
        EIMSK |= (1 << INT1);
      #elif defined(MCUCR) && defined(ISC10) && defined(ISC11) && defined(GICR)
        MCUCR = (MCUCR & ~((1 << ISC10) | (1 << ISC11))) | (mode << ISC10);
        GICR |= (1 << INT1);
      #elif defined(MCUCR) && defined(ISC10) && defined(GIMSK) && defined(GIMSK)
        MCUCR = (MCUCR & ~((1 << ISC10) | (1 << ISC11))) | (mode << ISC10);
        GIMSK |= (1 << INT1);
      #else
        #warning attach_interrupt_pin may need some more work for this cpu (case 1)
      #endif
        break;
      
      case 2:
      #if defined(EICRA) && defined(ISC20) && defined(ISC21) && defined(EIMSK)
        EICRA = (EICRA & ~((1 << ISC20) | (1 << ISC21))) | (mode << ISC20);
        EIMSK |= (1 << INT2);
      #elif defined(MCUCR) && defined(ISC20) && defined(ISC21) && defined(GICR)
        MCUCR = (MCUCR & ~((1 << ISC20) | (1 << ISC21))) | (mode << ISC20);
        GICR |= (1 << INT2);
      #elif defined(MCUCR) && defined(ISC20) && defined(GIMSK) && defined(GIMSK)
        MCUCR = (MCUCR & ~((1 << ISC20) | (1 << ISC21))) | (mode << ISC20);
        GIMSK |= (1 << INT2);
      #endif
        break;
  #endif
      }
    }
  }

 void wait_in_millis(unsigned long ms)
  {
    uint32_t start = micros();
  
    while (ms > 0) {
      yield();
      while ( ms > 0 && (micros() - start) >= 1000) {
        ms--;
        start += 1000;
      }
    }
  }

void assign_digital_pin(uint8_t pin, uint8_t mode)
  {
    uint8_t bit = digitalPinToBitMask(pin);
    uint8_t port = digitalPinToPort(pin);
    volatile uint8_t *reg, *out;
  
    if (port == NOT_A_PIN) return;
  
    // JWS: can I let the optimizer do this?
    reg = portModeRegister(port);
    out = portOutputRegister(port);
  
    if (mode == INPUT) { 
      uint8_t oldSREG = SREG;
                  cli();
      *reg &= ~bit;
      *out &= ~bit;
      SREG = oldSREG;
    } else if (mode == INPUT_PULLUP) {
      uint8_t oldSREG = SREG;
                  cli();
      *reg &= ~bit;
      *out |= bit;
      SREG = oldSREG;
    } else {
      uint8_t oldSREG = SREG;
                  cli();
      *reg |= bit;
      SREG = oldSREG;
    }
  }

static void turn_pwm_off(uint8_t timer)
  {
    switch (timer)
    {
      #if defined(TCCR1A) && defined(COM1A1)
      case TIMER1A:   cbi(TCCR1A, COM1A1);    break;
      #endif
      #if defined(TCCR1A) && defined(COM1B1)
      case TIMER1B:   cbi(TCCR1A, COM1B1);    break;
      #endif
      #if defined(TCCR1A) && defined(COM1C1)
      case TIMER1C:   cbi(TCCR1A, COM1C1);    break;
      #endif
      
      #if defined(TCCR2) && defined(COM21)
      case  TIMER2:   cbi(TCCR2, COM21);      break;
      #endif
      
      #if defined(TCCR0A) && defined(COM0A1)
      case  TIMER0A:  cbi(TCCR0A, COM0A1);    break;
      #endif
      
      #if defined(TCCR0A) && defined(COM0B1)
      case  TIMER0B:  cbi(TCCR0A, COM0B1);    break;
      #endif
      #if defined(TCCR2A) && defined(COM2A1)
      case  TIMER2A:  cbi(TCCR2A, COM2A1);    break;
      #endif
      #if defined(TCCR2A) && defined(COM2B1)
      case  TIMER2B:  cbi(TCCR2A, COM2B1);    break;
      #endif
      
      #if defined(TCCR3A) && defined(COM3A1)
      case  TIMER3A:  cbi(TCCR3A, COM3A1);    break;
      #endif
      #if defined(TCCR3A) && defined(COM3B1)
      case  TIMER3B:  cbi(TCCR3A, COM3B1);    break;
      #endif
      #if defined(TCCR3A) && defined(COM3C1)
      case  TIMER3C:  cbi(TCCR3A, COM3C1);    break;
      #endif
  
      #if defined(TCCR4A) && defined(COM4A1)
      case  TIMER4A:  cbi(TCCR4A, COM4A1);    break;
      #endif          
      #if defined(TCCR4A) && defined(COM4B1)
      case  TIMER4B:  cbi(TCCR4A, COM4B1);    break;
      #endif
      #if defined(TCCR4A) && defined(COM4C1)
      case  TIMER4C:  cbi(TCCR4A, COM4C1);    break;
      #endif      
      #if defined(TCCR4C) && defined(COM4D1)
      case TIMER4D: cbi(TCCR4C, COM4D1);  break;
      #endif      
        
      #if defined(TCCR5A)
      case  TIMER5A:  cbi(TCCR5A, COM5A1);    break;
      case  TIMER5B:  cbi(TCCR5A, COM5B1);    break;
      case  TIMER5C:  cbi(TCCR5A, COM5C1);    break;
      #endif
    }
  }
  
  void write_digital_pin(uint8_t pin, uint8_t val)
  {
    uint8_t timer = digitalPinToTimer(pin);
    uint8_t bit = digitalPinToBitMask(pin);
    uint8_t port = digitalPinToPort(pin);
    volatile uint8_t *out;
  
    if (port == NOT_A_PIN) return;
  
    // If the pin that support PWM output, we need to turn it off
    // before doing a digital write.
    if (timer != NOT_ON_TIMER) turn_pwm_off(timer);
  
    out = portOutputRegister(port);
  
    uint8_t oldSREG = SREG;
    cli();
  
    if (val == LOW) {
      *out &= ~bit;
    } else {
      *out |= bit;
    }
  
    SREG = oldSREG;
  }
int read_digital_pin(uint8_t pin)
  {
    uint8_t timer = digitalPinToTimer(pin);
    uint8_t bit = digitalPinToBitMask(pin);
    uint8_t port = digitalPinToPort(pin);
  
    if (port == NOT_A_PIN) return LOW;
  
    // If the pin that support PWM output, we need to turn it off
    // before getting a digital reading.
    if (timer != NOT_ON_TIMER) turn_pwm_off(timer);
  
    if (*portInputRegister(port) & bit) return HIGH;
    return LOW;
  }

int lightsensor = A1;
float light_thresh = 10.0; // this variable decides the threshold to classify a situation as day or night

const int moisturesensor = A0;  // Soil moisture sensor pin
float moisture_thresh = 50.0; // his variable decides the threshold to classify a situation as wet or dry

const int relay_for_pump = 12;

#define DHTPIN A2     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22 // Specifying the DHT type, i.e DHT22
DHT dht(DHTPIN, DHTTYPE);   // creating an object of DHT

const int D1 = 2;
const int a1 = 4;
const int b1 = 5;
const int c1 = 6;
const int d1 = 7;
const int e1 = 8;
const int f1 = 9;
const int g1 = 10;
//const int DP = 11;// dot is not used in this project

const int D2 = 3;
const int a2 = 14;
const int b2 = 15;
const int c2 = 16;
const int d2 = 17;
const int e2 = 22;
const int f2 = 24;
const int g2 = 26;


bool* sensor_values;
int* current_state_var;

void setup() {
  
 Serial.begin(9600);
 dht.begin();

 assign_digital_pin(D1, OUTPUT);
  assign_digital_pin(a1, OUTPUT);
  assign_digital_pin(b1, OUTPUT);
  assign_digital_pin(c1, OUTPUT);
  assign_digital_pin(d1, OUTPUT);
  assign_digital_pin(e1, OUTPUT);
  assign_digital_pin(f1, OUTPUT);
  assign_digital_pin(g1, OUTPUT);
 
  assign_digital_pin(D2, OUTPUT); 
  assign_digital_pin(a2, OUTPUT);
  assign_digital_pin(b2, OUTPUT);
  assign_digital_pin(c2, OUTPUT);
  assign_digital_pin(d2, OUTPUT);
  assign_digital_pin(e2, OUTPUT);
  assign_digital_pin(f2, OUTPUT);
  assign_digital_pin(g2, OUTPUT);

 attach_interrupt_pin(2, Pause, LOW);
}

void loop() {
  
  sensor_values = sensor_check();
  current_state_var = statecheck(sensor_values);
  stateaction(current_state_var);

}


bool temp()
{
  float t = dht.readTemperature();
  if (t < 25.0){ return LOW; }
  else {return HIGH;}
}

bool humidity()
{
  float h = dht.readHumidity();
  if (h < 50.0){return LOW;}
  else{return HIGH;}  
}

bool light()
{
   int value; 
   float light_percentage;

   value = read_analog_pin(lightsensor);
   light_percentage = (value*100.0)/1023.0;

  if (light_percentage < light_thresh){return LOW;}
  else{return HIGH;}
}

bool moisture()
{
  float moisture_percentage;
  int value;
  value = read_analog_pin(moisturesensor);
  moisture_percentage = ( 100 - ( (value/1023.00) * 100 ) );

  if (moisture_percentage < moisture_thresh){return LOW;}
  else{return HIGH;}

}

bool* sensor_check(){

   static bool values[4];
   values[0] = temp();
   values[1] = humidity();
   values[2] = light();
   values[3] = moisture();

   return values;
    
}


int* Array(int a, int b,int c){
  
    static int var[3];
    var[0] = a;
    var[1] = b;
    var[2] = c;
    return var;
}

int* statecheck(bool* sensor_value){

  if(sensor_value[0]==LOW && sensor_value[1]==LOW && sensor_value[2]==LOW && sensor_value[3]==LOW){
           return Array(1,15000,1000);
    }
 else if(sensor_value[0]==LOW && sensor_value[1]==LOW &&sensor_value[2]==LOW && sensor_value[3]==HIGH){
           return Array(2,30000,3000);
    }
 else if(sensor_value[0]==LOW && sensor_value[1]==LOW && sensor_value[2]==HIGH && sensor_value[3]==LOW){
           return Array(3,15000,3000);
    }
 else if(sensor_value[0]==LOW && sensor_value[1]==LOW && sensor_value[2]==HIGH && sensor_value[3]==HIGH){
           return Array(4,30000,5000);
    }
 else if(sensor_value[0]==LOW && sensor_value[1]==HIGH && sensor_value[2]==LOW && sensor_value[3]==LOW){
           return Array(5,20000,3000);
    }
 else if(sensor_value[0]==LOW && sensor_value[1]==HIGH && sensor_value[2]==LOW && sensor_value[3]==HIGH){
           return Array(6,0,0);
    }
 else if(sensor_value[0]==LOW && sensor_value[1]==HIGH && sensor_value[2]==HIGH && sensor_value[3]==LOW){
           return Array(7,20000,5000);
    }
 else if(sensor_value[0]==LOW && sensor_value[1]==HIGH && sensor_value[2]==HIGH && sensor_value[3]==HIGH){
           return Array(8,30000,1000);
    }
 else if(sensor_value[0]==HIGH && sensor_value[1]==LOW && sensor_value[2]==LOW && sensor_value[3]==LOW){
           return Array(9,10000,3000);
    }
 else if(sensor_value[0]==HIGH && sensor_value[1]==LOW && sensor_value[2]==LOW && sensor_value[3]==HIGH){
           return Array(10,25000,5000);
    }
 else if(sensor_value[0]==HIGH && sensor_value[1]==LOW && sensor_value[2]==HIGH && sensor_value[3]==LOW){
           return Array(11,10000,5000);
    }
 else if(sensor_value[0]==HIGH && sensor_value[1]==LOW && sensor_value[2]==HIGH && sensor_value[3]==HIGH){
           return Array(12,20000,1000);
    }
 else if(sensor_value[0]==HIGH && sensor_value[1]==HIGH && sensor_value[2]==LOW && sensor_value[3]==LOW){
           return Array(13,15000,5000);
    }
 else if(sensor_value[0]==HIGH && sensor_value[1]==HIGH && sensor_value[2]==LOW && sensor_value[3]==HIGH){
           return Array(14,25000,1000);
    }
 else if(sensor_value[0]==HIGH && sensor_value[1]==HIGH && sensor_value[2]==HIGH && sensor_value[3]==LOW){
           return Array(15,10000,1000);
    }
 else if(sensor_value[0]==HIGH && sensor_value[1]==HIGH && sensor_value[2]==HIGH && sensor_value[3]==HIGH){
           return Array(16,25000,3000);
    }
}


void number1(int d)             //Number 1
{
  if (d == 1)
 {
  write_digital_pin(a1, HIGH);
  write_digital_pin(b1, LOW);
  write_digital_pin(c1, LOW);
  write_digital_pin(d1, HIGH);
  write_digital_pin(e1, HIGH);
  write_digital_pin(f1, HIGH);
  write_digital_pin(g1, HIGH);
  }   
 else
 {
  write_digital_pin(a2, HIGH);
  write_digital_pin(b2, LOW);
  write_digital_pin(c2, LOW);
  write_digital_pin(d2, HIGH);
  write_digital_pin(e2, HIGH);
  write_digital_pin(f2, HIGH);
  write_digital_pin(g2, HIGH);
 }
}

void number2(int d)             //Number 2
{ 
  if (d == 1)
 {
  write_digital_pin(a1, LOW);
  write_digital_pin(b1, LOW);
  write_digital_pin(c1, HIGH);
  write_digital_pin(d1, LOW);
  write_digital_pin(e1, LOW);
  write_digital_pin(f1, HIGH);
  write_digital_pin(g1, LOW);
  }   
 else
 {
  write_digital_pin(a2, LOW);
  write_digital_pin(b2, LOW);
  write_digital_pin(c2, HIGH);
  write_digital_pin(d2, LOW);
  write_digital_pin(e2, LOW);
  write_digital_pin(f2, HIGH);
  write_digital_pin(g2, LOW);
 }
}

void number3(int d)            //Number 3
{
  if (d == 1)
 {
  write_digital_pin(a1, LOW);
  write_digital_pin(b1, LOW);
  write_digital_pin(c1, LOW);
  write_digital_pin(d1, LOW);
  write_digital_pin(e1, HIGH);
  write_digital_pin(f1, HIGH);
  write_digital_pin(g1, LOW);
  }   
 else
 {
  write_digital_pin(a2, LOW);
  write_digital_pin(b2, LOW);
  write_digital_pin(c2, LOW);
  write_digital_pin(d2, LOW);
  write_digital_pin(e2, HIGH);
  write_digital_pin(f2, HIGH);
  write_digital_pin(g2, LOW);
 }
}

void number4(int d)             //Number 4
{
  if (d == 1)
 {
  write_digital_pin(a1, HIGH);
  write_digital_pin(b1, LOW);
  write_digital_pin(c1, LOW);
  write_digital_pin(d1, HIGH);
  write_digital_pin(e1, HIGH);
  write_digital_pin(f1, LOW);
  write_digital_pin(g1, LOW);
  }   
 else
 {
  write_digital_pin(a2, HIGH);
  write_digital_pin(b2, LOW);
  write_digital_pin(c2, LOW);
  write_digital_pin(d2, HIGH);
  write_digital_pin(e2, HIGH);
  write_digital_pin(f2, LOW);
  write_digital_pin(g2, LOW);
 }
}

void number5(int d)             //Number 5
{
  if (d == 1)
 {
  write_digital_pin(a1, LOW);
  write_digital_pin(b1, HIGH);
  write_digital_pin(c1, LOW);
  write_digital_pin(d1, LOW);
  write_digital_pin(e1, HIGH);
  write_digital_pin(f1, LOW);
  write_digital_pin(g1, LOW);
  }   
 else
 {
  write_digital_pin(a2, LOW);
  write_digital_pin(b2, HIGH);
  write_digital_pin(c2, LOW);
  write_digital_pin(d2, LOW);
  write_digital_pin(e2, HIGH);
  write_digital_pin(f2, LOW);
  write_digital_pin(g2, LOW);
 }
}

void number6(int d)             //Number 6
{
  if (d == 1)
 {
  write_digital_pin(a1, LOW);
  write_digital_pin(b1, HIGH);
  write_digital_pin(c1, LOW);
  write_digital_pin(d1, LOW);
  write_digital_pin(e1, LOW);
  write_digital_pin(f1, LOW);
  write_digital_pin(g1, LOW);
  }   
 else
 {
  write_digital_pin(a2, LOW);
  write_digital_pin(b2, HIGH);
  write_digital_pin(c2, LOW);
  write_digital_pin(d2, LOW);
  write_digital_pin(e2, LOW);
  write_digital_pin(f2, LOW);
  write_digital_pin(g2, LOW);
 }
}

void number7(int d)            //Number 7
{
  if (d == 1)
 {
  write_digital_pin(a1, LOW);
  write_digital_pin(b1, LOW);
  write_digital_pin(c1, LOW);
  write_digital_pin(d1, HIGH);
  write_digital_pin(e1, HIGH);
  write_digital_pin(f1, HIGH);
  write_digital_pin(g1, HIGH);
  }   
 else
 {
  write_digital_pin(a2, LOW);
  write_digital_pin(b2, LOW);
  write_digital_pin(c2, LOW);
  write_digital_pin(d2, HIGH);
  write_digital_pin(e2, HIGH);
  write_digital_pin(f2, HIGH);
  write_digital_pin(g2, HIGH);
 }
}

void number8(int d)            //Number 8
{
  if (d == 1)
 {
  write_digital_pin(a1, LOW);
  write_digital_pin(b1, LOW);
  write_digital_pin(c1, LOW);
  write_digital_pin(d1, LOW);
  write_digital_pin(e1, LOW);
  write_digital_pin(f1, LOW);
  write_digital_pin(g1, LOW);
  }   
 else
 {
  write_digital_pin(a2, LOW);
  write_digital_pin(b2, LOW);
  write_digital_pin(c2, LOW);
  write_digital_pin(d2, LOW);
  write_digital_pin(e2, LOW);
  write_digital_pin(f2, LOW);
  write_digital_pin(g2, LOW);
  }   
}


void number9(int d)             //Number 9
{
  if (d == 1)
 {
  write_digital_pin(a1, LOW);
  write_digital_pin(b1, LOW);
  write_digital_pin(c1, LOW);
  write_digital_pin(d1, LOW);
  write_digital_pin(e1, HIGH);
  write_digital_pin(f1, LOW);
  write_digital_pin(g1, LOW);
  }   
 else
 {
  write_digital_pin(a2, LOW);
  write_digital_pin(b2, LOW);
  write_digital_pin(c2, LOW);
  write_digital_pin(d2, LOW);
  write_digital_pin(e2, HIGH);
  write_digital_pin(f2, LOW);
  write_digital_pin(g2, LOW); 
 }
}

void number0(int d)             //Number 0
{
  if (d == 1)
 {
  write_digital_pin(a1, LOW);
  write_digital_pin(b1, LOW);
  write_digital_pin(c1, LOW);
  write_digital_pin(d1, LOW);
  write_digital_pin(e1, LOW);
  write_digital_pin(f1, LOW);
  write_digital_pin(g1, HIGH);
  }   
 else
 {
  write_digital_pin(a2, LOW);
  write_digital_pin(b2, LOW);
  write_digital_pin(c2, LOW);
  write_digital_pin(d2, LOW);
  write_digital_pin(e2, LOW);
  write_digital_pin(f2, LOW);
  write_digital_pin(g2, HIGH);
 }
}


void Display_on(int state)
{
  switch (state) {
    
    case 1: write_digital_pin(D1, HIGH);
            number1(1);
            break;
            
            
    case 2: write_digital_pin(D1, HIGH);
            number2(1);
            break;
    
    case 3: write_digital_pin(D1, HIGH);
            number3(1);
            break;
    
    case 4: write_digital_pin(D1, HIGH);
            number4(1);
            break;
    
    case 5: write_digital_pin(D1, HIGH);
            number5(1);
            break;
    
    case 6: write_digital_pin(D1, HIGH);
            number6(1);
            break;
    
    case 7: write_digital_pin(D1, HIGH);
            number7(1);
            break;
    
    case 8: write_digital_pin(D1, HIGH);
            number8(1);
            break;
    
    case 9: write_digital_pin(D1, HIGH);
            number9(1);
            break;
    
    case 10: write_digital_pin(D1, HIGH);
             number1(1);
             write_digital_pin(D2, HIGH);
             number0(2);
             break;
    
    case 11: write_digital_pin(D1, HIGH);
             number1(1);
             write_digital_pin(D2, HIGH);
             number1(2);
             break;
    
    case 12: write_digital_pin(D1, HIGH);
             number1(1);
             write_digital_pin(D2, HIGH);
             number2(2);
             break;
    
    case 13: write_digital_pin(D1, HIGH);
             number1(1);
             write_digital_pin(D2, HIGH);
             number3(2);
             break;
    
    case 14: write_digital_pin(D1, HIGH);
             number1(1);
             write_digital_pin(D2, HIGH);
             number4(2);
             break;
    
    case 15: write_digital_pin(D1, HIGH);
             number1(1);
             write_digital_pin(D2, HIGH);
             number5(2);
             break;
    
    case 16: write_digital_pin(D1, HIGH);
             number1(1);
             write_digital_pin(D2, HIGH);
             number6(2);
             break;
    
    default: write_digital_pin(D1, HIGH);
             number0(1);
             write_digital_pin(D2, HIGH);
             number0(2);
             break;
  }
}

void Display_off()
{
  write_digital_pin(D1, LOW);
  write_digital_pin(D2, LOW);
  
  write_digital_pin(a1, HIGH);
  write_digital_pin(b1, HIGH);
  write_digital_pin(c1, HIGH);
  write_digital_pin(d1, HIGH);
  write_digital_pin(e1, HIGH);
  write_digital_pin(f1, HIGH);
  write_digital_pin(g1, HIGH);
  
  write_digital_pin(a2, HIGH);
  write_digital_pin(b2, HIGH);
  write_digital_pin(c2, HIGH);
  write_digital_pin(d2, HIGH);
  write_digital_pin(e2, HIGH);
  write_digital_pin(f2, HIGH);
  write_digital_pin(g2, HIGH);

  }

void stateaction(int* val){

    Serial.print("State = ");
    Serial.print(val[0]);
    Display_on(val[0]);
    
    Serial.print(", ");
    Serial.print("Waiting time = ");
    Serial.print(val[1]/1000);
    Serial.print("secs");
    wait_in_millis(val[1]);
    
    Serial.print(", ");
    Serial.print("Watering time = ");
    Serial.print(val[2]/1000);
    Serial.println("secs");
    write_digital_pin(relay_for_pump, HIGH);
    wait_in_millis(val[2]);
    write_digital_pin(relay_for_pump, LOW);
    
    Display_off();
  }

 void Pause()
  {
    write_digital_pin(relay_for_pump, HIGH);
    stay_paused:
                 if (read_digital_pin(21) == HIGH)
                   {
                     Serial.println("Program resumes");
                     return;
                   }
                  else
                  {
                    Serial.println("Program in pause mode");
                    goto stay_paused;
                  }
  }
