// Include Guard
#ifndef SENSOR_H
#define SENSOR_H

// Varibales & Constants
extern float dirValue;
extern unsigned short int lineValue[22];
extern unsigned short int lineThreshold;

// Function
void dirSetup(void);
void refreshDir(void);

void refreshLine(void);
void printLine(void);

#endif