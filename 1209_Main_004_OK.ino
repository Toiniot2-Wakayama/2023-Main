#include "pin.h"
#include "motor.h"
#include "sensor.h"
#include "tone.h"

const float pGain = 0.9;
const float dGain = 0.05;
const float iGain = 0.5;
const unsigned short int freq = 1000;
const unsigned short int dirTolerance = 7;

unsigned short int lineValue;

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

  // ========================================

  refreshDir();

  if(dirTolerance <= dir && dir <= 360 - dirTolerance){
    digitalWrite(ledPin[2], 1);

    // P
    float motorPower;
    if(dir > 180){
      motorPower = -1 * (pGain * (dir - 360));
    }
    else{
      motorPower = -1 * (pGain * (dir));
    }

    motor(motorPower, motorPower, motorPower, motorPower);
  }
  
  digitalWrite(ledPin[2], 0);

  // ========================================

  refreshLine();
  
  for(int i=0; i<8; i++){
    Serial.print(line[i]);
    Serial.print("\t");
  }
  lineValue = lineBlock[0]*1000 + lineBlock[1]*100 + lineBlock[2]*10 + lineBlock[3];
  Serial.println(lineValue);
  
  if(lineValue != 0){
    digitalWrite(ledPin[1], 1);
    switch(lineValue){
    case 1111:
      motor(0, 0, 0, 0);
      break;

    case 111:
    case 10:
      motor(100, 100, -100, -100);
      break;

    case 1011:
    case 1:
      motor(-100, 100, 100, -100);
      break;

    case 1101:
    case 1000:
      motor(-100, -100, 100, 100);
      break;

    case 1110:
    case 100:
      motor(100, -100, -100, 100);
      break;

    case 11:
      motor(0, 100, 0, -100);
      break;

    case 1001:
      motor(-100, 0, 100, 0);
      break;

    case 1100:
      motor(0, -100, 0, 100);
      break;

    case 110:
      motor(100, 0, -100, 0);
      break;
    }
    return;
  }

  digitalWrite(ledPin[1], 0);

  // ========================================

  refreshBall8();

  if((ballAngle >= 0 && ballAngle < 22.5) || (ballAngle >= 337.5)){
    motor(100, 100, -100, -100);
  }
  else if(ballAngle >= 22.5 && ballAngle < 67.5){
    motor(-100, 100, 100, -100);
  }
  else if(ballAngle >= 67.5 && ballAngle < 112.5){
    motor(-100, 0, 100, 0);
  }
  else if(ballAngle >= 112.5 && ballAngle < 157.5){
    motor(-100, -100, 100, 100);
  }
  else if(ballAngle >= 157.5 && ballAngle < 202.5){
    motor(0, -100, 0, 100);
  }
  else if(ballAngle >= 202.5 && ballAngle < 247.5){
    motor(-100, -100, 100, 100);
  }
  else if(ballAngle >= 247.5 && ballAngle < 292.5){
    motor(0, -100, 0, 100);
  }
  else if(ballAngle >= 292.5 && ballAngle < 337.5){
    motor(100, -100, -80, 100);
  }
}