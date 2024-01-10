#include "pin.h"
#include "motor.h"
#include "sensor.h"
#include "tone.h"

// Constance for DIR
#define I_DELTA 0.002
#define DIR_TOLERANCE 5

// Constance for BALL
#define BALL_TOLERANCE 10
int BALL_FAR = 750;
#define BALL_NO 250
// #define BALL_MEDIUM 2500

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
float ballAngleMove = 40;
float motorPowerBall[4];
float angle16;
float angle8;

int motorStep = 50;

void setup(){
  pinSetup();
  dirSetup();
  motorSetup(motorStep, false);

  // Get front-direction
  digitalWrite(ledPin[2], 1);
  while(true){
    refreshDirRaw();
    Serial.println(dir);
    if(dir >= 9000){
      tone(bzPin, soundPitch[9]);
    }
    else{
      dirCalibration = true;
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
  if(digitalRead(btnPin[0]) == 1){
    if(digitalRead(btnPin[3]) == 0){
      motorStep += 1;
      motorSetup(motorStep, false);
    }
    else{
      motorStep -= 1;
      motorSetup(motorStep, false);
    }
  }

  if(digitalRead(btnPin[1]) == 1){
    if(digitalRead(btnPin[3]) == 0){
      BALL_FAR += 25;
      motorSetup(motorStep, false);
    }
    else{
      BALL_FAR -= 25;
      motorSetup(motorStep, false);
    }
  }

  //==================================================

  // refreshLine();

  // if(lineBlock[4] > 0){
  //   digitalWrite(ledPin[1], 1);

  //   //lineBlock[4] = Front/Right/Back/Left
  //   switch(lineBlock[4]){
  //   case 1111:
  //   case 1010:
  //   case 101:
  //     motor(0, 0, 0, 0);
  //     break;

  //   case 111:
  //   case 10:
  //     motor(0, 0, 0, 0);
  //     delay(10);
  //     motor(100, 100, -100, -100);
  //     delay(200);
  //     break;

  //   case 1011:
  //   case 1:
  //     motor(0, 0, 0, 0);
  //     delay(10);
  //     motor(-100, 100, 100, -100);
  //     delay(200);
  //     break;

  //   case 1101:
  //   case 1000:
  //     motor(0, 0, 0, 0);
  //     delay(10);
  //     motor(-100, -100, 100, 100);
  //     delay(200);
  //     break;

  //   case 1110:
  //   case 100:
  //     motor(0, 0, 0, 0);
  //     delay(10);
  //     motor(100, -100, -100, 100);
  //     delay(200);
  //     break;
    
  //   default:
  //     motor(0, 0, 0, 0);
  //     break;
  //   }

  //   return;
  // }

  // digitalWrite(ledPin[1], 0);

  //==================================================

  refreshDir();
  currDiff = dir > 180 ? dir - 360 : dir;
  currDiff = dir < -180 ? dir + 360 : dir;
  if((-1 * DIR_TOLERANCE < currDiff && currDiff < DIR_TOLERANCE) == false){
    digitalWrite(ledPin[2], 1);
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

    return;
  }
  digitalWrite(ledPin[2], 0);

  //==================================================

  refreshBall16();

  if(ballSum < BALL_NO){
    // Ball is not existing
    digitalWrite(ledPin[0], 0);
    digitalWrite(ledPin[1], 0);
    noTone(bzPin);
    motorP(0, 0, 0, 0);
    return;
  }
  else{
    tone(bzPin, soundPitch[ballBig]);
  }

  if(ballSum < BALL_FAR){
    // Ball is far from robot
    digitalWrite(ledPin[0], 1);
    digitalWrite(ledPin[1], 0);
    switch(ballBig){
    case 0:
    case 1:
    case 15:
      motorP(100, 100, -100, -100);
      break;

    case 2:
    case 3:
      motorP(0, 100, 0, -100);
      break;

    case 4:
    case 5:
      motorP(-100, 0, 100, 0);
      break;

    case 6:
    case 7:
    case 9:
    case 10:
      motorP(-100, -100, 100, 100);
      break;

    case 8:
      motorP(-100, 100, 100, -100);
      break;

    case 11:
    case 12:
      motorP(0, -100, 0, 100);
      break;

    case 13:
    case 14:
      motorP(100, 0, -100, 0);
      break;
    }
  }
  // else if(ballSum < BALL_MEDIUM){
  //   // Ball is medium-far from robot
  //   digitalWrite(ledPin[0], 0);
  //   digitalWrite(ledPin[1], 1);
  //   switch(ballBig){
  //   case 0:
  //     motorP(100, 100, -100, -100);
  //     break;

  //   case 1:
  //     motorP(100, 90, -100, -90);
  //     break;

  //   case 2:
  //   case 7:
  //   case 8:
  //   case 9:
  //     motorP(-100, 100, 100, -100);
  //     break;

  //   case 3:
  //   case 4:
  //   case 5:
  //     motorP(-100, 0, 100, 0);
  //     break;

  //   case 6:
  //   case 10:
  //     motorP(-100, -100, 100, 100);
  //     break;

  //   case 11:
  //   case 12:
  //   case 13:
  //     motorP(0, -100, 0, 100);
  //     break;

  //   case 14:
  //     motorP(100, -100, -100, 100);
  //     break;

  //   case 15:
  //     motorP(90, 100, -90, -100);
  //     break;
  //   }
  // }
  else{
    // Ball is near from robot
    digitalWrite(ledPin[0], 0);
    digitalWrite(ledPin[1], 1);
    switch(ballBig){
    case 0:
      motorP(100, 100, -100, -100);
      break;

    case 1:
      motorP(100, 80, -100, -80);
      break;

    case 2:
    case 3:
      motorP(-100, 0, 100, 0);
      break;

    case 4:
    case 5:
      motorP(-100, 50, 100, -50);
      break;

    case 6:
    case 10:
      motorP(-100, -100, 100, 100);
      break;

    case 7:
    case 8:
    case 9:
      motorP(-100, 100, 100, -100);
      break;

    case 11:
    case 12:
      motorP(50, -100, -50, 100);
      break;

    case 13:
    case 14:
      motorP(0, -100, 0, 100);
      break;

    case 15:
      motorP(80, 100, -80, -100);
      break;
    }
  }
}