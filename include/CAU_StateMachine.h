/*
 * CAU_StateMachine.h
 *
 *  Created on: 01.11.2016
 *      Author: hewe
 */

#ifndef CAU_STATEMACHINE_H_
#define CAU_STATEMACHINE_H_

#include "mbed.h"

#ifndef NULL
#define NULL   ((void *) 0)
#endif


class CAU_StateMachine {
public:
	CAU_StateMachine();
	virtual ~CAU_StateMachine();

	int CAU_StateMachine_ReadStatus();

private:
	mbed::DigitalOut *greenLED;
	mbed::DigitalOut *blueLED;
	mbed::DigitalOut *redLED;
};

#endif /* CAU_STATEMACHINE_H_ */
