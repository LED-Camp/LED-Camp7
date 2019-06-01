#ifndef __LINE_SENSOR_H__
#define __LINE_SENSOR_H__

class LineSensor {
private:
    int  pinLeft;
    int  pinCenter;
    int  pinRight;

protected:
    LineSensor(int pinLeft, int pinCenter, int pinRight);

public:
    static LineSensor* _instance;
    static LineSensor* getInstance(int pinLeft, int pinCenter, int pinRight);
    void getLineValue(bool* left, bool* center, bool* right);
};

#endif
