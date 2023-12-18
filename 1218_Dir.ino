#include "pin.h"
#include "sensor.h"
#include "motor.h"
#include "tone.h"

#define P_GAIN 0.9
#define I_GAIN 0.2
#define D_GAIN 2.5

#define I_DELTA 0.002

#define DIR_TOLERANCE 10

float dirP;
float dirI;
float dirD;

float currDiff;
float prevDiff;
float diffDiff;
float diffSum;

float motorPower;

void setup() {
  pinSetup();
  dirSetup();

  digitalWrite(ledPin[0], 1);
  tone(bzPin, pitch[9]);
  waitBtn(0);
  digitalWrite(ledPin[0], 0);
  noTone(bzPin);

  refreshDirRaw();
  dirOpponent = dir;
}

void loop() {
  refreshDir();

  currDiff = dir > 180 ? dir - 360 : dir;

  dirP = currDiff * P_GAIN;
  //dirI = diffSum * I_GAIN;
  dirD = diffDiff * D_GAIN * -1;

  motorPower = (dirP + dirI + dirD) * -1;

  Serial.print("currDiff: ");
  Serial.print(currDiff);
  Serial.print("\tdirP: ");
  Serial.print(dirP);
  //.print("\tdirI: ");
  //Serial.print(dirI);
  Serial.print("\tdirD: ");
  Serial.print(dirD);
  Serial.print("\tmotorPower: ");
  Serial.println(motorPower);

  diffDiff = abs(currDiff) - abs(prevDiff);
  //diffSum += (prevDiff + currDiff) / 2 * I_DELTA;
  prevDiff = currDiff;
}