#include "SensorManager.h"
#include "DeviceManager.h"
#include "../include/Data/SensorData.h"
#include "../include/Data/UserSettings.h"

SensorManager sensor;
DeviceManager device(sensor);
UserSettings settings;
SensorData data;

unsigned long previousMillis = 0;   
const long interval = 2000;

void setup() {
  
  Serial.begin(115200);
  sensor.begin();
  settings.targetLux = 2000;
  settings.targetSoilMoisture = 40;
}

void loop() {

  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis >= interval) {
  
    previousMillis = currentMillis;
    data = sensor.readSensors();
    device.startDevice(data, settings);
  }
}
