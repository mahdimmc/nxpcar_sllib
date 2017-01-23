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
#include "CAU_SerialRecv.h"

/* Create I/O pointer  object */
CAU_SerialRecv *CAUSerialRecv;

/* Init function */
extern "C" void CAU_SerialRecv_Init(int quantToTrnf_, int fullDigits_, int deciDigits_) {
	CAUSerialRecv = new CAU_SerialRecv(quantToTrnf_, fullDigits_, deciDigits_);
}

/* Accessor function */
extern "C" void CAU_SerialGetData(double *results) {
	CAUSerialRecv->CAU_SerialGetData(results);
}


/* Terminate function */
extern "C" void CAU_SerialRecv_Terminate() {
	delete CAUSerialRecv;
}





