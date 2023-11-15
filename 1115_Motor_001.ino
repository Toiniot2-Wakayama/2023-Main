#include "pin.h"
#include "motor.h"

void setup(){
  pinSetup();
}

void loop(){
  motor(50, 50, 50, 50);
}