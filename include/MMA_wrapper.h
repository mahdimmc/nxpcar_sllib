/* 
 * Wrapper to make I/O functions available with C linkage.
 * This allows C++ methods to be called from C code.
 *
 * Copyright 2014 The MathWorks, Inc. */

// Initialize the accelerometer
void MW_MMA_Init(int scaleNum);
// Get the current acceleration in x, y and z axis from the sensor
float MW_MMA_getAccX();
float MW_MMA_getAccY();
float MW_MMA_getAccZ();
// Free the memory that was dynamically allocated
void MW_MMA_Terminate();