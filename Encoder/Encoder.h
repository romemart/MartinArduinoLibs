#ifndef Encoder_h
#define Encoder_h

#include "Arduino.h"


class Encoder{
 public:
   //Constructors
   Encoder(int SW,bool init=false);
   Encoder(int minimum, int maximum, int CLK, int DT, void* interruptHandler);
   Encoder(int minimum, int maximum, int CLK, int DT, int SW, void* interruptHandler);

   //Setters
   void interruptHandling();
   void setRotaryEncoder(int minimum, int maximum, int CLK, int DT, void* interruptHandler);
   void setPosition(int value);
   void setStepPosition(int value);
   void setSwitchPin(int value,bool init=false);
   void setSwitchInit(bool value);

   //Getters
   volatile int getPosition();
   bool getSwitchToggle();

 private:
   bool swToggle;   //toggle value of the switch HIGH or LOW
   bool swFirstTime;//flow control variable 

   int pinCLK;      //pin CLK is connected
   int pinDT;       //pin DT is connected
   int pinSW;       //pin Sw is connected
   int intMin;      //minimum position rotary shaft 
   int intMax;      //maximum position rotary shaft
   volatile int currPos;     //current position rotary shaft
   int prevPos;     //previous position rotary shaft
   int stepPos;     //presition of each click position (one to one or customed)

   volatile unsigned long rotLastRunTime; //rotary encoder last run time saved
   unsigned long swInitialRunTime; //switch encoder initial run time saved
 };

#endif