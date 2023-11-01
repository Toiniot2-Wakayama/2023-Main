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
float dirOpponent = 0;

unsigned short int line[22];
unsigned short int lineBlock[5];

unsigned short int ball[16];
float ballX;
float ballY;
float ballAngle;
unsigned short int ballBlock[9];

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

    if (gyro != 3 || mag != 3) {
        // Serial.println("Calibration hasn't finished yet...");
        dir = 9900 + gyro * 10 + mag * 1;
        return;
    }

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
    
    if(line[10] + line[11] + line[12] == 0){
        lineBlock[2] = 0;
    }
    else{
        lineBlock[2] = 1;
    }

    if(line[13] + line[14] + line[15] == 0){
        lineBlock[3] = 0;
    }
    else{
        lineBlock[3] = 1;
    }
    
    if(line[16] + line[17] + line[18] + line[19] + line[20] + line[21] == 0){
        lineBlock[4] = 0;
    }
    else{
        lineBlock[4] = 1;
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
void refreshBall(void) {
    ballX = 0;
    ballY = 0;
    for (int i = 0; i < 16; i++) {
        ball[i] = analogRead(ballPin[i]);
        ballX += cos((45*i)/180*M_PI);
        ballY += sin((45*i)/180*M_PI);
    }
    ballAngle = atan2(ballY, ballX);

    if(ball[0] >= 900){
        ballBlock[0] = 1;
    }
    else{
        ballBlock[0] = 0;
    }

    if(ball[0] + ball[1] + ball[15] >= 2400){
        ballBlock[1] = 1;
    }
    else{
        ballBlock[1] = 0;
    }

    if(ball[1] + ball[2] + ball[3] >= 2400){
        ballBlock[2] = 1;
    }
    else{
        ballBlock[2] = 0;
    }

    if(ball[3] + ball[4] + ball[5] >= 2400){
        ballBlock[3] = 1;
    }
    else{
        ballBlock[3] = 0;
    }

    if(ball[5] + ball[6] + ball[7] >= 2400){
        ballBlock[4] = 1;
    }
    else{
        ballBlock[4] = 0;
    }

    if(ball[7] + ball[8] +  ball[9] >= 2400){
        ballBlock[5] = 1;
    }
    else{
        ballBlock[5] = 0;
    }

    if(ball[9] + ball[10] + ball[11] >= 2400){
        ballBlock[6] = 1;
    }
    else{
        ballBlock[6] = 0;
    }

    if(ball[11] + ball[12] + ball[13] >= 2400){
        ballBlock[7] = 1;
    }
    else{
        ballBlock[7] = 0;
    }
    
    if(ball[13] + ball[14] + ball[15] >= 2400){
        ballBlock[8] = 1;
    }
    else{
        ballBlock[8] = 0;
    }

    return;
}

void refreshBallPrint(void) {
    refreshBall();

    for (int i = 0; i < 16; i++) {
        Serial.print(ball[i] + ",");
    }
    Serial.println();
    return;
}