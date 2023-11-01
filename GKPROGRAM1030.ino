#include "pin.h"
#include "sensor.h"
#include "ui.h"
#include "motor.h"
#include "linegk.h"







void setup() {

  pinSetup();
  Serial.begin(9600);
  // put your setup code here, to run once:
}

void loop() {

  refreshLine();
  decideLine();
  refreshBall();


  //moving forward
  if(ballBlock[0] == 1){
      motor(100, 100, 100, 100);
  }
  
  //ball is front stopping
  else if(ballBlock[1] == 1){
      motor(100, 100, 100, 100);
  }

  //left slow
  else if(ballBlock[2] == 1){
      motor(100, 100, 100, 100);
  }

  //left fast
  else if(ballBlock[3] == 1){
      motor(100, 100, 100, 100);
  }

  //left slow
  else if(ballBlock[4] == 1){
      motor(100, 100, 100, 100);
  }

  //ball is back stopping
  else if(ballBlock[5] == 1){
      motor(100, 100, 100, 100);
  }

  //right slow
  else if(ballBlock[6] == 1){
      motor(100, 100, 100, 100);
  }

  //right fast
  else if(ballBlock[7] == 1){
      motor(100, 100, 100, 100);
  }

  //right slow
  else if(ballBlock[8] == 1){
      motor(100, 100, 100, 100);
  }





  

  

  

  

  



  // put your main code here, to run repeatedly:

}
