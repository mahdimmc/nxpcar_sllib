/*
 * CAU_SerialHandler.cpp
 *
 *  Created on: 13.12.2016
 *      Author: hewe@tf.uni-kiel.de
 */

#include "CAU_SerialHandler.h"
#include "mbed.h"

// This is the only function of this block: create *pc (serial I/O object pointer) pointed to NULL
mbed::Serial *pc = NULL;


CAU_SerialHandler::CAU_SerialHandler() {
   
}

CAU_SerialHandler::~CAU_SerialHandler() {
	
}

// Double to ASCII.
void CAU_SerialHandler::dtoa(char *s, double n) {
    static double PRECISION = 0.001;
    // The inpact on the ROM +11kB size does com from pow and ... i guess
	// handle special cases
	if (isnan(n)) {
		strcpy(s, "nan");
	} else if (isinf(n)) {
		strcpy(s, "inf");
	} else if (n == 0.0) {
		strcpy(s, "+000.00");
	} else {
		int digit, m, m1, zeroPadding;
		char *c = s;
		int neg = (n < 0);
		if (neg)
			n = -n;
		// calculate magnitude
		m = log10(n);
		int useExp = (m >= 3 || (neg && m >= 3) || m <= -3);
		if (neg)
			*(c++) = '-';
		else
			*(c++) = '+';
		// set up for scientific notation
		if (useExp) {
			if (m < 0)
				m -= 1.0;
			n = n / pow(10.0, m);
			m1 = m;
			m = 0;
		}
		if (m < 1.0) {
			m = 0;
		}
		// convert the number
		zeroPadding = 0;
		double weight;
		while (n > PRECISION || m >= 0) {
			weight =  pow(10.0, m);
			if (zeroPadding == 0){ // ZeroPaddingLeft
				if (weight == 1){
					*(c++) = '0';
					*(c++) = '0';
				}
				else if (weight == 10){
					*(c++) = '0';
				}
				zeroPadding = 1;
			}
			if (weight > 0 && !isinf(weight)) {
				digit = floor(n / weight);
				n -= (digit * weight);
				*(c++) = '0' + digit;
			}
			if (m == 0 && n > 0)
				*(c++) = '.';
			m--;
		}
		// ZeroPaddingRight
		if (weight == 1){
			if (*c == '.')
				*(c++) = '.';
			*(c++) = '0';
			*(c++) = '0';
		}
		else if (weight == 0.1){
			*(c++) = '0';
		}

		if (useExp) {
			// convert the exponent
			int i, j;
			c = c - 3;
			*(c++) = 'e';
			if (m1 > 0) {
				*(c++) = '+';
			} else {
				*(c++) = '-';
				m1 = -m1;
			}
			m = 0;
			while (m1 > 0) {
				*(c++) = '0' + m1 % 10;
				m1 /= 10;
				m++;
			}
			c -= m;
			for (i = 0, j = m-1; i<j; i++, j--) {
				// swap without temporary
				c[i] ^= c[j];
				c[j] ^= c[i];
				c[i] ^= c[j];
			}
			c += m;
		}
		*(c) = '\0';
	}
//	return s;
}

// ASCII to double. This function can deal with trash chars in front of the number
void CAU_SerialHandler::atod(float *d, char str[])
{
	float* result = d;
	*result = 0;
	int len = strlen(str);
	int pos = 0, n;
	int offsetSign = 0;
	int sign = 1;
	// Skip all non numeric if its not a minus sign
	while (!(str[offsetSign] >= '0' && str[offsetSign] <= '9')){
		// Get sign
		if(str[offsetSign] == '-'){
			sign = -1;
		}
		offsetSign++;
	}

	for (n = offsetSign; n < len; n++)
	{
		if (str[n] == '.')
		{
			pos = len - n  - 1;
		}
		else
		{
			*result = *result * 10.0f + (str[n]-'0');
		}
	}

	while ( pos--)
	{
		*result = *result/10.0f;
	}
	*result = *result * sign;
}


