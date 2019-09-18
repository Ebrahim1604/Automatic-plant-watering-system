
#define ARDUINO_MAIN
#include "wiring_private.h"
#include "pins_arduino.h"
#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <stdio.h>

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

const int trigger = A3;
const int relay = A8;
const int interrupt_pin = 21;

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



void setup() {
  // put your setup code here, to run once:
  assign_digital_pin(trigger, INPUT);
  assign_digital_pin(relay, OUTPUT);
  Serial.begin(9600);

  write_digital_pin(relay,HIGH);
  pinMode(interrupt_pin, INPUT_PULLUP);
  attach_interrupt_pin(2, Pause, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:

   if(read_digital_pin(trigger)==LOW){
   
      Serial.println("Pumping for 10 secs");
      write_digital_pin(relay,LOW);
      wait_in_millis(10000);
      write_digital_pin(relay,HIGH);

      Serial.println("1 second wait");
      wait_in_millis(1000);

      Serial.println("Pumping for 5 secs");
      write_digital_pin(relay,LOW);
      wait_in_millis(5000);
      write_digital_pin(relay, HIGH);

      Serial.println("1 second wait");
      wait_in_millis(1000);

      Serial.println("Pumping for 2 secs");
      write_digital_pin(relay,LOW);
      wait_in_millis(2000);
      write_digital_pin(relay,HIGH);

      Serial.println("1 second wait");
      wait_in_millis(1000);

    }
} 

void Pause()
{
  write_digital_pin(relay, HIGH);
  stay_paused:
               if (read_digital_pin(interrupt_pin) == HIGH)
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

