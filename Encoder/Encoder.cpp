#include "Encoder.h"

Encoder::Encoder(int SW,bool init=false){
  Encoder::setSwitchPin(SW,init);
 };

Encoder::Encoder(int minimum, int maximum, int CLK, int DT,void* interruptHandler){
  Encoder::setRotaryEncoder(minimum, maximum, CLK, DT, interruptHandler);
 };

Encoder::Encoder(int minimum, int maximum, int CLK, int DT, int SW, void* interruptHandler){
  
  Encoder::setRotaryEncoder(minimum, maximum, CLK, DT,interruptHandler);

  Encoder::setSwitchPin(SW);
 };

void Encoder::interruptHandling(){
    unsigned long rotCurrRunTime=millis();

    if((rotCurrRunTime-rotLastRunTime)>5){
    //clockwise mode  
    if (digitalRead(pinDT) == HIGH){ 
      currPos+=stepPos;
    }
    //counter-clockwise mode
    else{                       
      currPos-=stepPos;
    }
    currPos = min(intMax, max(intMin, currPos));
    rotLastRunTime=rotCurrRunTime;
  }
 };

void Encoder::setRotaryEncoder(int minimum, int maximum, int CLK, int DT, void* interruptHandler){
    // Setup Pin connection

    pinCLK=CLK;
    pinDT=DT;

    // To save the number of milliseconds elapsed during the execution 
    // of each encoder object
    
    rotLastRunTime=0;

    // To set minimum and maximum offset limits for each encoder object

    intMin=minimum;
    intMax=maximum;

    // To set step position for each encoder object

    stepPos=1;

    // To save current and previous encoder object position 

    currPos=0;
    prevPos=0;

    // Setup Input Pins of encoder object in Arduino

    pinMode (pinCLK,INPUT);
    pinMode (pinDT,INPUT);

    // Setup interrupts of encoder object in Arduino

    attachInterrupt(digitalPinToInterrupt(pinCLK), interruptHandler, LOW);
 };

void Encoder::setPosition(int value){
  currPos=value;
 };

void Encoder::setStepPosition(int value){
  stepPos=value;
 };

void Encoder::setSwitchPin(int value,bool init=false){
  // Setup Pin connection
  pinSW=value;

  // To save the number of milliseconds elapsed during the execution
  swInitialRunTime=0;

  // To set initial value
  swToggle=init;

  //flow control variable
  swFirstTime=false;
  
  // Setup Input Pin of encoder object
  pinMode (pinSW,INPUT_PULLUP);
 };

void Encoder::setSwitchInit(bool value){
  swToggle=value;
 };

volatile int Encoder::getPosition(){
  if(prevPos!=currPos) prevPos=currPos;
  return currPos;
 };

bool Encoder::getSwitchToggle(){

  if (!digitalRead(pinSW)) 
  { 
    if(!swFirstTime){
      swInitialRunTime=millis();
      swFirstTime=true;
    }
    
    if((millis()-swInitialRunTime<33) && (millis()-swInitialRunTime>30) ){
      swToggle=!swToggle;
      delay(2);
    }
  }
  else{
    swInitialRunTime=0;
    swFirstTime=false;
  }
  return swToggle;
 };