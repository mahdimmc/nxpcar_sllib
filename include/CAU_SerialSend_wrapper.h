/*
 *
 * ===================================
 * Chair of Automatic Control
 * Christian-Albrechts University Kiel
 * Created on: Nov 07, 2016
 * Author: hewe@tf.uni-kiel.de
 *
*/

#ifndef CAU_SERIALSEND_WRAPPER_H_
#define CAU_SERIALSEND_WRAPPER_H_

/* Init function */
void CAU_SerialSend_Init(int quantToTrnf_);

/* Accessor function*/
void CAU_SerialSetData(double *input_);

/* Terminate function */
void CAU_SerialSend_Terminate();

#endif /* CAUSERIALSEND_WRAPPER_H_ */
