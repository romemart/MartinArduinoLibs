#include <Encoder.h>
#define PWM 5                                 // output signal PWM pin setted 62.5 KHz
#define LED 13                                // output LED pin to test KY-040 Switch 

void encoderInterruptHandler1();              //forward declaration

Encoder e1(0,255,2,4,8,&encoderInterruptHandler1);        //params: minimum, maximum, Clock pin, DT pin, SW pin, nameHandlerFunction

void setup() {
  pinMode(PWM, OUTPUT);                        // define output pin to PWM signal 62.5 KHz 
  pinMode(LED, OUTPUT);                        // define output pin to connect LED
  TCCR0B = TCCR0B & B11111000 | B00000001;     // set timer 0 divisor to 1 for PWM frequency of 62500.00 Hz     
  e1.setPosition(128);                         // 0=0% dutycicle, 128=50% dutycicle, 255=100% dutycicle
  e1.setSwitchInit(HIGH);                      // set initial value in HIGH 
}

void loop() {
  analogWrite(PWM,e1.getPosition());           // update dutycicle 
  digitalWrite(LED,e1.getSwitchToggle());      // update LED status
}

void encoderInterruptHandler1() {
  e1.interruptHandling();
}
