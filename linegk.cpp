// Arduino Include
#include <Arduino.h>

// Main Include
#include "linegk.h"
#include "sensor.h"


// Other Include
#include <math.h>






unsigned short int lineMove;



// Function

// Line =============================================
void decideLine(void) {

    

    if(lineBlock[0] == 1 && lineBlock[1] == 0 && lineBlock[2] == 0 && lineBlock[3] == 0 && lineBlock[4] == 0){
        lineMove = 0;
    }

    if(lineBlock[0] == 0 && lineBlock[1] == 1 && lineBlock[2] == 0 && lineBlock[3] == 0 && lineBlock[4] == 0){
        lineMove = 1;
    }

    if(lineBlock[0] == 0 && lineBlock[1] == 0 && lineBlock[2] == 1 && lineBlock[3] == 0 && lineBlock[4] == 0){
        lineMove = 2;
    }

    if(lineBlock[0] == 0 && lineBlock[1] == 0 && lineBlock[2] == 0 && lineBlock[3] == 1 && lineBlock[4] == 0){
        lineMove = 3;
    }

    if(lineBlock[0] == 0 && lineBlock[1] == 0 && lineBlock[2] == 0 && lineBlock[3] == 0 && lineBlock[4] == 1){
        lineMove = 4;
    }

    if(lineBlock[0] == 0 && lineBlock[1] == 1 && lineBlock[2] == 0 && lineBlock[3] == 0 && lineBlock[4] == 0){
        lineMove = 5;
    }

    if(lineBlock[0] == 0 && lineBlock[1] == 1 && lineBlock[2] == 0 && lineBlock[3] == 0 && lineBlock[4] == 0){
        lineMove = 6;
    }
    return;


    
}




