#ifndef __CONTROLLER__
#define __CONTROLLER__

#include <cstdint>
#include "CommonDefine.h"
#include "RangingSensor.h"
#include "TwinWheelDriver.h"
#include "Position.h"
#include "CNetMqtt.h"

class Score;

class Controller {
private:
    TwinWheelDriver *twinWheelDriver;
    RangingSensor *rangingSensor;
    CNetMqtt netMqtt;
    Score *score;

    enMsgId_t enMsg;

protected:
    Controller(void);
    ~Controller(void);


public:
    static Controller* _instance;

    static Controller* getInstance(void);
    Position *position;
    // Position系
    void reset(void);
    void getPosition(float* distance, float* angle);

    // twinWheelDriver系
    void changeDriveMode(Mode mode, int voltage_level);

    // RangingSensor系
    float getRanging(void);

    // Course系
    void getNextScoreTable(int nextScoreTable[4]);
    int subscrTopic(void);
    int dequeueMessage(void);

};

#endif
