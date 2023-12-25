#include "pin.h"
#include "motor.h"
#include "sensor.h"
#include "tone.h"

// Constance for DIR
#define I_DELTA 0.002
#define DIR_TOLERANCE 5

// Constance for BALL
#define BALL_TOLERANCE 6.5

// Variables for DIR
float P_GAIN = 1;
float I_GAIN = 1;
float D_GAIN = 1;
float dirP;
float dirI;
float dirD;
float currDiff;
float prevDiff;
float diffDiff;
float diffSum;
float motorPowerDir;

// Variables for BALL
float ballAngleModify = 0;
float ballAngleEdit = 40;
float motorPowerBall[4];
float angle16;
float angle8;


void setup(){
  pinSetup();
  dirSetup();

  // Get front-direction
  digitalWrite(ledPin[2], 1);
  while(true){
    refreshDirRaw();
    Serial.println(dir);
    if(dir >= 9000){
      tone(bzPin, soundPitch[9]);
    }
    else{
      noTone(bzPin);
    }
    if(digitalRead(btnPin[0]) == 1){
      waitBtn(0);
      break;
    }
  }
  digitalWrite(ledPin[2], 0);

  refreshDirRaw();
  dirOpponent = dir;
}


void loop(){
  // Dir Section
  refreshDir();

  currDiff = dir > 180 ? dir - 360 : dir;

  if(digitalRead(btnPin[0]) == 1){
    waitBtn(0);
    if(digitalRead(btnPin[3]) == 0){
      P_GAIN += 0.01;
    }
    else{
      P_GAIN -= 0.01;
    }
  }
  if(digitalRead(btnPin[1]) == 1){
    waitBtn(1);
    if(digitalRead(btnPin[3]) == 0){
      D_GAIN += 0.1;
    }
    else{
      D_GAIN -= 0.1;
    }
  }

  if((-1 * DIR_TOLERANCE < currDiff && currDiff < DIR_TOLERANCE) == false){
    digitalWrite(ledPin[0], 1);
    dirP = currDiff * P_GAIN;
    //dirI = diffSum * I_GAIN;
    dirD = diffDiff * D_GAIN * -1;

    motorPowerDir = (dirP + dirI + dirD) * -1;
    motorPowerDir = motorPowerDir < -100 ? -100 : motorPowerDir;
    motorPowerDir = motorPowerDir > 100 ? 100 : motorPowerDir;

    motor(motorPowerDir, motorPowerDir, motorPowerDir, motorPowerDir);

    diffDiff = abs(currDiff) - abs(prevDiff);
    //diffSum += (prevDiff + currDiff) / 2 * I_DELTA;
    prevDiff = currDiff;

    //return;
  }
  digitalWrite(ledPin[0], 0);

  //==================================================

  refreshLine();

  if(lineBlock[4] > 0){
    digitalWrite(ledPin[1], 1);

    //lineBlock[4] = Front/Right/Back/Left
    switch(lineBlock[4]){
    case 1111:
    case 1010:
    case 101:
      motor(0, 0, 0, 0);
      break;

    case 111:
    case 10:
      motor(100, 100, -100, -100);
      delay(200);
      break;

    case 1011:
    case 1:
      motor(-100, 100, 100, -100);
      delay(200);
      break;

    case 1101:
    case 1000:
      motor(-100, -100, 100, 100);
      delay(200);
      break;

    case 1110:
    case 100:
      motor(100, -100, -100, 100);
      delay(200);
      break;

    default:
      motor(0, 0, 0, 0);
    }

    return;
  }

  digitalWrite(ledPin[1], 0);

  //==================================================

  refreshBall8();

  if((-1 * BALL_TOLERANCE < ballAngle && ballAngle < BALL_TOLERANCE) == false){
    if(ballAngle >= 180){
      ballAngle -= ballAngleEdit;
    }
    else if(ballAngle < 180){
      ballAngle += ballAngleEdit;
    }
  }
  else{
    ballAngle = 0;
  }

  motorPowerBall[0] = 100 * sin(radians(ballAngle - 45)) * -1;
  motorPowerBall[1] = 100 * sin(radians(ballAngle - 135)) * -1;
  motorPowerBall[2] = 100 * sin(radians(ballAngle - 225)) * -1;
  motorPowerBall[3] = 100 * sin(radians(ballAngle - 315)) * -1;

  motor(motorPowerBall[0], motorPowerBall[1], motorPowerBall[2], motorPowerBall[3]);
}