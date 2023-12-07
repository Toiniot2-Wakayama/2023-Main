// Include Guard
#ifndef SENSOR_H
#define SENSOR_H

// Varibales & Constants
extern float dir;
extern float dirPrev;
extern float dirOpponent;
extern unsigned short int line[22];
extern unsigned short int lineBlock[4];
extern unsigned short int ball[16];
extern float ballX;
extern float ballY;
extern float ballAngle;

// Function
void dirSetup(void);
void refreshDirRaw(void);
void refreshDir(void);

void refreshLine(void);
void refreshLinePrint(void);

void refreshBall8(void);
void refreshBall16(void);
void refreshBallPrint8(void);
void refreshBallPrint16(void);

#endif