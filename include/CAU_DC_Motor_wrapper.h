/* 
 * Wrappers to make I/O functions available with C linkage. This allows C++
 * methods to be called from C code.
 *
 * Copyright 2014 The MathWorks, Inc. */

// Initialize the DC Motor
void CAU_DC_Motor_Init(uint8_T motorNum);
// Set the speed of the chosen DC Motor (-1 to 1)
void CAU_DC_Motor_SetSpeed(uint8_T motorNum, float speed);
// Release dynamically allocated memory
void CAU_DC_Motor_Terminate(uint8_T motorNum);
