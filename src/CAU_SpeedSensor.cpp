/*
 * CAU_SpeedSensor.cpp
 *
 * ===================================
 * Chair of Automatic Control
 * Christian-Albrechts University Kiel
 * Created on: Jan 28, 2016
 * Updated: 07.12.2016
 * Author: hewe@tf.uni-kiel.de, gefr@tf.uni-kiel.de
 *
 */


#include "CAU_SpeedSensor.h"
#include "CAU_PinMapping.h"

// Constructor and Destructor
CAU_SpeedSensor::CAU_SpeedSensor(SpdSnsrInitPar_t par_, int SensorNum_){
    
    this->_timer = new Timer();
    // Init private members
    this->_actualSpeed = 0u;
    this->_elapsedTime = 0u;
    this->_par = par_;
    this->_stillstand = 1u;
    this->_fltSig = 0u;
    
    /* Calculate discrete filter coefficient */
    if(0u < this->_par.chrTPT1)
    {
        // old implementation: this->_coeff = exp(-(double_t)(this->_par.smplT) / (double_t)(this->_par.chrTPT1));
        this->_coeff = exp(-this->_par.chrTPT1);
    }
    else
    {
        this->_coeff = 0.0;
    }
    
    // Bindings
    switch (SensorNum_){
        case 0: //left sensor
            this->_INTP = new InterruptIn(CAU_SPEED_L);
            break;
        case 1: // right sensor
            this->_INTP = new InterruptIn(CAU_SPEED_R);
            break;
    }
    this->_INTP->fall(this, &CAU_SpeedSensor::triggerFallAction); // Bind the interrupt action
}

CAU_SpeedSensor::~CAU_SpeedSensor() {
    
}

// Accessor method for acutal calculated speed */
double_t CAU_SpeedSensor::getSpeed() {
    this->calcSpeed();
    return this->_actualSpeed;
}

/* Accessor method for stillstand detection flag */
uint8_t CAU_SpeedSensor::getStillstand() {
    return this->_stillstand;
}


void CAU_SpeedSensor::calcSpeed() {
    if((0 < this->_elapsedTime) && (0u == this->_stillstand))
    {
        /* Calculate speed signal in m/s
         * Speed = delta travel in mm from one magnet to the next divided by the elapsed time in us */
        this->_actualSpeed = (double_t)(this->_par.sgmntWdth*1000u) / (double_t)this->_elapsedTime;
        
        /* PT1 Filter for speed signal when characteristic time is defined, meaing > 0 */
        if(0u < this->_par.chrTPT1)
        {
            this->_actualSpeed = this->filterFctn(this->_actualSpeed);
        }
    }
    
    if (this->_timer->read_ms() > this->_par.elpsdTMax )
    {
        this->_actualSpeed = 0u;
        this->_elapsedTime = 0u;
        this->_stillstand = 1u;
        
        // take control of the timer
        this->_timer->reset();
        this->_timer->stop();
    }
}


void CAU_SpeedSensor::triggerFallAction() {
    if(0u == this->_stillstand)
    {
        this->_elapsedTime = this->_timer->read_us();
    }
    else
    {
        this->_elapsedTime = 0u;
    }
    // take control of the timer
    this->_timer->reset();
    this->_timer->stop();
    this->_timer->start();
    
    this->_stillstand = 0u;
}


double_t CAU_SpeedSensor::filterFctn(double_t rawSig_)
{
    /* Update filtered signal */
    this->_fltSig = this->_coeff*this->_fltSig + (1-this->_coeff)*rawSig_;
    return this->_fltSig;
}
