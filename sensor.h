// Include Guard
#ifndef SENSOR_H
#define SENSOR_H

// Varibales & Constants
extern float dir;
extern unsigned short int line[22];
extern unsigned short int lineThreshold;

// Function
void dirSetup(void);
void refreshDir(void);

void refreshLine(void);
void refreshLinePrint(void);

#endif