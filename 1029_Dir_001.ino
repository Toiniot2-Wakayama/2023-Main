#include "pin.h"
#include "sensor.h"
#include "ui.h"
#include "motor.h"

#define P_GAIN 1
#define I_GAIN 1
#define D_GAIN 1

void setup() {
  pinSetup();
  dirSetup();
  displaySetup();

  while(true){
    Serial.println("Press A to Set Opponent's Dir...");
    if(digitalRead(btnPin[0]) == 1){
      while(true){
        if(digitalRead(btnPin[0]) == 0){
          refreshDirRaw();
          dirOpponent = dir;
          break;
        }
      }
      break;
    }
  }
}

void loop() {
  refreshDir();
  Serial.println(dir);
  drawDir(dir);
  
  if(dir > 180){
    Serial.println("Turn Right ↺");
  }
  else if(dir <= 180){
    Serial.println("Turn Left ↻");
  }

  // Limit "dir" between -180 to 180
  dir -= 180;
  dir = dir * P_GAIN;
  motor(dir, dir, dir, dir);
}