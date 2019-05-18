#include "Motor.h"
#include <wiringPi.h>
#include <softPwm.h>

#define PWM_RANGE ((double)100.0)

Motor::Motor(int pin1, int pin2) {
    this->pin1 = pin1;
    this->pin2 = pin2;

    softPwmCreate(this->pin1, 0, PWM_RANGE);
    softPwmCreate(this->pin2, 0, PWM_RANGE);
}

Motor::~Motor() {

}

void Motor::pwmWrite(double ratio) {
    if (ratio > 100.0)
        ratio = 100.0; // saturation
    else if (ratio < -100.0)
        ratio = -100.0;


    if ((ratio < 1.0) && (ratio > -1.0)) { // Stop
        softPwmWrite(pin1, 100);
        softPwmWrite(pin2, 100);
    } else if (ratio > 0) { // Nomal rotation
        softPwmWrite(pin1, (int) (ratio));
        softPwmWrite(pin2, 0);
    } else { // Reverse rotation
        softPwmWrite(pin1, 0);
        softPwmWrite(pin2, (int) (-ratio));
    }
}
