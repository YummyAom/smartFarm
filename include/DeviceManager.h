#ifndef DEVICE_MANAGER_H
#define DEVICE_MANAGER_H

#include "../include/Device/PumpController.h"
#include "../include/Device/LedController.h"
#include "../include/Device/FanController.h"
#include "SensorManager.h"
#include "./Data/SensorData.h"
#include "./Data/UserSettings.h"

// SensorManager sensor;

// class DeviceManager {
//   // FanController fan;
//   // PumpController pump;
//   LedController led;
// public:
//   DeviceManager();
//   void begin();
//   void startDevice(SensorData &data,UserSettings &settings);
// };

class DeviceManager {
  FanController fan;
  PumpController pump;
  LedController led;
  SensorManager &sensor;  
public:
  DeviceManager(SensorManager &sm);
  void begin();
  void startDevice(SensorData &data, UserSettings &settings);  // ใช้ SensorData
};


#endif