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


#include "FXAS21002.h"
 #include "mbed.h"

FXAS21002::FXAS21002(PinName sda, PinName scl) : gyroi2c(sda,scl)
 {
       
 }
    
 void FXAS21002::gyro_config(int scaleNum)
 {
   char d[2];
   d[0] = FXAS21002_CTRL_REG1;                       //Puts device in standby mode
   d[1] = 0x08;
   gyroi2c.write(FXAS21002_I2C_ADDRESS, d,2);   


   d[0] = FXAS21002_CTRL_REG0;                       //sets FS
   switch(scaleNum)
   {
   case '1':
   {
	   d[1] = 0x03; 			//sets FS =+/- 250 dps
	   break;
   }
   case '2':
   {
	   d[1] = 0x02; 			//sets FS =+/- 500 dps
	   break;
   }
   case '3':
   {
	   d[1] = 0x01; 			//sets FS =+/- 1000 dps
	   break;
   }
   default:
   {
	   d[1] = 0x00; 			//sets FS =+/- 2000 dps (default mode)
	   break;
   }
   }
   gyroi2c.write(FXAS21002_I2C_ADDRESS, d, 2);   
           
   
   d[0] = FXAS21002_CTRL_REG1;                       //Puts device in active mode
   d[1] = 0x0A;
   gyroi2c.write(FXAS21002_I2C_ADDRESS, d,2);   
      
 }
 
 void FXAS21002::acquire_gyro_data_dps(float * g_data, int scaleNum)
 {
  
    char data_bytes[7];
   gyroi2c.write(FXAS21002_I2C_ADDRESS,FXAS21002_STATUS,1,true);  // Read the 6 data bytes - LSB and MSB for X, Y and Z Axes.
   gyroi2c.read(FXAS21002_I2C_ADDRESS,data_bytes,7);
   
   float scale_factor=0.0625;

   switch(scaleNum)
   {
   case '1':
   {
	   scale_factor = 0.0078125; 		// FS =+/- 250 dps
	   break;
   }
   case '2':
   {
	   scale_factor = 0.015625; 		// FS =+/- 500 dps
	   break;
   }
   case '3':
   {
	   scale_factor = 0.03125; 			// FS =+/- 1000 dps
	   break;
   }
   default:
   {
	   scale_factor = 0.0625; 			// FS =+/- 2000 dps (default mode)
	   break;
   }
   }



   g_data[0] =  (float)((int16_t)((data_bytes[1]*256) + (data_bytes[2]))) * scale_factor;
   g_data[1] =  (float)((int16_t)((data_bytes[3]*256) + (data_bytes[4]))) * scale_factor;
   g_data[2] =  (float)((int16_t)((data_bytes[5]*256) + (data_bytes[6]))) * scale_factor;
   
 }
