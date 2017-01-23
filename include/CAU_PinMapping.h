/*
 * CAU_PinMapping.h
 *
 *  Created on: 01.12.2016
 *      Author: hewe
 */

#ifndef CAU_PIN_MAPPING_H_
#define CAU_PIN_MAPPING_H_

#include "mbed.h"

extern mbed::Serial *pc;


/*Bluetooth modul connection*/
#define CAU_BT_TX PTA2
#define CAU_BT_RX PTA1

/*Speedsensor connection left & right*/
#define CAU_SPEED_L PTA12
#define CAU_SPEED_R PTD4

/*SensorFusionBoard I2C */
#define CAU_I2C_SF_SDA PTE0
#define CAU_I2C_SF_SCL PTE1

#endif /* CAU_PIN_MAPPING_H_ */
