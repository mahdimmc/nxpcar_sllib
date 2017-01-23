/*
 *
 * ===================================
 * Chair of Automatic Control
 * Christian-Albrechts University Kiel 
 * Created on: Apr 20, 2016
 * Author: hewe@tf.uni-kiel.de
 *
 */


#include "mbed.h"
#include "TextLCD.h"


// lcd object to represent the TextLCD

TextLCD* lcd;

// init
extern "C" void MW_TextLCD_Init(int scaleNum) {
    lcd = new TextLCD(PTC0, PTC7, PTB8, PTB9, PTB10, PTB11, TextLCD::LCD16x2);			
}


// print to lcd
extern "C" void MW_TextLCD_print(int lineNmbr, float inputNmbr) {
    // lcd->cls();
    if (lineNmbr == 1) {
        lcd->locate(0,0);
    }
    else {
        lcd->locate(0,1);
    }
    lcd->printf("%6.3f", inputNmbr); wait(0.05);
}


// terminate
extern "C" void MW_TextLCD_Terminate() {
    delete lcd;
}
