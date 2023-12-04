#include "pin.h"
#include "sensor.h"
#include "motor.h"
#include "ui.h"

void setup(){
  pinSetup();
  displaySetup();
}

void loop(){
  // Get LineValue
  refreshLine();
  drawLine(lineBlock[0], lineBlock[1], lineBlock[2], lineBlock[3]);

  if((lineBlock[0]*1000 + lineBlock[1]*100 + lineBlock[2]*10 + lineBlock[3] == 0) == false){
    switch(lineBlock[0]*1000 + lineBlock[1]*100 + lineBlock[2]*10 + lineBlock[3]){
      // Stop
      case 1111:
        motor(0, 0, 0, 0);
        break;

      // Go Front
      case 111:
      case 10:
        motor(70, 70, -70, -70);
        break;

      // Go Left
      case 1011:
      case 1:
        motor(-70, 70, 70, -70);
        break;

      // Go Back
      case 1101:
      case 1000:
        motor(-70, -70, 70, 70);
        break;

      // Go Right
      case 1110:
      case 100:
        motor(70, -70, -70, 70);
        break;

      // Go Front-left
      case 11:
        motor(0, 70, 0, -70);
        break;

      // Go Left-back
      case 1001:
        motor(-70, 0, 70, 0);
        break;

      // Go Back-right
      case 1100:
        motor(0, -70, 0, 70);
        break;

      // Go Right-front
      case 110:
        motor(70, 0, -70, 0);
        break;
      

      // Default(Error Values)
      default:
        motor(0, 0, 0, 0);
        break;
    }
    return;
  }

  // Stop moving
  motor(0, 0, 0, 0);
}