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
/*
void  move(float angle, int power) {
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
*/

/*
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
*/

void motor(float m1, float m2, float m3, float m4){
  m1 = m1>100 ? 100 : m1;
  m1 = m1<-100 ? -100 : m1;
  m2 = m2>100 ? 100 : m2;
  m2 = m2<-100 ? -100 : m2;
  m3 = m3>100 ? 100 : m3;
  m3 = m3<-100 ? -100 : m3;
  m4 = m4>100 ? 100 : m4;
  m4 = m4<-100 ? -100 : m4;

  analogWrite(motorPin[0][2], fabsf(0.01*m1*256));
  analogWrite(motorPin[1][2], fabsf(0.01*m2*256));
  analogWrite(motorPin[2][2], fabsf(0.01*m3*256));
  analogWrite(motorPin[3][2], fabsf(0.01*m4*256));

  if(m1 < 0){
      digitalWrite(motorPin[0][0], 0);
      digitalWrite(motorPin[0][1], 1);
  }
  else if(m1 >= 0){
      digitalWrite(motorPin[0][0], 1);
      digitalWrite(motorPin[0][1], 0);
  }

  if(m2 < 0){
      digitalWrite(motorPin[1][0], 0);
      digitalWrite(motorPin[1][1], 1);
  }
  else if(m2 >= 0){
      digitalWrite(motorPin[1][0], 1);
      digitalWrite(motorPin[1][1], 0);
  }

  if(m3 < 0){
      digitalWrite(motorPin[2][0], 0);
      digitalWrite(motorPin[2][1], 1);
  }
  else if(m3 >= 0){
      digitalWrite(motorPin[2][0], 1);
      digitalWrite(motorPin[2][1], 0);
  }

  if(m1 < 4){
      digitalWrite(motorPin[3][0], 0);
      digitalWrite(motorPin[3][1], 1);
  }
  else if(m4 >= 0){
      digitalWrite(motorPin[3][0], 1);
      digitalWrite(motorPin[3][1], 0);
  }
}