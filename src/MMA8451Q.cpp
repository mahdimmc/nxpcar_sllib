/* Copyright (c) 2010-2011 mbed.org, MIT License
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

#include "MMA8451Q.h"

#define REG_WHO_AM_I      0x0D
#define REG_CTRL_REG_1    0x2A
#define REG_XYZ_DATA_CFG  0x0E
#define REG_OUT_X_MSB     0x01
#define REG_OUT_Y_MSB     0x03
#define REG_OUT_Z_MSB     0x05

#define UINT14_MAX        16383u

MMA8451Q::MMA8451Q(PinName sda, PinName scl, int addr, int scaleNum) : m_i2c(sda, scl), m_addr(addr) {
    // activate the peripheral

    // Puts acc in standby for configuring
    uint8_t data[2] = {REG_CTRL_REG_1, 0x00}; 
    writeRegs(data, 2);
    
    // configure acc scale
    data[0] = REG_XYZ_DATA_CFG;
    switch (scaleNum)
    {
        default:
        case 1: // Writing 00 turns off high-pass filter and sets full scale range to 2g (default mode)
        {
            data[1] = 0x00;
            scaleFactor = 4096;
            break;
        }
        case 2: //for 4g
        {
            data[1] = 0x01;
            scaleFactor = 2048;
            break;
        }
        case 3: //for 8g
        { 
            data[1] = 0x02;
            scaleFactor = 1024;
            break;
        }
    }
    writeRegs(data, 2);
    
    // activate the peripheral
    data[0] = REG_CTRL_REG_1;
    data[1] = 0x01;
    writeRegs(data, 2);
}

MMA8451Q::~MMA8451Q() { }

uint8_t MMA8451Q::getWhoAmI() {
    uint8_t who_am_i = 0;
    readRegs(REG_WHO_AM_I, &who_am_i, 1);
    return who_am_i;
}

float MMA8451Q::getAccX() {
    //divide by scaleFactor that accelorometer output value is formatted to g (gravity)
    return (float(getAccAxis(REG_OUT_X_MSB))*9.80665/scaleFactor);
}

float MMA8451Q::getAccY() {
    return (float(getAccAxis(REG_OUT_Y_MSB))*9.80665/scaleFactor); //4096.0
}

float MMA8451Q::getAccZ() {
    return (float(getAccAxis(REG_OUT_Z_MSB))*9.80665/scaleFactor);
}

void MMA8451Q::getAccAllAxis(float * res) {
    res[0] = getAccX();
    res[1] = getAccY();
    res[2] = getAccZ();
}

int16_t MMA8451Q::getAccAxis(uint8_t addr) {
    int16_t acc;
    uint8_t res[2];
    readRegs(addr, res, 2);

    acc = (res[0] << 6) | (res[1] >> 2);
    if (acc > UINT14_MAX/2)
        acc -= UINT14_MAX;
    
   // acc = (res[0]*256u) | (res[1] >> 0);
   // acc = acc/4u;


    return acc;
}

void MMA8451Q::readRegs(int addr, uint8_t * data, int len) {
    char t[1] = {addr};
    m_i2c.write(m_addr, t, 1, true);
    m_i2c.read(m_addr, (char *)data, len);
}

void MMA8451Q::writeRegs(uint8_t * data, int len) {
    m_i2c.write(m_addr, (char *)data, len);
}
