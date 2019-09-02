#include "TwinWheelDriver.h"
#include "Motor.h"
#include "Position.h"
#include "UserDefine.h"
#include <stdio.h>
TwinWheelDriver* TwinWheelDriver::_instance = 0;

TwinWheelDriver* TwinWheelDriver::getInstance(int pin1A, int pin1B, int pin2A,
        int pin2B) {
    if (_instance == 0) {
        _instance = new TwinWheelDriver(pin1A, pin1B, pin2A, pin2B);
    }

    return _instance;

}

TwinWheelDriver::TwinWheelDriver(int pin1A, int pin1B, int pin2A, int pin2B) {
    this->motorL = new Motor(pin1A, pin1B);
    this->motorR = new Motor(pin2A, pin2B);
}

void TwinWheelDriver::changeDriveMode(Mode mode, int voltage_level, Position* position) {
    //voltage_level : 0〜100
    double r = ((double) voltage_level) * R_MOTOR_COFF / 100.0;
    double l = ((double) voltage_level) * L_MOTOR_COFF / 100.0;
    
    if (mode == STOP) {
        motorL->pwmWrite(0.0);
        motorR->pwmWrite(0.0);
        position->setDir(DIR_STOP, DIR_STOP);
    } else if (mode == FORWARD) {
        motorL->pwmWrite(l);
        motorR->pwmWrite(r);
        position->setDir(DIR_FORWARD, DIR_FORWARD);
    } else if (mode == BACKWARD) {
        motorL->pwmWrite(-l);
        motorR->pwmWrite(-r);
        position->setDir(DIR_BACK, DIR_BACK);
    } else if (mode == CW) {
        motorL->pwmWrite(l);
        motorR->pwmWrite(-r);
        position->setDir(DIR_FORWARD, DIR_STOP);
    } else if (mode == CCW) {
        motorL->pwmWrite(-l);
        motorR->pwmWrite(r);
        position->setDir(DIR_STOP, DIR_FORWARD);
    }
}
