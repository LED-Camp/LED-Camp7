#include "ColorSensor.h"

#include <stdio.h>

#include "bh1745nuc.h"

ColorSensor::ColorSensor()
{

}


ColorSensor::~ColorSensor()
{

}


ColorSensor* ColorSensor::_instance = 0;

ColorSensor* ColorSensor::getInstance()
{
    if (_instance == 0)
    {
        _instance = new ColorSensor();
    }

    return _instance;
}


void ColorSensor::Initialize()
{
    bh1745nuc_init();
}

void ColorSensor::getColor(uint16_t * r, uint16_t * g, uint16_t * b, uint16_t * c)
{
    bh1745nuc_get_val(r, g, b, c);
}
