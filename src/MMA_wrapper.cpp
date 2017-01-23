#include "mbed.h"
#include "MMA8451Q.h"

// acc object to represent the Accelerometer
#define MMA8451_I2C_ADDRESS (0x1d<<1)

MMA8451Q* acc;

// init
extern "C" void MW_MMA_Init(int scaleNum) {
    acc = new MMA8451Q(PTE25, PTE24, MMA8451_I2C_ADDRESS, scaleNum);
}


// read
extern "C" float MW_MMA_getAccX() {
    return acc->getAccX();
}
extern "C" float MW_MMA_getAccY() {
    return acc->getAccY();
}
extern "C" float MW_MMA_getAccZ() {
    return acc->getAccZ();
}



// terminate
extern "C" void MW_MMA_Terminate() {
    delete acc;
}
