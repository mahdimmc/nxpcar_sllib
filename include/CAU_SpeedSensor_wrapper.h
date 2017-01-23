/*
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


/* Initiatlisation function for speed sensor object */
void CAU_SpeedSensor_Init(uint16_T SgmntWdth_, uint16_T ElpsdTMax_, double ChrTPT1_, uint8_T SensorNum_);

/* Accessor function acutal speed */
double CAU_Get_Speed(uint8_T SensorNum_);

/* Accessor function of stillstand detection */
uint8_T CAU_Get_Stillstand(uint8_T SensorNum_);

/* Terminate function of speed sensor object */
void CAU_SpeedSensor_Terminate(uint8_T SensorNum_);