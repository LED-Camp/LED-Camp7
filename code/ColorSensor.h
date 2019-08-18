#ifndef __COLOER_SENSOR__
#define __COLOER_SENSOR__

#include <cstdint>


class ColorSensor
{
public:
    ColorSensor();
    ~ColorSensor();

    static ColorSensor* _instance;

    static ColorSensor* getInstance();
    void Initialize();
    void getColorValue(uint16_t * r, uint16_t * g, uint16_t * b, uint16_t * c);

private:
    
};


#endif //__COLOR_SENSOR__
