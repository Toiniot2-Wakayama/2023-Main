#include "pin.h"
#include "sensor.h"
#include "motor.h"

const float pGain = 0.85;
const float dGain = 0.05;
const float iGain = 0.5;
const unsigned short int freq = 1000;
const unsigned short int dirTolerance = 5;

void setup(){
  pinSetup();
  dirSetup();

  digitalWrite(ledPin[0], 1);
  digitalWrite(ledPin[1], 1);

  while(true){
    refreshDirRaw();
    Serial.println(dir);
    if(dir < 9900){
      break;
    }
  }
  digitalWrite(ledPin[1], 0);

  waitBtn(0);
  refreshDirRaw();
  dirOpponent = dir;

  digitalWrite(ledPin[0], 0);
}

void loop(){
  refreshDir();
  Serial.print(dir);

  if((-1 * dirTolerance <= dir & dir <= dirTolerance) == false){
    digitalWrite(ledPin[2], 1);

    // P
    float motorPower;
    motorPower = 0 - (pGain * (dir - 180));
    Serial.print("\t");
    Serial.println(motorPower);

    motor(motorPower, motorPower, motorPower, motorPower);

    return;
  }

  motor(0, 0, 0, 0);
  digitalWrite(ledPin[2], 0);
}