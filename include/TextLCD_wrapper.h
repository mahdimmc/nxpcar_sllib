/*
 * Wrappers to make I/O functions available with C linkage. This allows C++
 * methods to be called from C code.
 *
 * ===================================
 * Chair of Automatic Control
 * Christian-Albrechts University Kiel
 * Created on: Apr 20, 2016
 * Author: hewe@tf.uni-kiel.de
 *
 */

// Initialize the TextLCD
void MW_TextLCD_Init();
// Print char* on TextLCD
void MW_TextLCD_print(int lineNmbr, float inputNmbr);
// Free the memory that was dynamically allocated
void MW_TextLCD_Terminate();