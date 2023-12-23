#include "pin.h"
#include "motor.h"
#include "sensor.h"
#include "tone.h"

#define BALL_TOLERANCE 6.5

float ballAngleModify = 0;
float ballAngleEdit = 30;

float motorPower[4];

float angle16;
float angle8;

void setup(){
  pinSetup();
  tone(bzPin, soundPitch[9]);
  waitBtn(0);
  noTone(bzPin);
}

void loop(){
  /*
  refreshBall8();
  Serial.print(ballAngle);
  Serial.print("\t");

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

  Serial.println(ballAngle);

  motorPower[0] = sin(radians(ballAngle - 45));
  motorPower[1] = sin(radians(ballAngle - 135));
  motorPower[2] = sin(radians(ballAngle - 225));
  motorPower[3] = sin(radians(ballAngle - 315));

  motor(motorPower[0], motorPower[1], motorPower[2], motorPower[3]);
  */
  /*
  if(digitalRead(btnPin[0]) == HIGH){
    waitBtn(0);
    if(digitalRead(btnPin[2]) == HIGH){
      ballAngleModify += 1;
    }
    else{
      ballAngleModify += 0.1;
    }
  }
  if(digitalRead(btnPin[1]) == HIGH){
    waitBtn(1);
    if(digitalRead(btnPin[2]) == HIGH){
      ballAngleModify -= 1;
    }
    else{
      ballAngleModify -= 0.1;
    }
  }

  Serial.print(ballAngleModify);
  Serial.print("\t");

  refreshBall16();
  angle16 = ballAngle + ballAngleModify;
  Serial.print(angle16);
  Serial.print("\t");

  refreshBall8();
  angle8 = ballAngle + ballAngleModify;
  Serial.print(angle8);
  Serial.print("\t");

  Serial.print(0);
  Serial.print("\t");
  Serial.print(360);
  Serial.print("\t");
  
  Serial.println(abs(angle16 - angle8));
  */

  refreshBallPrint16();
}