#include <Encoder.h>
#define PWM1 5
#define PWM2 6

void encoderInterruptHandler1(); //forward declaration
void encoderInterruptHandler2(); //forward declaration

Encoder e1(0,255,2,4,&encoderInterruptHandler1);        //params: minimum, maximum, Clock pin, DT pin, nameHandlerFunction
Encoder e2(0,255,3,7,&encoderInterruptHandler2);        //params: minimum, maximum, Clock pin, DT pin, nameHandlerFunction

void setup() {
  pinMode(PWM1, OUTPUT);
  pinMode(PWM2, OUTPUT); 
  TCCR0B = TCCR0B & B11111000 | B00000001;     // set timer 0 divisor to 1 for PWM frequency of 62500.00 Hz     
  e1.setPosition(128);                         // 0=0% dutycycle, 128=50% dutycicle, 255=100% dutycicle
  e2.setPosition(128);                         // 0=0% dutycycle, 128=50% dutycicle, 255=100% dutycicle
}

void loop() {
  analogWrite(PWM1,e1.getPosition());         // update dutycycle PWM1 output pin
  analogWrite(PWM2,e2.getPosition());         // update dutycycle PWM2 output pin
}

void encoderInterruptHandler1() {             // interrupt attending for encoder1
  e1.interruptHandling();
}

void encoderInterruptHandler2() {             // interrupt attending for encoder2
  e2.interruptHandling();
}
