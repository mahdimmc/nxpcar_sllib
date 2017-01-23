/*
 *
 * Wrappers to make I/O functions available with C linkage. This allows C++
 * methods to be called from C code.
 *
 * ===================================
 * Chair of Automatic Control
 * Christian-Albrechts University Kiel
 * Created on: Dec 13, 2016
 * Author: hewe@tf.uni-kiel.de
 *
 */

#include "CAU_SerialHandler.h"

/* Create I/O pointer  object */
CAU_SerialHandler *CAUSerialHandler;

/* Init function */
extern "C" void CAU_SerialHandler_Init() {
	CAUSerialHandler = new CAU_SerialHandler();
}

/* Terminate function */
extern "C" void CAU_SerialHandler_Terminate() {
	delete CAUSerialHandler;
}





