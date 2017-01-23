/*
 * CAUSerialRecv.h
 *
 *  Created on: 01.11.2016
 *      Author: tfuser
 */

#ifndef CAU_SERIALRECV_H_
#define CAU_SERIALRECV_H_

#include "mbed.h"

#ifndef NULL
#define NULL   ((void *) 0)
#endif

class CAU_SerialRecv {
public:
	CAU_SerialRecv(int quantToTrnf_, int fullDigits_, int deciDigits_);
	virtual ~CAU_SerialRecv();

	void serialDataCallback();

	void CAU_SerialGetData(double *results);

private:
	////mbed::Serial *pc;
	//mbed::DigitalOut *greenLED;
	//mbed::DigitalOut *blueLED;
	//mbed::DigitalOut *redLED;
	int quantToTrnf; // quantity to be send
	int fullDigits;
	int deciDigits;
	int bufferLength;
	volatile int startFlag;
	volatile int newCommandFlag;
	volatile int bytesRecieved;
	char startChar;
	char *serialBuffer;
	char *msgPtr;
	float *results;
};

#endif /* CAUSERIALRECV_H_ */
