#include "Controller.h"
#include "Score.h"
#include "UserDefine.h"

Controller* Controller::_instance = 0;

Controller* Controller::getInstance(void) {
    if (_instance == 0) {
        _instance = new Controller();
    }

    return _instance;

}

Controller::Controller(void) {
    // netMqtt = CNetMqtt::getInstance();
    // netMqtt.initConnect("PLAYER", COURSE_IP_ADDR);

    position = Position::getInstance(17, 27);
    lineSensor = LineSensor::getInstance(10, 9, 11);

    colorSensor = ColorSensor::getInstance();
    colorSensor->Initialize();
    
    rangingSensor = RangingSensor::getInstance();
    rangingSensor->Initialize();

    twinWheelDriver = TwinWheelDriver::getInstance(13, 19, 5, 6);

    

    score = new Score();
}

Controller::~Controller(void) {
    delete(score);
}

void Controller::reset(void) {
    position->reset();
}

void Controller::getPosition(float* distance, float* angle) {
    position->getPosition(distance, angle);
}


void Controller::changeDriveMode(Mode mode, int voltage_level) {
    twinWheelDriver->changeDriveMode(mode, voltage_level, position);
}

float Controller::getRanging(void) {
  return rangingSensor->getRanging();
}

void Controller::getColorValue(uint16_t* red, uint16_t* green, uint16_t* blue, uint16_t* clear) {
    colorSensor->getColor(red, green, blue, clear);
}

void Controller::getLineValue(bool* left, bool* center, bool* right){
    lineSensor->getLineValue(left, center, right);
}
    

void Controller::getNextScoreTable(int nextScoreTable[4]) {
    char payload[255];

    // メッセージ取得
    netMqtt.getContent(payload,sizeof(payload));

    // メッセージの解析
    score->ParsePayload(payload);

    // スコアの取得とリターン
    score->getNextScoreTable(nextScoreTable);
}

//
int Controller::subscrTopic(void) {
    return netMqtt.subscrTopic("LED-Camp/point");
}

int Controller::dequeueMessage(void) {
    return netMqtt.dequeueMessage(&enMsg);
}
