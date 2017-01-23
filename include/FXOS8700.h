 /* Copyright (c) 2015 NXP Semiconductors. MIT License
*
* Permission is hereby granted, free of charge, to any person obtaining a copy of this software
* and associated documentation files (the "Software"), to deal in the Software without
* restriction, including without limitation the rights to use, copy, modify, merge, publish,
* distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all copies or
* substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
* BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
* DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef FXOS8700_H
#define FXOS8700_H
#include "mbed.h"

#define FXOS8700_I2C_ADDRESS (0x1E<<1) //pins SA0,SA1=0

#define FXOS8700_STATUS 0x00
#define FXOS8700_MDR_STATUS 0x32
#define FXOS8700_WHO_AM_I 0x0D
#define FXOS8700_CTRL_REG1 0x2A
#define FXOS8700_XYZ_DATA_CFG 0x0E
#define FXOS8700_M_CTRL_REG1 0x5B
#define FXOS8700_WHO_AM_I_VALUE 0xC7

class FXOS8700
{
    public:
  /**
  * FXOS8700 constructor
  *
  * @param sda SDA pin
  * @param sdl SCL pin
  */
    FXOS8700(PinName sda, PinName scl);
      
	  
   /**
   * Configure acceleration sensor
   *
   * @param scaleNum full scale range selection parameter
   */  
    void accel_config(int scaleNum);
	
   /**
   * Configure magnetometer sensor
   */  
    void mag_config(void);
	
   /**
   * Get acceleration data in g from sensor
   *
   * @param da array where acceleration data will be stored
   */        
    void acquire_accel_data_g(float * da);
    
   /**
   * Get magnetude data in uT from sensor
   *
   * @param dm array where magnetude data will be stored
   */ 
    void acquire_mag_data_uT(float * dm);
    
    private:
    I2C accelmagi2c;		// I2C
	uint16_t scaleFactor; 	// full scale range selection scaling factor
    
};

#endif