#ifndef __TWINWHEELDRIVER__
#define __TWINWHEELDRIVER__

class Motor;
class Position;

typedef enum {
  STOP, FORWARD, BACKWARD, CW, CCW,BRAKE
} Mode;

class TwinWheelDriver {
private:
    static TwinWheelDriver* _instance;
    Motor* motorL;
    Motor* motorR;
protected:
    TwinWheelDriver(int pin1A, int pin1B, int pin2A, int pin2B);
public:
    ~TwinWheelDriver();

    static TwinWheelDriver* getInstance(int pin1A, int pin1B, int pin2A,
            int pin2B);
    void changeDriveMode(Mode mode, int voltage_level, Position* position);

};

#endif
