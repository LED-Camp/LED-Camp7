#ifndef __CONTROLLER__
#define __CONTROLLER__

#include <cstdint>
#include "CommonDefine.h"
#include "RangingSensor.h"
#include "TwinWheelDriver.h"
#include "Position.h"
#include "CNetMqtt.h"
#include "LineSensor.h"


class Score;

class Controller {
private:
    TwinWheelDriver *twinWheelDriver;
    RangingSensor *rangingSensor;
    CNetMqtt netMqtt;
    LineSensor *lineSensor;
    Score *score;

    enMsgId_t enMsg;

protected:
    Controller(void);
    ~Controller(void);


public:
    static Controller* _instance;

    static Controller* getInstance(void);
    Position *position;
    // Positionån
    void reset(void);
    void getPosition(float* distance, float* angle);

    // twinWheelDriverån
    void changeDriveMode(Mode mode, int voltage_level);
    // LineSensorån
    void getLineValue(bool* left, bool* center, bool* right);
    // RangingSensorån
    float getRanging(void);

    // Courseån
    void getNextScoreTable(int nextScoreTable[4]);
    int subscrTopic(void);
    int dequeueMessage(void);

};

#endif
