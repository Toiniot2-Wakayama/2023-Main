// Include
#include "pin.h"
#include "ui.h"
#include "sensor.h"

void setup() {
  pinSetup();
  dirSetup();
  displaySetup();

  drawLogo();
  while(true){
    if(digitalRead(btnPin[1]) == 1){
      while(true){
        if(digitalRead(btnPin[1]) == 0){
          break;
        }
      }
      break;
    }
  }
}

int mode = 0;
bool btnMode = false;

void loop() {
  if(digitalRead(btnPin[0]) == 1 && btnMode == false){
    btnMode = true;
  }
  else if(digitalRead(btnPin[0]) == 0 && btnMode == true){
    btnMode = false;
    mode = mode == 2 ? 0 : mode+1;
  }

  if(mode == 0){
    refreshLinePrint();
    drawLine(lineBlock[0], lineBlock[1], lineBlock[2], lineBlock[3]);
  }
  else if(mode == 1){
    refreshDirPrint();
    drawDir(dir);
  }
  else if(mode == 2){
    refreshBallPrint();
    drawBall(ballAngle);
  }

  if(digitarRead(btnPin[2]) == 1){
    refreshDir();
    dirOpponent = dir;
  }
}