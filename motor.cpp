// Arduino Include
#include <Arduino.h>

// Header Include
#include "motor.hpp"

// Other Include
#include "pin.hpp"
#include <math.h>

// Constant
const float pi = 3.1415926535;

// Function
void motor(float angle, int power) {
  float motor_out_value[4];
  int motor_out[4][3];

  angle = (angle+45) / 180 * pi;
  power = power > 100 ? 100 : power;
  power = power < 0 ? 0 : power;

  motor_out_value[0] = sin(angle)*power;
  motor_out_value[1] = cos(angle)*power;
  motor_out_value[2] = sin(angle)*power*(-1);
  motor_out_value[3] = cos(angle)*power*(-1);

  // MotorIn Set
  for(int i=0; i<4; i++){
    if(motor_out_value[i] > 0){
      motor_out[i][0] = 1;
      motor_out[i][1] = 0;
    }
    else if(motor_out_value[i] < 0){
      motor_out[i][0] = 0;
      motor_out[i][1] = 1;
    }
    else{
      motor_out[i][0] = 1;
      motor_out[i][1] = 1;
    }
  }

  //MotorPWM Set
  for(int i=0; i<4; i++){
    motor_out[i][2] = fabsf(0.01*motor_out_value[i]*256);
  }

  // Pin Output
  for(int i=0; i<4; i++){
    for(int j=0; j<2; j++){
      digitalWrite(motorPin[i][j], motor_out[i][j]);
    }
    analogWrite(motorPin[i][2], motor_out[i][2]);
  }
}

void turn(bool reverse, int power){
  float motor_out_value[4];
  int motor_out[4][3];
  
  //MotorPWM Set
  for(int i=0; i<4; i++){
    motor_out[i][2] = fabsf(0.01*power*256);
  }

  for(int i=0; i<4; i++){
    if(reverse == true){
      motor_out[i][0] = 0;
      motor_out[i][1] = 1;
    }
    else{
      motor_out[i][0] = 1;
      motor_out[i][1] = 0;
    }
  }

  // Pin Output
  for(int i=0; i<4; i++){
    for(int j=0; j<2; j++){
      digitalWrite(motorPin[i][j], motor_out[i][j]);
    }
    analogWrite(motorPin[i][2], motor_out[i][2]);
  }
}