#include "mbed.h"
#include "FXAS21002.h"
#include "CAU_PinMapping.h"

FXAS21002* gyro;

float gyro_data[3];

// init
extern "C" void MW_gyro_Init(int scaleNum) {
	gyro = new FXAS21002(CAU_I2C_SF_SDA, CAU_I2C_SF_SCL);  
	gyro->gyro_config(scaleNum);
    wait(0.1);
}
extern "C" float MW_gyro_getX(int scaleNum) {
	gyro->acquire_gyro_data_dps(gyro_data, scaleNum);
	return gyro_data[0];
}
extern "C" float MW_gyro_getY() {
	return gyro_data[1];
}
extern "C" float MW_gyro_getZ() {
	return gyro_data[2];
}
// terminate
extern "C" void MW_gyro_Terminate() {
    delete gyro;
}

