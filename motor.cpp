// Arduino Include
#include <Arduino.h>

// Header Include
#include "motor.h"

// Other Include
#include "pin.h"
#include <math.h>

#define P_GAIN 1

int pStep = 10;
bool motorSerial = false;

// PWM Frequency Config
/*
#include <avr/io.h>
void change_freq1(int divide){
  TCCR1B = (TCCR1B & 0b11111000) | divide;
}
*/

// Constant
const float pi = 3.1415926535;
float motorNow[4];

// Function
float m1;
float m2;
float m3;
float m4;

void motor(float m1, float m2, float m3, float m4){
    // Checking Values with Ternary Operator
    m1 = m1>100 ? 100 : m1;
    m1 = m1<-100 ? -100 : m1;
    m1 = abs(m1) < 10 && m1 < -1 ? -10 : m1;
    m1 = abs(m1) < 10 && m1 > 1 ? 10 : m1;
    m1 = abs(m1) <= 1 ? 0 : m1;

    m2 = m2>100 ? 100 : m2;
    m2 = m2<-100 ? -100 : m2;
    m2 = abs(m2) < 10 && m2 < -1 ? -10 : m2;
    m2 = abs(m2) < 10 && m2 > 1 ? 10 : m2;
    m2 = abs(m2) <= 1 ? 0 : m2;

    m3 = m3>100 ? 100 : m3;
    m3 = m3<-100 ? -100 : m3;
    m3 = abs(m3) < 10 && m3 < -1 ? -10 : m3;
    m3 = abs(m3) < 10 && m3 > 1 ? 10 : m3;
    m3 = abs(m3) <= 1 ? 0 : m3;

    m4 = m4>100 ? 100 : m4;
    m4 = m4<-100 ? -100 : m4;
    m4 = abs(m4) < 10 && m4 < -1 ? -10 : m4;
    m4 = abs(m4) < 10 && m4 > 1 ? 10 : m4;
    m4 = abs(m4) <= 1 ? 0 : m4;

    // Output PWM
    analogWrite(motorPin[0][2], (int) fabsf(m1*255*0.01));
    analogWrite(motorPin[1][2], (int) fabsf(m2*255*0.01));
    analogWrite(motorPin[2][2], (int) fabsf(m3*255*0.01));
    analogWrite(motorPin[3][2], (int) fabsf(m4*255*0.01));

    // Output H/L
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

    if(m4 < 0){
        digitalWrite(motorPin[3][0], 0);
        digitalWrite(motorPin[3][1], 1);
    }
    else if(m4 >= 0){
        digitalWrite(motorPin[3][0], 1);
        digitalWrite(motorPin[3][1], 0);
    }

    return;
}

void motorP(int m1G, int m2G, int m3G, int m4G){
  for(int i=0; i<pStep; i++){
    motorNow[0] += (m1G - motorNow[0]) / pStep;
    motorNow[1] += (m2G - motorNow[1]) / pStep;
    motorNow[2] += (m3G - motorNow[2]) / pStep;
    motorNow[3] += (m4G - motorNow[3]) / pStep;
    motor(motorNow[0], motorNow[1], motorNow[2], motorNow[3]);
    if(motorSerial){
      for(int j=0; j<4; j++){
        Serial.print(motorNow[j]);
        Serial.print("\t");
      }
      Serial.println();
    }
  }
}

void motorSetup(int p_step, bool motor_serial){
  pStep = p_step;
  motorSerial = motorSerial;
}