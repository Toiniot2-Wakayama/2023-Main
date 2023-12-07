// Arduino Include
#include <Arduino.h>

// Main Include
#include "sensor.h"
#include "pin.h"

// Other Include
#include <math.h>

// Include for DirSensor
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

// DirSensor
#define BNO055_SAMPLERATE_DELAY_MS (100)
Adafruit_BNO055 bno = Adafruit_BNO055(-1, 0x28, &Wire);

// Variable
float dir;
float dirPrev;
float dirOpponent;

unsigned short int line[22];
unsigned short int lineBlock[4];

unsigned short int ball[16];
float ballX;
float ballY;
float ballAngle;

// Function
// Dir ==============================================
void dirSetup(void) {
    if (!bno.begin())
    {
        Serial.println("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
        while (1);
    }
    bno.setExtCrystalUse(true);
    Serial.println("BNO055 Connected Successfully!");

    return;
}

void refreshDirRaw(void) {
    // Calibration Check
    uint8_t system, gyro, accel, mag = 0;
    bno.getCalibration(&system, &gyro, &accel, &mag);

    /*
    if (gyro != 3 || mag != 3) {
        // Serial.println("Calibration hasn't finished yet...");
        dir = 9900 + gyro * 10 + mag * 1;
        return;
    }
    */

    // Euler Angle
    imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
    imu::Quaternion quat = bno.getQuat();

    /*
    // Quarternion Angle (Needed to be calculated into YAW angle)
    Serial.print("qW: ");
    Serial.print(quat.w(), 4);
    Serial.print(" qX: ");
    Serial.print(quat.x(), 4);
    Serial.print(" qY: ");
    Serial.print(quat.y(), 4);
    Serial.print(" qZ: ");
    Serial.print(quat.z(), 4);
    Serial.print("\t\t");
    */

    // Refresh Value
    dirPrev= dir;
    dir = euler.x();
    return;
}

void refreshDir(void) {
    refreshDirRaw();
    dir -= dirOpponent;
    dir = dir < 0 ? dir+360 : dir;
    dir = dir > 360 ? dir-360 : dir;
    return;
}

// Line =============================================
void refreshLine(void) {
    for (int i=0; i<22; i++) {
        line[i] = digitalRead(linePin[i]);
    }

    if(line[0] + line[1] + line[2] + line[3] == 0){
        lineBlock[0] = 0;
    }
    else{
        lineBlock[0] = 1;
    }
    
    if(line[4] + line[5] + line[6] + line[7] + line[8] + line[9] == 0){
        lineBlock[1] = 0;
    }
    else{
        lineBlock[1] = 1;
    }
    
    if(line[10] + line[11] + line[12] + line[13] + line[14] + line[15] == 0){
        lineBlock[2] = 0;
    }
    else{
        lineBlock[2] = 1;
    }
    
    if(line[16] + line[17] + line[18] + line[19] + line[20] + line[21] == 0){
        lineBlock[3] = 0;
    }
    else{
        lineBlock[3] = 1;
    }
    return;
}

void refreshLinePrint(void) {
    refreshLine();

    for (int i = 0; i < 22; i++) {
        Serial.print(line[i]);
        Serial.print(",");
    }
    Serial.println();
    return;
}

// Ball =============================================
void refreshBall8(void) {
    ballX = 0;
    ballY = 0;
    for (int i = 0; i < 4; i++) {
        ball[i*2] = 1023 - analogRead(ballPin[i*4]);
        ballX += ball[i*4] * cos(radians(45*i*4 + 90));
        ballY += ball[i*4] * sin(radians(45*i*4 + 90));
    }
    ballAngle = degrees(atan2(ballY, ballX));
    return;
}

void refreshBall16(void) {
    ballX = 0;
    ballY = 0;
    for (int i = 0; i < 16; i++) {
        ball[i] = analogRead(ballPin[i]);
        ballX += cos((45*i)/180*M_PI);
        ballY += sin((45*i)/180*M_PI);
    }
    ballAngle = degrees(atan2(ballY, ballX));
    return;
}

void refreshBallPrint8(void) {
    refreshBall8();

    for (int i = 0; i < 8; i++) {
        Serial.print(ball[i] + ",");
    }
    Serial.println();
    return;
}

void refreshBallPrint16(void) {
    refreshBall16();

    for (int i = 0; i < 16; i++) {
        Serial.print(ball[i] + ",");
    }
    Serial.println();
    return;
}