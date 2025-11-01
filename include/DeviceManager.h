#ifndef DEVICE_MANAGER_H
#define DEVICE_MANAGER_H

#include "../include/Device/PumpController.h"
#include "../include/Device/LedController.h"
#include "../include/Device/FanController.h"
#include "SensorManager.h"
#include "./Data/SensorData.h"
#include "./Data/UserSettings.h"
#include "./Data/DeviceData.h"

class DeviceManager {
  FanController fan;
  PumpController pump;
  LedController led;
  SensorManager &sensor;

  bool ledState;
  bool fanState;
  bool pumpState;

public:
  DeviceState state; 

  DeviceManager(SensorManager &sm);
  void begin();
  void startDevice(SensorData &data, UserSettings &settings);
  DeviceState getState();  
};

#endif
