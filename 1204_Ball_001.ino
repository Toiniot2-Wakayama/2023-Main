#include "pin.cpp"
#include "sensor.cpp"
#include "motor.cpp"
#include "ui.cpp"

void setup(){
  pinSetup();
  displaySetup();
}

void loop(){
  // Get BallValue
  refreshBall8();

  if((ballAngle >= 0 && ballAngle < 22.5) || (ballAngle >= 337.5)){
    motor(80, 80, -80, -80);
  }
  else if(ballAngle >= 22.5 && ballAngle < 67.5){
    motor(80, -80, -80, 80);
  }
  else if(ballAngle >= 67.5 && ballAngle < 112.5){
    motor(0, -80, 0, 80);
  }
  else if(ballAngle >= 112.5 && ballAngle < 157.5){
    motor(-80, -80, 80, 80);
  }
  else if(ballAngle >= 157.5 && ballAngle < 202.5){
    motor(0, -80, 0, 80);
  }
  else if(ballAngle >= 202.5 && ballAngle < 247.5){
    motor(-80, -80, 80, 80);
  }
  else if(ballAngle >= 247.5 && ballAngle < 292.5){
    motor(-80, 0, 80, 0);
  }
  else if(ballAngle >= 292.5 && ballAngle < 337.5){
    motor(-80, 80, 80, -80);
  }
}