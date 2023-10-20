// Arduino Include
#include <Arduino.h>

// Header Include
#include "line.hpp"

// Other Include
#include "pin.hpp"

// Variable
unsigned short int line[22];

// Function
// Get SensorValue
void getLine(void) {
  for(int i=0; i<22; i++){
    line[i] = digitalRead(linePin[i]);
  }
}

void getLinePrint(void) {
  getLine();

  for(int i=0; i<22; i++){
    Serial.print(line[i] + ",");
  }
  Serial.println();
}