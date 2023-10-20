// Main Include
#include "pin.hpp"
#include "line.hpp"
#include "dir.hpp"
#include "motor.hpp"

#include "tone.hpp"

// Other Include
#include <math.h>

// Variables
bool defenceFlag;
float opponentDir;
float dirDif;

// Setup
void setup() {
  pinSetup();
  dirSetup();

  for(int i=0; i<20; i++){
    digitalWrite(ledPin[0], 1);
    delay(50);
    digitalWrite(ledPin[0], 0);
    delay(50);
  }

  // Wait for Push of ButtonA
  while(true){
    if(digitalRead(btnPin[0]) == 1){
      digitalWrite(ledPin[0], 0);
      break;
    }
    digitalWrite(ledPin[0], 1);
    getDir();
    Serial.println(dir);
    delay(10);
  }
  while(true){
    if(digitalRead(btnPin[0]) == 0){
      // Direction of Opponent
      getDir();
      opponentDir = dir;
      Serial.println();
      Serial.println(opponentDir);
      Serial.println();
      if(opponentDir > 180){
        opponentDir -= 360;
      }
      else if(opponentDir < -180){
        opponentDir += 360;
      }

      digitalWrite(ledPin[0], 1);
      digitalWrite(ledPin[1], 1);
      digitalWrite(ledPin[2], 1);
      Serial.println("3");
      tone(bzPin, pitch[9]);
      delay(500);
      noTone(bzPin);
      delay(500);
      Serial.println("2");
      digitalWrite(ledPin[2], 0);
      tone(bzPin, pitch[9]);
      delay(500);
      noTone(bzPin);
      delay(500);
      Serial.println("1");
      digitalWrite(ledPin[1], 0);
      tone(bzPin, pitch[9]);
      delay(500);
      noTone(bzPin);
      delay(500);
      digitalWrite(ledPin[0], 0);
      Serial.println("Let's Go!");
      tone(bzPin, pitch[9]*2);
      delay(500);
      noTone(bzPin);
      delay(500);
      break;
    }
    delay(10);
    digitalWrite(ledPin[0], 0);
  }

  // Offence or Defence
  defenceFlag = digitalRead(btnPin[3]) == 0 ? true : false;
}

// Loop
void loop() {
  // Dir ==============================================
  getDir();
  dir = dir > 180 ? dir-360: dir;
  dir = dir < -180 ? dir+360: dir;
  dirDif = (opponentDir-dir)>180 ? opponentDir-dir-360: opponentDir-dir;
  dirDif = (opponentDir-dir)<-180 ? opponentDir-dir+360: opponentDir-dir;

  /*
  Serial.print(180);
  Serial.print(",");
  Serial.print(-180);
  Serial.print(",");
  Serial.print(opponentDir);
  Serial.print(",");
  Serial.print(dir);
  Serial.print(",");
  Serial.println(dirDif);
  */

  //motor(dirDif, 100);

  // Line =============================================
  //getLine();
  /*
  if(line[0] == 1){
    Serial.print("↓");
  }
  if(line[4] == 1){
    Serial.print("→");
  }
  if(line[10] == 1){
    Serial.print("↑");
  }
  if(line[16] == 1){
    Serial.print("←");
  }
  Serial.println();
  */

  // Ball =============================================

}