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

    bh1745nuc_write_byte(BH1745NUC_INTERRUPT, 0x01);
    bh1745nuc_write_byte(BH1745NUC_PERSISTENCE, 0x01);
    bh1745nuc_write_byte(BH1745NUC_TH_LSB, 0x00);
    bh1745nuc_write_byte(BH1745NUC_TH_MSB, 0x00);
    bh1745nuc_write_byte(BH1745NUC_TL_LSB, 0xFF);
    bh1745nuc_write_byte(BH1745NUC_TL_MSB, 0xFF);
}

void ColorSensor::getColorValue(uint16_t* r, uint16_t* g, uint16_t* b, uint16_t* c)
{
    bh1745nuc_get_val(r, g, b, c);
}

