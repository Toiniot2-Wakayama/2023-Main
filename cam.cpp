#include <Arduino.h>

#include "cam.h"

#include <Pixy2SPI_SS.h>

void cameraSetup(Pixy2SPI_SS pixy){
  pixy.ccc.getBlocks();
  
  // If there are detect blocks, print them!
  Serial.print("Detected ");
  Serial.println(pixy.ccc.numBlocks);
  for (int i=0; i<pixy.ccc.numBlocks; i++)
  {
    Serial.print("  block ");
    Serial.print(i);
    Serial.print(": ");
    pixy.ccc.blocks[i].print();
    if(0<i)
    {
      Serial.print(":");
    } 
  }
} 
