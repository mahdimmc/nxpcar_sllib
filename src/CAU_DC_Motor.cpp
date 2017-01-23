#include "CAU_DC_Motor.h"
#include "mbed.h"

DigitalOut CAU_DC_Motor::hBridgeEN(PTE21);

CAU_DC_Motor::~CAU_DC_Motor() {
    disableHbridge();
    delete this->motorIn1;
    delete this->motorIn2;
}

CAU_DC_Motor::CAU_DC_Motor(char motorLetter) {
    disableHbridge();

    switch( motorLetter ) {
        default:
            break;

        case 'A':
            this->motorIn1 = new PwmOut(PTC3);
            this->motorIn2 = new PwmOut(PTC4);

            break;

        case 'B':
            this->motorIn1 = new PwmOut(PTC1);
            this->motorIn2 = new PwmOut(PTC2);

            break;
    }
    
    initMotorInput(this->motorIn1);
    initMotorInput(this->motorIn2);
    enableHbridge();
}

void CAU_DC_Motor::initMotorInput(PwmOut* motorIn) {
    motorIn->period_us(240);
    motorIn->write(0.0);
}

void CAU_DC_Motor::setSpeed(float speed) {
    if(speed > 1.0)
        speed = 1.0;
    else if(speed < -1.0)
        speed = -1.0;

    if(speed >= 0) {
        *(this->motorIn1) = speed;
        *(this->motorIn2) = 0.0;
    } else if(speed < 0) {
        *(this->motorIn1) = 0.0;
        *(this->motorIn2) = -speed;
    }
}

void CAU_DC_Motor::disableHbridge() {
    this->hBridgeEN = false;
}

void CAU_DC_Motor::enableHbridge() {
    this->hBridgeEN = true;
}

float CAU_DC_Motor::getSpeed() {

    return this->motorIn1->read() - this->motorIn2->read();
}
    
CAU_DC_Motor& CAU_DC_Motor::operator= (float speed) { 
    setSpeed(speed);
    return *this;
}

CAU_DC_Motor& CAU_DC_Motor::operator= (CAU_DC_Motor& rhs) {
    setSpeed(rhs.getSpeed());
    return *this;
}

CAU_DC_Motor::operator float() {
    return getSpeed();
}
