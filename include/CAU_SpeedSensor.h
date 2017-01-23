/*
 * CAU_SpeedSensor.h
 *
 * ===================================
 * Chair of Automatic Control
 * Christian-Albrechts University Kiel 
 * Created on: Jan 28, 2016
 * Author: hewe@tf.uni-kiel.de, gefr@tf.uni-kiel.de
 *
 */

#ifndef INCLUDE_CAU_SPEEDSENSOR_H_
#define INCLUDE_CAU_SPEEDSENSOR_H_

#include "mbed.h"

typedef struct SpdSnsrInitPar {
    uint16_t sgmntWdth;     /* segment width between two magnets */
    uint16_t elpsdTMax;     /* maximum elapsed time befor stillstand detection */
    double_t chrTPT1;       /* characteristic time constant of PT1 */
}SpdSnsrInitPar_t;


class CAU_SpeedSensor
{

public:
	// Constructor and Destructor
	CAU_SpeedSensor(SpdSnsrInitPar_t par, int SensorNum_);
	~CAU_SpeedSensor();

	// Accessor methods
	double_t getSpeed();
    uint8_t getStillstand();
	
	// Misc methods
	void calcSpeed();
	void triggerFallAction();
    double_t filterFctn(double_t rawSig_);

private:
    InterruptIn *_INTP;         /* interrrupt pin for edge detection */
	Timer *_timer;              /* pointer to timer object */
    SpdSnsrInitPar_t _par;      /* Paramter struct for initialisation */
    uint32_t _elapsedTime;      /* elapsed time in us measured by interrupt */
	double_t _actualSpeed;      /* actual claculated speed */
    uint8_t _stillstand;        /* flag for stillstand detection 1...stillstand / 0...movement */
    double_t _fltSig;           /* store the last filtered value*/
    double_t _coeff;            /* the filter coeff */
	
};


#endif /* INCLUDE_CAU_SPEEDSENSOR_H_ */
