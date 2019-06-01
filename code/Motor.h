
#ifndef __MOTOR__
#define __MOTOR__

class Motor {
private:
    int pin1;
    int pin2;

public:
    Motor(int pin1, int pin2);
    ~Motor();

    void pwmWrite(double);
};

#endif
