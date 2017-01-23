/*
 * speedSensor_wrapper.cpp
 *
 * Wrappers to make I/O functions available with C linkage. This allows C++
 * methods to be called from C code.
 *
 * ===================================
 * Chair of Automatic Control
 * Christian-Albrechts University Kiel
 * Created on: Jan 27, 2016
 * Author: hewe@tf.uni-kiel.de, gefr@tf.uni-kiel.de
 *
 */

#include "mbed.h"
#include "CAU_SpeedSensor.h"

// total number of simulatanious instances
const uint8_t number = 2;
/* Create pointer to speed sensor object */
CAU_SpeedSensor* speedSensor[number];

/* Initiatlisation function for speed sensor object */
extern "C" void CAU_SpeedSensor_Init(uint16_t SgmntWdth_, uint16_t ElpsdTMax_, double_t ChrTPT1_, uint8_t SensorNum_) {
    SpdSnsrInitPar_t InitPar;
        
    InitPar.sgmntWdth = SgmntWdth_;     /* Segement width of circle between two magnets */
    InitPar.elpsdTMax = ElpsdTMax_;     /* Maximum elapsed time for stillstand detection */
    InitPar.chrTPT1   = ChrTPT1_;       /* Characteristic time of PT1 filter in respect to the sample time of the simulink block */
	
    /* Creation of speed sensor instance and initialisation*/
    speedSensor[SensorNum_] = new CAU_SpeedSensor(InitPar, SensorNum_);
}

/* Accessor function acutal speed */
extern "C" double_t CAU_Get_Speed(uint8_t SensorNum_) {
    return speedSensor[SensorNum_]->getSpeed();
}

/* Accessor function of stillstand detection */
extern "C" uint8_t CAU_Get_Stillstand(uint8_t SensorNum_) {
    return speedSensor[SensorNum_]->getStillstand();
}


/* Terminate function of speed sensor object */
extern "C" void CAU_SpeedSensor_Terminate(uint8_t SensorNum_) {
	delete speedSensor[SensorNum_];
}





