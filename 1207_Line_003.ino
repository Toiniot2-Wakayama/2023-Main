#include "pin.h"
#include "sensor.h"
#include "motor.h"

void setup() {
  pinSetup();
}

unsigned short int lineValue;

void loop() {
  refreshLine();
  lineValue = lineBlock[0]*1000 + lineBlock[1]*100 + lineBlock[2]*10 + lineBlock[3];
  Serial.println(lineValue);
  
  if(lineValue != 0){
    switch(lineValue){
    case 1111:
      motor(0, 0, 0, 0);
      break;

    case 111:
    case 10:
      motor(70, 70, -70, -70);
      break;

    case 1011:
    case 1:
      motor(-70, 70, 70, -70);
      break;

    case 1101:
    case 1000:
      motor(-70, -70, 70, 70);
      break;

    case 1110:
    case 100:
      motor(70, -70, -70, 70);
      break;

    case 11:
      motor(0, 70, 0, -70);
      break;

    case 1001:
      motor(-70, 0, 70, 0);
      break;

    case 1100:
      motor(0, -70, 0, 70);
      break;

    case 110:
      motor(70, 0, -70, 0);
      break;
    }
    return;
  }

  motor(0, 0, 0, 0);
}
