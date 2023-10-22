// Arduino Include
#include <Arduino.h>

// Header Include
#include "tone.hpp"

// Other Include
#include "pin.hpp"

// Constant
const float pitch[12] = {
  261.626,  // 0: C
  277.183,  // 1: C#
  293.665,  // 2: D
  311.327,  // 3: D#
  329.628,  // 4: E
  349.228,  // 5: F
  369.994,  // 6: F#
  391.995,  // 7: G
  415.305,  // 8: G#
  440.000,  // 9: A
  466.164,  // 10: A#
  493.883,  // 11: B
};

// Function
void playSound(int type){
  switch(type){
  case 0:
    tone(bzPin, pitch[6]);
    delay(300);
    tone(bzPin, pitch[2]);
    delay(300);
    tone(bzPin, pitch[9]/2);
    delay(300);
    tone(bzPin, pitch[2]);
    delay(300);
    tone(bzPin, pitch[4]);
    delay(300);
    tone(bzPin, pitch[9]);
    delay(300);
    noTone(bzPin);
    delay(300);
    tone(bzPin, pitch[9]/2);
    delay(300);
    tone(bzPin, pitch[4]);
    delay(300);
    tone(bzPin, pitch[6]);
    delay(300);
    tone(bzPin, pitch[4]);
    delay(300);
    tone(bzPin, pitch[9]/2);
    delay(300);
    tone(bzPin, pitch[2]);
    delay(600);
    noTone(bzPin);
    delay(600);
    break;

  case 1:
    tone(bzPin, pitch[11]*3);
    break;

  case 2:
    break;

  case 3:
    break;
  }
}