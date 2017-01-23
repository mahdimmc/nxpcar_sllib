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
#include "CAU_SerialSend.h"

/* Create I/O pointer  object */
CAU_SerialSend *CAUSerialSend;

/* Init function */
extern "C" void CAU_SerialSend_Init(int quantToTrnf_) {
	CAUSerialSend = new CAU_SerialSend(quantToTrnf_);
}

/* Accessor function */
extern "C" void CAU_SerialSetData(double *input_) {
	CAUSerialSend->CAU_SerialSetData(input_);
}


/* Terminate function */
extern "C" void CAU_SerialSend_Terminate() {
	delete CAUSerialSend;
}





