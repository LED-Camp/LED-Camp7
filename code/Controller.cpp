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
#ifdef EXPERIMENTAL_USE
    netMqtt = CNetMqtt::getInstance();
    netMqtt.initConnect("PLAYER", COURSE_IP_ADDR);
#endif
    position = Position::getInstance(17, 27);

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

