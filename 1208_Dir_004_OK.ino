#include "pin.h"
#include "sensor.h"
#include "motor.h"
#include "tone.h"

const float pGain = 0.65;
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
  // Switch is Off
  if(digitalRead(btnPin[3]) == 0){
    motor(0, 0, 0, 0);
    tone(bzPin, pitch[9]);
    return;
  }
  else{
    noTone(bzPin);
  }

  // Switch is on
  refreshDir();
  Serial.print(dir);

  if((-1 * dirTolerance <= dir && dir <= dirTolerance) == false){
    digitalWrite(ledPin[2], 1);

    // P
    float motorPower;
    if(dir > 180){
      motorPower = -1 * (pGain * (dir - 360));
    }
    else{
      motorPower = -1 * (pGain * (dir));
    }

    Serial.print("\t");
    Serial.println(motorPower);

    motor(motorPower, motorPower, motorPower, motorPower);

    // PD
    /*
    motorPower = P_GAIN * (dirPrev - dir) - D_GAIN * (dirPrev - dir) / FREQ;
    motor(motorPower, motorPower, motorPower, motorPower);
    diffPrev = dirPrev - dir;
    */

    return;
  }
  
  digitalWrite(ledPin[2], 0);
  motor(0, 0, 0, 0);
}