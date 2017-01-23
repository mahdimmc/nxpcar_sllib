/*
 * CAU_SerialSend.h
 *
 *  Created on: 01.11.2016
 *      Author: hewe
 */

#ifndef CAU_SERIALSEND_H_
#define CAU_SERIALSEND_H_

#ifndef NULL
#define NULL   ((void *) 0)
#endif


static int MAX_NUMBER_STRING_SIZE = 7;

class CAU_SerialSend {
public:
	CAU_SerialSend(int quantToTrnf_);
	virtual ~CAU_SerialSend();

	void CAU_SerialSetData(double *input_);
    // char * dtoa(char *s, double n);
private:
	int quantToTrnf; 
	char const *delimiter;
	char const *startChar;
	char *serialBuffer;
    char asciiFloat[7]; // MAX_NUMBER_STRING_SIZE
};

#endif /* CAUSERIALSEND_H_ */
