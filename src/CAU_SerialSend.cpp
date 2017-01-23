/*
 * CAUSerialSend.cpp
 *
 *  Created on: 01.11.2016
 *      Author: hewe@tf.uni-kiel.de
 */

#include "CAU_SerialSend.h"
#include "CAU_SerialHandler.h"
#include "CAU_PinMapping.h"
#include "MW_target_hardware_resources.h" //Needed for Simulinks UART configuration
#include <string>
#include <math.h>
#include "mbed.h"



CAU_SerialSend::CAU_SerialSend(int quantToTrnf_) {
	delimiter = ";";
	startChar = ">";
    
    if (pc == NULL){
        pc = new Serial(CAU_BT_TX, CAU_BT_RX); 
        pc->baud(MW_UART0_BAUDRATE); 
    }
	    
	quantToTrnf = quantToTrnf_;
    
    // As dtoa() is configured in this way, you should not alter theese
	int const fullDigits = 3;
	int const deciDigits = 2;
    int const extraChars = 3; // start/delimiter + decimal dot + sign
    
    int const oneNumLength = (extraChars + fullDigits + deciDigits);
	int const bufferLength = quantToTrnf * oneNumLength;
	serialBuffer = (char *) malloc(bufferLength * sizeof(char));
    
    
	// greenLED = new DigitalOut(LED_GREEN);
	// blueLED = new DigitalOut(LED_BLUE);
	// redLED = new DigitalOut(LED_RED);
	// Turn off LEDs
	//redLED->write(1);
	//blueLED->write(1);
}

CAU_SerialSend::~CAU_SerialSend() {
	// TODO Auto-generated destructor stub
}

void CAU_SerialSend::CAU_SerialSetData(double *input_) {
    // redLED->write(!redLED->read());
    
    // Format the transfer string
    strcpy(serialBuffer, startChar); 
    for (int i=0; i<quantToTrnf; i++){
        if (i>0){
             strcpy(serialBuffer + strlen(serialBuffer), delimiter); 
        }
        CAU_SerialHandler::dtoa(asciiFloat, input_[i]);
        strcpy(serialBuffer + strlen(serialBuffer), asciiFloat);
    }
   pc->printf("%s\r", serialBuffer);
}



