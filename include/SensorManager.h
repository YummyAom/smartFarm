#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

#include "Sensor/LDRSensor.h"
#include "Sensor/DHTSensor.h"
#include "Sensor/SOILSensor.h"
#include "./Data/SensorData.h"
class SensorManager {
private:
    DHTSensor dht;
    LDRSensor ldr;
    SOILSensor soil;
public:
  SensorManager();
  void begin();
  void readAndPrint();
  SensorData readSensors();
};

#endif
