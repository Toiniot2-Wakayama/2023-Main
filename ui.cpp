// Arduino Include
#include <Arduino.h>

// Header Include
#include "ui.h"

// Other Include
#include "pin.h"

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <math.h>

// Display Width & Height
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// Other Definitions
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#define NUMFLAKES 10

// Logo
#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16
static const unsigned char PROGMEM logo[] =
{
  0b01111111, 0b10000111,
  0b00111111, 0b11000111,
  0b00011111, 0b11000011,
  0b00011111, 0b11100011,
  0b00011111, 0b11100011,
  0b00011111, 0b11100011,
  0b00001111, 0b11100001,
  0b10001111, 0b11110001,
  0b10001111, 0b11110001,
  0b10000111, 0b11110000,
  0b10000111, 0b11111000,
  0b11000111, 0b11111000,
  0b11000111, 0b11111000,
  0b11000011, 0b11111000,
  0b11100011, 0b11111100,
  0b11100000, 0b11111110
};

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
void displaySetup() {
    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;);
    }

    // Pause 500ms
    delay(500);

    // Clear Display
    display.clearDisplay();

    // Show the display buffer on the screen. You MUST call display() after
    // drawing commands to make them visible on screen!
    display.display();
    delay(500);
}

void drawLogo(void) {
    // Clear Display
    display.clearDisplay();

    // Draw Bitmap of Logo
    display.drawBitmap((display.width() - LOGO_WIDTH) / 2, 0, logo, LOGO_WIDTH, LOGO_HEIGHT, 1);
    
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(15, 30);
    display.println("TOINIOT2");
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.println("\n   Push B to Start");

    display.display();
    delay(10);
}

void drawDir(float angle) {
    // Clear Display
    display.clearDisplay();

    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0,0);
    display.println(angle);

    angle = angle - 90; 
    angle = angle * (M_PI / 180);

    display.drawCircle(display.width()/2, display.height()/2, display.height()/2-2, SSD1306_WHITE);
    display.drawLine(display.width() / 2, display.height() / 2, display.width() / 2 + (display.height() / 2 - 2)*cos(angle), display.height() / 2 + (display.height() / 2 - 2)*sin(angle), SSD1306_WHITE);

    // Update Displaying
    display.display();

    delay(10);
}

void drawLine(int front, int left, int back, int right) {
    // Clear Display
    display.clearDisplay();

    if (front == 1) {
        display.fillRect(59, 0, 10, 25, SSD1306_WHITE);
    }
    else {
      display.drawRect(59, 0, 10, 25, SSD1306_WHITE);
    }

    if (left == 1) {
        display.fillRect(27, 27, 30, 10, SSD1306_WHITE);
    }
    else {
        display.drawRect(27, 27, 30, 10, SSD1306_WHITE);
    }

    if (back == 1) {
        display.fillRect(59, 39, 10, 25, SSD1306_WHITE);
    }
    else {
        display.drawRect(59, 39, 10, 25, SSD1306_WHITE);
    }

    if (right == 1) {
        display.fillRect(71, 27, 30, 10, SSD1306_WHITE);
    }
    else {
        display.drawRect(71, 27, 30, 10, SSD1306_WHITE);
    }


    // Update Displaying
    display.display();

    delay(10);
}

void drawBall(float angle) {
    // Clear Display
    display.clearDisplay();

    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0,0);
    display.println(angle);

    angle = angle - 90; 
    angle = angle * (M_PI / 180);

    display.drawCircle(display.width()/2, display.height()/2, display.height()/2-2, SSD1306_WHITE);
    display.drawLine(display.width() / 2, display.height() / 2, display.width() / 2 + (display.height() / 2 - 2)*cos(angle), display.height() / 2 + (display.height() / 2 - 2)*sin(angle), SSD1306_WHITE);

    // Update Displaying
    display.display();

    delay(10);
}

void drawPD(float p, float d){
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(p);
  display.println(d);
  display.display();
}