#include <stdio.h>
#include "LineSensor.h"
#include <wiringPi.h>

/*******************************************/
LineSensor* LineSensor::_instance = 0;

LineSensor::LineSensor(int pinLeft, int pinCenter, int pinRight) {
    wiringPiSetupGpio();
    pinMode(pinLeft,INPUT);
    pinMode(pinCenter,INPUT);
    pinMode(pinRight,INPUT);
    this->pinLeft = pinLeft;
    this->pinCenter = pinCenter;
    this->pinRight = pinRight;
}

LineSensor* LineSensor::getInstance(int pinLeft, int pinCenter, int pinRight){
    if (_instance == 0) {
        _instance = new LineSensor(pinLeft, pinCenter, pinRight);
    }
    return _instance;
}

void LineSensor::getLineValue(bool* left, bool* center, bool* right){
    *left = digitalRead(this->pinLeft);
    *center = digitalRead(this->pinCenter);
    *right = digitalRead(this->pinRight);
}
