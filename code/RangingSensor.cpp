#include "RangingSensor.h"

RangingSensor::RangingSensor()
{

}


RangingSensor::~RangingSensor()
{
}

RangingSensor* RangingSensor::_instance = 0;


RangingSensor* RangingSensor::getInstance(){
  if(_instance == 0){
    _instance = new RangingSensor();
    //    _instance->Initialize();
  }

  return _instance;
}


void RangingSensor::Initialize()
{
  VL53L0X_Error status = VL53L0X_ERROR_NONE;

  uint32_t refSpadCount;
  uint8_t isApertureSpads;
  uint8_t VhvSettings;
  uint8_t PhaseCal;

  

  printf ("1\n");
  pm_device->I2cDevAddr = 0x29;
  printf ("2\n");
  pm_device->fd = VL53L0X_i2c_init((char*)"/dev/i2c-1", pm_device->I2cDevAddr);

  printf ("3\n");
  if (m_device.fd < 0)
    {
    status = VL53L0X_ERROR_CONTROL_INTERFACE;
    printf ("Failed to init\n");
  }

  printf ("4\n");
  if (status == VL53L0X_ERROR_NONE)
    {
    status = VL53L0X_DataInit(pm_device);
  }

  printf ("5\n");
  if (status == VL53L0X_ERROR_NONE) {
    printf ("Call of VL53L0X_StaticInit\n");
    status = VL53L0X_StaticInit(pm_device); // Device Initialization
  }

  if(status == VL53L0X_ERROR_NONE)
    {
    printf ("Call of VL53L0X_PerformRefCalibration\n");
    status = VL53L0X_PerformRefCalibration(pm_device,
					   &VhvSettings, &PhaseCal); // Device Initialization
  }

  if(status == VL53L0X_ERROR_NONE)
    {
      printf ("Call of VL53L0X_PerformRefSpadManagement\n");
      status = VL53L0X_PerformRefSpadManagement(pm_device,
						&refSpadCount, &isApertureSpads); // Device Initialization
    }

  if(status == VL53L0X_ERROR_NONE)
    {
      status = VL53L0X_SetDeviceMode(pm_device, VL53L0X_DEVICEMODE_CONTINUOUS_RANGING); // Setup in single ranging mode
    }

  if(status == VL53L0X_ERROR_NONE)
    {
      status = VL53L0X_StartMeasurement(pm_device);
    }
}


float RangingSensor::getRanging()
{
  VL53L0X_RangingMeasurementData_t rangingMeasurementData = {0};

  VL53L0X_Error status = VL53L0X_ERROR_NONE;

  status = VL53L0X_PerformSingleRangingMeasurement(pm_device, &rangingMeasurementData);
  //  printf("Measured distance: %i\n\n", rangingMeasurementData.RangeMilliMeter);

  return ((float)rangingMeasurementData.RangeMilliMeter / 10.0);
}
