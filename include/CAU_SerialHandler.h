/*
 * CAU_SerialHandler.h
 *
 *  Created on: 13.12.2016
 *      Author: hewe
 */

#ifndef CAU_SERIALHANDLER_H_
#define CAU_SERIALHANDLER_H_


#ifndef NULL
#define NULL   ((void *) 0)
#endif



class CAU_SerialHandler {
public:
	CAU_SerialHandler();
	virtual ~CAU_SerialHandler();
    static void dtoa(char *s, double n);
    static void atod(float *d, char str[]); // ASCII to double
private:

};

#endif /* CAU_SERIALHANDLER_H_ */
