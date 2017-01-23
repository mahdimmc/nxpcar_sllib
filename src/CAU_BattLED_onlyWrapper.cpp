/*
 * Wrappers to make I/O functions available with C linkage. This allows C++
 * methods to be called from C code.
 *
 * ===================================
 * Chair of Automatic Control
 * Christian-Albrechts University Kiel
 * Created on: 15.12.2016
 * Author: hewe@tf.uni-kiel.de
 */

#include "mbed.h"

// total number of LEDs
const uint8_t numBattLEDs = 4;
// PwmOut object to represent the LEDs
DigitalOut* battLED[numBattLEDs];
// array of PinNames to simplify code extendability
PinName battLedPins[numBattLEDs] = {PTB11, PTB10, PTB9, PTB8};

extern "C" void CAU_BattLED_Init(uint8_t ledNum) {
    battLED[ledNum] = new DigitalOut(battLedPins[ledNum]);
    battLED[ledNum]->write(0); //turn it off to start
}

extern "C" void CAU_BattLED_SetValue(uint8_t ledNum, uint8_t ledVal) {
    battLED[ledNum]->write(ledVal);
}

extern "C" uint8_t CAU_BattLED_GetValue(uint8_t ledNum) {
    return battLED[ledNum]->read();
}

extern "C" void CAU_BattLED_Terminate(uint8_t ledNum) {
    delete battLED[ledNum];
}

extern "C" void CAU_BattLEDs_Init() {
    for(uint8_t i = 0; i < numBattLEDs; i++)
    {
        CAU_BattLED_Init(i);
    }
}

extern "C" void CAU_BattLEDs_ShowState(int stateIndex, int errState, int stateSwitchNotice) {
    // Indicate current sate
    if ( errState == 0 ){
        if( stateIndex == 1 ) // idle
        {
            if (stateSwitchNotice)
                CAU_BattLED_SetValue(0, (uint8_t)(CAU_BattLED_GetValue(0) != 1));
            else
                CAU_BattLED_SetValue(0, 1);
            CAU_BattLED_SetValue(1, 0);
            CAU_BattLED_SetValue(2, 0);
        }
        else if( stateIndex == 2 ) // do
        {
            CAU_BattLED_SetValue(0, 0);
            if (stateSwitchNotice)
                CAU_BattLED_SetValue(1, (uint8_t)(CAU_BattLED_GetValue(1) != 1));
            else
                CAU_BattLED_SetValue(1, 1);
            CAU_BattLED_SetValue(2, 0);
        }
        else if( stateIndex == 3 ) // exit
        {
            CAU_BattLED_SetValue(0, 0);
            CAU_BattLED_SetValue(1, 0);
            if (stateSwitchNotice)
                CAU_BattLED_SetValue(2, (uint8_t)(CAU_BattLED_GetValue(2) != 1));
            else
                CAU_BattLED_SetValue(2, 1);
        }
        // indicate running programm by blinking, but only if no other LED is blinking
        if (stateSwitchNotice)
            CAU_BattLED_SetValue(3, 0);
        else
            CAU_BattLED_SetValue(3, (uint8_t)(CAU_BattLED_GetValue(3) != 1)); 
    }
    else { // err: blink all state leds
        int led0 =  CAU_BattLED_GetValue(0);
        int led1 =  CAU_BattLED_GetValue(1);
        int led2 =  CAU_BattLED_GetValue(2);
        int sum = led0 + led1 + led2;
        if (sum==0 || sum==3){ // needed for sync of leds
            CAU_BattLED_SetValue(0, (uint8_t)(led0 != 1));
            CAU_BattLED_SetValue(1, (uint8_t)(led1 != 1));
            CAU_BattLED_SetValue(2, (uint8_t)(led2 != 1));
        }
        else {
            CAU_BattLED_SetValue(0, 0);
            CAU_BattLED_SetValue(1, 0);
            CAU_BattLED_SetValue(2, 0);
        }
        CAU_BattLED_SetValue(3, 0);
    }
}

extern "C" void CAU_BattLEDs_Terminate() {
    for(uint8_t i = 0; i < numBattLEDs; i++)
    {
        CAU_BattLED_Terminate(i);
    }
}
