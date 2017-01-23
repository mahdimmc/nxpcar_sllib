#ifndef CAU_DC_MOTOR_H
#define CAU_DC_MOTOR_H

#include "mbed.h"

class CAU_DC_Motor
{

public:
    // Constructor and Destructor
    ~CAU_DC_Motor();
    CAU_DC_Motor(char motorLetter);
    
    // initialize pwm signals to 240us period and 0% duty cycle
    void initMotorInput(PwmOut* motorIn);
    
    // accessor methods
    void  setSpeed(float speed);    // Set the speed of the motor (-1 to 1)
    float getSpeed();               // Get the speed of the motor

    void enableHbridge();           // Enable BOTH motors to run
    void disableHbridge();          // Disable BOTH motors from running

    /**  Shorthand for the accessor methods */
    CAU_DC_Motor& operator= (float speed);
    CAU_DC_Motor& operator= (CAU_DC_Motor& rhs);
    operator float();

private:
    // PwmOut object which drive the motor
    PwmOut* motorIn1;            // PWM signal to drive the H-Bridge In1
    PwmOut* motorIn2;            // PWM signal to drive the H-Bridge In2
    static DigitalOut hBridgeEN; // GPIO pin to enable/disable the H-Bridge
};

#endif