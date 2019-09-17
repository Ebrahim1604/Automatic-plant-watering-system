
#define ARDUINO_MAIN
#include "wiring_private.h"
#include "pins_arduino.h"

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
  attachInterrupt(digitalPinToInterrupt(interrupt_pin), Pause, LOW);
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
  digitalWrite(relay, HIGH);
  stay_paused:
               if (digitalRead(interrupt_pin) == HIGH)
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

