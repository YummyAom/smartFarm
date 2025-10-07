#include "SensorManager.h"
#include "Adafruit_ADS1X15.h"

#define DHT22_PIN 26 
#define CHANAL_LDR 1  
#define CHANAL_SOIL 0
Adafruit_ADS1115 ads;

SensorManager::SensorManager(): 
dht(DHT22_PIN, DHT22),
  ldr(CHANAL_LDR, ads),
  soil(CHANAL_SOIL, ads)
{}

void SensorManager::begin(){
  this->ldr.begin();
}
SensorData SensorManager::readSensors() {
  SensorData data;
  data.lux = ldr.claculateLux();
  data.soilMoisture = soil.getSoilMoisturePercent();
  return data;
}

