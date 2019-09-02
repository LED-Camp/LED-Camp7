#ifndef __CONTROLLER__
#define __CONTROLLER__

#include <cstdint>
#include "CommonDefine.h"
#include "ColorSensor.h"
#include "RangingSensor.h"
#include "TwinWheelDriver.h"
#include "Position.h"
#include "LineSensor.h"


class Score;

class Controller {
private:
    TwinWheelDriver *twinWheelDriver;
    ColorSensor *colorSensor;
    RangingSensor *rangingSensor;
    LineSensor *lineSensor;

protected:
    Controller(void);
    ~Controller(void);

public:
    static Controller* _instance;

    static Controller* getInstance(void);
    Position *position;
    // Position系
    void positionReset(void);
    void getPosition(float* distance, float* angle);

    // twinWheelDriver系
    void changeDriveMode(Mode mode, int voltage_level);

    // LineSensor系
    void detectBlack(bool* left, bool* center, bool* right);
    
    // RangingSensor系
    float getRanging(void);

    void getColorValue(uint16_t* red, uint16_t* green, uint16_t* blue, uint16_t* clear);
    void getColor(uint16_t red, uint16_t green, uint16_t blue, uint16_t* color);
    
};

#endif
