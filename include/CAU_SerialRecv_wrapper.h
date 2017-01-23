/*
 *
 * ===================================
 * Chair of Automatic Control
 * Christian-Albrechts University Kiel
 * Created on: Nov 07, 2016
 * Author: hewe@tf.uni-kiel.de
 *
*/

/* Init function */
void CAU_SerialRecv_Init(int quantToTrnf_, int fullDigits_, int deciDigits_);

/* Accessor function*/
void CAU_SerialGetData(double *results);

/* Terminate function */
void CAU_SerialRecv_Terminate();
