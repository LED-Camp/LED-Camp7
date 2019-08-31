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
    void getColor(uint16_t red, uint16_t green, uint16_t blue, uint16_t* color);

private:
    
};


#endif //__COLOR_SENSOR__
