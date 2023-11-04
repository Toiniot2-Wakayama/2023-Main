#include "pin.h"
#include "sensor.h"
#include "ui.h"
#include "camera.h"

// Uncomment to use each communication type...
Pixy2 pixy;
// Pixy2SPI_SS pixy;
// Pixy2I2C pixy;

void setup() {
  pinSetup();
  displaySetup();
  cameraSetup(pixy);
}

void loop() {
  pixy.ccc.getBlocks();

  for (int i=0; i<pixy.ccc.numBlocks; i++)
  {
    Serial.print(pixy.ccc.blocks[i].m_x);
    Serial.print(",");
    Serial.print(pixy.ccc.blocks[i].m_y);
    Serial.print(",");
    Serial.print(pixy.ccc.blocks[i].m_width);
    Serial.print(",");
    Serial.print(pixy.ccc.blocks[i].m_height);
    Serial.print(",");
    Serial.println(pixy.ccc.blocks[i].m_signature);

    drawCamera(pixy.ccc.blocks[i].m_x, pixy.ccc.blocks[i].m_y, pixy.ccc.blocks[i].m_width, pixy.ccc.blocks[i].m_height);
  }
}