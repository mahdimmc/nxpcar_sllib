/*
 * CAUSerialRecv.cpp
 *                //if (strcmp(std::to_string(pc->getc()), startChar)){
 *               //if (pc->getc() == atoi(startChar)){
 *  Created on: 01.11.2016
 *      Author: hewe@tf.uni-kiel.de
 */

#include "CAU_SerialRecv.h"
#include "CAU_SerialHandler.h"
#include "CAU_PinMapping.h"
#include "MW_target_hardware_resources.h" //Needed for Simulinks UART configuration
#include <string>
// #include <cstdlib>



CAU_SerialRecv::CAU_SerialRecv(int quantToTrnf_, int fullDigits_, int deciDigits_) {
    
    //delimiter = " "; // Whitespace
    startChar = '>';
    
    if (pc == NULL){
        pc = new Serial(CAU_BT_TX, CAU_BT_RX);
        pc->baud(MW_UART0_BAUDRATE); //Set the baudrate for the connection KL25Z-BTModul
    }
    
    msgPtr = NULL;
    //greenLED = new DigitalOut(LED_GREEN);
    //blueLED = new DigitalOut(LED_BLUE);
    //redLED = new DigitalOut(LED_RED);
    quantToTrnf = quantToTrnf_;
    fullDigits = fullDigits_;
    deciDigits = deciDigits_;
    int const extraChars = 3; // start/delimiter + decimal dot + sign
    
    int const oneNumLength = (extraChars + fullDigits + deciDigits);
    bufferLength = quantToTrnf * oneNumLength;
    serialBuffer = (char *) malloc(bufferLength * sizeof(char));
    results = (float *) calloc(quantToTrnf, sizeof(float));
    bytesRecieved = 0;
    newCommandFlag = 0;
    startFlag = 0;
    
    //Turn off LEDs
    //redLED->write(1);
    //blueLED->write(1);
    //greenLED->write(1);
    
    pc->attach(this, &CAU_SerialRecv::serialDataCallback);
}

CAU_SerialRecv::~CAU_SerialRecv() {
    // TODO Auto-generated destructor stub
}

void CAU_SerialRecv::CAU_SerialGetData(double *results_) {
    
    for (int i = 0; i < quantToTrnf; i++) {
        results_[i] = (double) results[i];
    }
}

void CAU_SerialRecv::serialDataCallback() {
    while (pc->readable()) {
        if (newCommandFlag) { // avoid buffer overflow
            pc->getc();
        } else {
            if (startFlag == 0) {
                if (pc->getc() == startChar){
                    startFlag = 1;
                }
            } else {
                serialBuffer[bytesRecieved] = pc->getc(); // get waiting data
                bytesRecieved++;
                // redLED->write(!redLED->read());
                if (bytesRecieved == bufferLength-1) { // buffer full; message complete
                    // greenLED->write(!greenLED->read());
                    serialBuffer[bytesRecieved] = 0;
                    newCommandFlag = true;
                    // iterate through the buffer, seperator is a whitespace
					for (int i = 0; i < quantToTrnf; i++) {
						if (i == 0) {
							msgPtr = strtok(serialBuffer," ");
						} else {
							msgPtr = strtok(NULL, " ");
						}
                        CAU_SerialHandler::atod(&results[i], msgPtr);
					}
                    newCommandFlag = false;
                    bytesRecieved = 0;
                    startFlag = 0;
                }
            }
        }
    }
}

