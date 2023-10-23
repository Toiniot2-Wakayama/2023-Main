#include "pin.h"
#include "sensor.h"
#include "motor.h"
#include "tone.h"

// Variables
unsigned short int lineBlock[4];

void setup() {
  pinSetup();
  Serial.begin(9600);
}

void loop() {
  refreshLine();

  // Initialize "lineBlock"
  lineBlock[0] = 0;
  lineBlock[1] = 0;
  lineBlock[2] = 0;
  lineBlock[3] = 0;

  // Get Each Block's Value
  for(int i=0; i<22; i++){
    if(i < 4 && line[i] == 1){
      lineBlock[0] = 1000;
    }
    else if(i < 10 && line[i] == 1){
      lineBlock[1] = 100;
    }
    else if(i < 16 && line[i] == 1){
      lineBlock[2] = 10;
    }
    else if(line[i] == 1){
      lineBlock[3] = 1;
    }
  }

  if(lineBlock[0] + lineBlock[1] + lineBlock[2] + lineBlock[3] == 1000){
    // Front
    motor(-100, -100, 100, 100);
    tone(bzPin, pitch[0]);
  }
  else if(lineBlock[0] + lineBlock[1] + lineBlock[2] + lineBlock[3] == 1100){
    // Front-Left
    motor(0, -100, 0, 100);
    tone(bzPin, pitch[1]);
  }
  else if(lineBlock[0] + lineBlock[1] + lineBlock[2] + lineBlock[3] == 1010){
    // Front-Back
    motor(0, 0, 0, 0);
    tone(bzPin, pitch[2]);
  }
  else if(lineBlock[0] + lineBlock[1] + lineBlock[2] + lineBlock[3] == 1001){
    // Front-Right
    motor(-100, 0, 100, 0);
    tone(bzPin, pitch[3]);
  }

  else if(lineBlock[0] + lineBlock[1] + lineBlock[2] + lineBlock[3] == 1110){
    // Front-Left-Back
    motor(100, -100, -100, 100);
    tone(bzPin, pitch[4]);
  }
  else if(lineBlock[0] + lineBlock[1] + lineBlock[2] + lineBlock[3] == 1101){
    // Front-Left-Right
    motor(-100, -100, 100, 100);
    tone(bzPin, pitch[5]);
  }
  else if(lineBlock[0] + lineBlock[1] + lineBlock[2] + lineBlock[3] == 1011){
    // Front-Back-Right
    motor(-100, 100, 100, -100);
    tone(bzPin, pitch[6]);
  }
  
  else if(lineBlock[0] + lineBlock[1] + lineBlock[2] + lineBlock[3] == 1111){
    // Front-Left-Back-Right
    motor(0, 0, 0, 0);
    tone(bzPin, pitch[7]);
  }

  else if(lineBlock[0] + lineBlock[1] + lineBlock[2] + lineBlock[3] == 100){
    // Left
    motor(100, -100, -100, 100);
    tone(bzPin, pitch[8]);
  }
  else if(lineBlock[0] + lineBlock[1] + lineBlock[2] + lineBlock[3] == 110){
    // Left-Back
    motor(100, 0, -100, 0);
    tone(bzPin, pitch[9]);
  }
  else if(lineBlock[0] + lineBlock[1] + lineBlock[2] + lineBlock[3] == 101){
    // Left-Right
    motor(0, 0, 0, 0);
    tone(bzPin, pitch[10]);
  }
  else if(lineBlock[0] + lineBlock[1] + lineBlock[2] + lineBlock[3] == 111){
    // Left-Back-Right
    motor(100, 100, -100, -100);
    tone(bzPin, pitch[11]);
  }
  
  else if(lineBlock[0] + lineBlock[1] + lineBlock[2] + lineBlock[3] == 10){
    // Back
    motor(100, 100, -100, -100);
    tone(bzPin, pitch[0]*2);
  }
  else if(lineBlock[0] + lineBlock[1] + lineBlock[2] + lineBlock[3] == 11){
    // Back-Right
    motor(0, 100, 0, -100);
    tone(bzPin, pitch[1]*2);
  }

  else if(lineBlock[0] + lineBlock[1] + lineBlock[2] + lineBlock[3] == 1){
    // Right
    motor(-100, 100, 100, -100);
    tone(bzPin, pitch[2]*2);
  }

  else{
    noTone(bzPin);
  }

  if(digitalRead(btnPin[3]) == 1){
    noTone(bzPin);
  }

  delay(10);
}