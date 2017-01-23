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

#include "FXOS8700.h"
 #include "mbed.h"

FXOS8700::FXOS8700(PinName sda, PinName scl) : accelmagi2c(sda,scl)
 {
    
 }
    
 void FXOS8700::accel_config(int scaleNum)
 {
   char d[2]; 
   
   //Put device in Standby mode
   d[0] = FXOS8700_CTRL_REG1;                     
   d[1] = 0x00; 
   accelmagi2c.write(FXOS8700_I2C_ADDRESS, d,2);  


   // configure acc scale
    d[0] = FXOS8700_XYZ_DATA_CFG;
	switch (scaleNum)
		{
			default:
			case 1: // Writing 00 turns off high-pass filter and sets full scale range to 2g (default mode)
			{
				d[1] = 0x00;
				scaleFactor = 4096;
				break;
			}
			case 2: //for 4g
			{
				d[1] = 0x01;
				scaleFactor = 2048;
				break;
			}
			case 3: //for 8g
			{ 
				d[1] = 0x02;
				scaleFactor = 1024;
				break;
			}
		}
	accelmagi2c.write(FXOS8700_I2C_ADDRESS, d,2);  		
          
		  
   //Put device in Active mode
   d[0] = FXOS8700_CTRL_REG1;                     
   d[1] = 0x01;
   accelmagi2c.write(FXOS8700_I2C_ADDRESS, d, 2);   
      
 }
 
  void FXOS8700::mag_config(void)
 {
   char d[2];
   d[0] = FXOS8700_CTRL_REG1;                     //Puts device in Standby mode
   d[1] = 0x00;
   accelmagi2c.write(FXOS8700_I2C_ADDRESS, d,2);   
          
   
   d[0] = FXOS8700_M_CTRL_REG1;                   //Puts device in hybrid mode (both accel and mag are active)
   d[1] = 0x03;
   accelmagi2c.write(FXOS8700_I2C_ADDRESS, d, 2);   
   

   d[0] = FXOS8700_CTRL_REG1;                     //Puts device in Active mode
   d[1] = 0x01;
   accelmagi2c.write(FXOS8700_I2C_ADDRESS, d,2);  
   
 }
 
 void FXOS8700::acquire_accel_data_g(float * a_data)
 {
  
   char data_bytes[7];
   char d[1];
   d[0]=FXOS8700_STATUS;
   accelmagi2c.write(FXOS8700_I2C_ADDRESS,d,1,true);  // Read the 6 data bytes - LSB and MSB for X, Y and Z Axes.
   accelmagi2c.read(FXOS8700_I2C_ADDRESS,data_bytes,7);
   
   a_data[0] =  ((float)((int16_t)(((data_bytes[1]*256) + (data_bytes[2])))>> 2) * 9.80665 / scaleFactor);
   a_data[1] =  ((float)((int16_t)(((data_bytes[3]*256) + (data_bytes[4])))>> 2) * 9.80665 / scaleFactor);
   a_data[2] =  ((float)((int16_t)(((data_bytes[5]*256) + (data_bytes[6])))>> 2) * 9.80665 / scaleFactor);
   
 }

 void FXOS8700::acquire_mag_data_uT(float * m_data)
 {
  
   char data_bytes[7];
   char d[1];
   d[0]=FXOS8700_MDR_STATUS;
   accelmagi2c.write(FXOS8700_I2C_ADDRESS,d,1,true);  // Read the 6 data bytes - LSB and MSB for X, Y and Z Axes.
   accelmagi2c.read(FXOS8700_I2C_ADDRESS,data_bytes,7);
   
   m_data[0] =  (float)((int16_t)((data_bytes[1]*256) + (data_bytes[2]))) * 0.1;
   m_data[1] =  (float)((int16_t)((data_bytes[3]*256) + (data_bytes[4]))) * 0.1;
   m_data[2] =  (float)((int16_t)((data_bytes[5]*256) + (data_bytes[6]))) * 0.1;
   
 }
     
     