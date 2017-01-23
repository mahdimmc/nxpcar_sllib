/*
 * Wrappers to make I/O functions available with C linkage. This allows C++
 * methods to be called from C code.
 *
 * Copyright 2014 The MathWorks, Inc. */

#include "CAU_DC_Motor.h"

// total number os possible motors
const uint8_t numMotors = 2;
// CAU_DC_Motor object to represent the Motors
CAU_DC_Motor* motor[numMotors];
// array of motor letters to simplify code extendability
char motorLetter[numMotors] = {'A', 'B'};

extern "C" void CAU_DC_Motor_Init(uint8_t motorNum) {
    motor[motorNum] = new CAU_DC_Motor(motorLetter[motorNum]);
}

extern "C" void CAU_DC_Motor_SetSpeed(uint8_t motorNum, float speed) {
    motor[motorNum]->setSpeed(speed);
}

extern "C" void CAU_DC_Motor_Terminate(uint8_t motorNum) {
    delete motor[motorNum];
}
