/* 
 * Wrapper to make I/O functions available with C linkage.
 * This allows C++ methods to be called from C code.
 *
 * Copyright 2014 The MathWorks, Inc. */


// Initialize the accelerometer
void MW_acc_Init(int scaleNum);

// Get the current acceleration in x, y and z axis from the sensor
float MW_accel_getX();
float MW_accel_getY();
float MW_accel_getZ();
// Get the current mag in x, y and z axis from the sensor
float MW_mag_getX();
float MW_mag_getY();
float MW_mag_getZ();

// Free the memory that was dynamically allocated
void MW_acc_Terminate();
