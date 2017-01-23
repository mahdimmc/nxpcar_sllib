/* 
 * Wrapper to make I/O functions available with C linkage.
 * This allows C++ methods to be called from C code.
 *
 * Copyright 2014 The MathWorks, Inc. */


// Initialize the gyrosensor
void MW_gyro_Init(int scaleNum);

// Get the current gyro in x, y and z axis from the sensor
float MW_gyro_getX(int scaleNum);
float MW_gyro_getY();
float MW_gyro_getZ();

// Free the memory that was dynamically allocated
void MW_gyro_Terminate();
