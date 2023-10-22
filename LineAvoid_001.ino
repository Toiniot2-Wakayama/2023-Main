#include "pin.h"
#include "sensor.h"
#include "motor.h"

// Variables
unsigned short int lineBlock[4];

void setup() {
  pinSetup();
}

void loop() {
  refreshLine();

  // Initialize "lineBlock"
  lineBlock[0] = 0;
  lineBlock[1] = 0;
  lineBlock[2] = 0;
  lineBlock[3] = 0;

  // Get Each Block's Value
  for(i=0; i<22; i++){
    if(i < 4){
      lineBlock[0] += line[i];
    }
    else if(i < 10){
      lineBlock[1] += line[i]
    }
    else if(i < 16){
      lineBlock[2] += line[i]
    }
    else{
      lineBlock[3] += line[i]
    }
  }

  // One Block is detecting
  if(lineBlock[0] > 0){
    motor(-100, -100, 100, 100);
  }
  else if(lineBlock[1] > 0){
    motor(100, -100, -100, 100);
  }
  else if(lineBlock[2] > 0){
    motor(100, 100, -100, -100);
  }
  else if(lineBlock[3] > 0){
    motor(-100, 100, 100, -100);
  }
  // No Block is detecting
  else{
    motor(0, 0, 0, 0);
  }

  delay(10);
}
