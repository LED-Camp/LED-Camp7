#include "Controller.h"
#include "UserDefine.h"

Controller* Controller::_instance = 0;

Controller* Controller::getInstance(void) {
    if (_instance == 0) {
        _instance = new Controller();
    }

    return _instance;

}

Controller::Controller(void) {
    position = Position::getInstance(17, 27);
    lineSensor = LineSensor::getInstance(10, 9, 11);

    colorSensor = ColorSensor::getInstance();
    colorSensor->Initialize();

    rangingSensor = RangingSensor::getInstance();
    rangingSensor->Initialize();

    twinWheelDriver = TwinWheelDriver::getInstance(13, 19, 5, 6);

}

Controller::~Controller(void) {
}

void Controller::positionReset(void) {
    position->reset();
}

void Controller::getPosition(float* distance, float* angle) {
    position->getPosition(distance, angle);
}


void Controller::changeDriveMode(Mode mode, int pwmDuty) {
    twinWheelDriver->changeDriveMode(mode, pwmDuty, position);
}

float Controller::getRanging(void) {
  return rangingSensor->getRanging();
}

void Controller::getColorValue(uint16_t* red, uint16_t* green, uint16_t* blue, uint16_t* clear) {
    colorSensor->getColorValue(red, green, blue, clear);
}
void Controller::getColor(uint16_t red, uint16_t green, uint16_t blue, uint16_t* color){
    colorSensor->getColor(red, green, blue, color);
}

void Controller::detectBlack(bool* left, bool* center, bool* right){
    lineSensor->getLineValue(left, center, right);
}



