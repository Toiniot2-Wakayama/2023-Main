#include <Arduino.h>

// Main Include
#include "sensor.h"
#include "pin.h"

// Include for DirSensor
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

// DirSensor
#define BNO055_SAMPLERATE_DELAY_MS (100)
Adafruit_BNO055 bno = Adafruit_BNO055(-1, 0x28, &Wire);

// Variable
float dirValue;
unsigned short int line[22];
unsigned short int lineThreshold = 2;
unsigned short int ball[16];

// Function
// Dir ==============================================
void dirSetup(void) {
    if (!bno.begin())
    {
        Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
        while (1);
    }
    bno.setExtCrystalUse(true);

    return;
}

void refreshDir(void) {
    // Calibration Check
    uint8_t system, gyro, accel, mag = 0;
    bno.getCalibration(&system, &gyro, &accel, &mag);

    if (gyro != 3 || mag != 3) {
        Serial.println("Calibration hasn't finished yet...");
        dir = 9999999900 + gyro * 10 + mag * 1;
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

// Line =============================================
void refreshLine(void) {
    for (int i = 0; i < 22; i++) {
        line[i] = digitalRead(linePin[i]);
    }
    return;
}

void refreshLinePrint(void) {
    refreshLine();

    for (int i = 0; i < 22; i++) {
        Serial.print(line[i] + ",");
    }
    Serial.println();
    return;
}

void refreshLineThreshold(int refreshValue) {
    lineThreshold += refreshValue;
    return;
}

// Ball =============================================
void refreshBall(void) {
    for (int i = 0; i < 16; i++) {
        ball[i] = analogRead(ballPin[i]);
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