#ifndef __RANGING_SENSOR__
#define __RANGING_SENSOR__

#include <cstdint>

#include "vl53l0x_api.h"
#include "vl53l0x_platform.h"


class RangingSensor
{
 public:
  RangingSensor();
  ~RangingSensor();

  static RangingSensor* _instance;

  static RangingSensor* getInstance();
  void Initialize();
  float getRanging();
  
 private:
  VL53L0X_Dev_t m_device;
  VL53L0X_Dev_t* pm_device = &m_device;
};

#endif //__RANGING_SENSOR__
