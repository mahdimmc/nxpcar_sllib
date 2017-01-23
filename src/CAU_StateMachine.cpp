/*
 * CAUSerialSend.cpp
 *
 *  Created on: 09.12.2016
 *      Author: hewe@tf.uni-kiel.de
 */

#include "CAU_StateMachine.h"
// #include "CAU_PinMapping.h"


CAU_StateMachine::CAU_StateMachine() {
    
	greenLED = new DigitalOut(LED_GREEN);
	blueLED = new DigitalOut(LED_BLUE);
	redLED = new DigitalOut(LED_RED);

	// Turn off LEDs
	redLED->write(1);
	blueLED->write(1);
    greenLED->write(1);

}

CAU_StateMachine::~CAU_StateMachine() {
	// TODO Auto-generated destructor stub
}

int CAU_StateMachine::CAU_StateMachine_ReadStatus() {
    //redLED->write(!redLED->read());
    // redLED->write(0);
    return 0;
}

