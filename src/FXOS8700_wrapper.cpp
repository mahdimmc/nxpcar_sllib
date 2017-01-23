#include "mbed.h"
#include "FXOS8700.h"
#include "CAU_PinMapping.h"

FXOS8700*  accel;
FXOS8700*  mag;

float accel_data[3];
float mag_data[3];

// init
extern "C" void MW_acc_Init(int scaleNum) {
	accel= new FXOS8700(CAU_I2C_SF_SDA, CAU_I2C_SF_SCL);  // SDA, SCL
	mag  = new FXOS8700(CAU_I2C_SF_SDA, CAU_I2C_SF_SCL);  // PTE0, PTE1);   // PTC11,PTC10

	accel->accel_config(scaleNum);
    mag->mag_config();

    wait(0.1);
}


// read
// read accelerometer
extern "C" float MW_accel_getX() {
	accel->acquire_accel_data_g(accel_data);
	return accel_data[0];
}
extern "C" float MW_accel_getY() {
	return accel_data[1];
}
extern "C" float MW_accel_getZ() {
	return accel_data[2];
}

// read magnetude
extern "C" float MW_mag_getX() {
	mag->acquire_mag_data_uT(mag_data);
	return mag_data[0];
}
extern "C" float MW_mag_getY() {
	return mag_data[1];
}
extern "C" float MW_mag_getZ() {
	return mag_data[2];
}


// terminate
extern "C" void MW_acc_Terminate() {
    delete accel;
    delete mag;
}

