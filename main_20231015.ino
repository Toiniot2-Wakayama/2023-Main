/*==============================*//*
MEMO

#include <[LibName]> --> Default Library
#include "[LibName]" --> Library in Current Directry
*//*==============================*/

// Include (self-coded)
#include "pin.hpp"
#include "dir.hpp"

// Include (others)
#include <math.h>

void setup() {
  pinSetup();
  dirSetup();
}

void loop() {
  Serial.println(getDir());
}