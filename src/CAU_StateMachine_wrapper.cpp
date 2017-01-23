/*
 *
 * Wrappers to make I/O functions available with C linkage. This allows C++
 * methods to be called from C code.
 *
 * ===================================
 * Chair of Automatic Control
 * Christian-Albrechts University Kiel
 * Created on: Nov 07, 2016
 * Author: hewe@tf.uni-kiel.de
 *
 */

#include "mbed.h"
#include "CAU_StateMachine.h"

/* Create I/O pointer  object */
CAU_StateMachine *CAUStateMachine;

/* Init function */
extern "C" void CAU_StateMachine_Init(int quantToTrnf_, int fullDigits_, int deciDigits_) {
	CAUStateMachine = new CAU_StateMachine();
}

/* Accessor function */
extern "C" int CAU_StateMachine_ReadStatus() {
	return CAUStateMachine->CAU_StateMachine_ReadStatus();
}


/* Terminate function */
extern "C" void CAU_StateMachine_Terminate() {
	delete CAUStateMachine;
}





