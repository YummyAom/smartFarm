#include "../include/Sensor/SOILSensor.h"
#include <math.h>

const float Vin = 3.3;
const float Rref = 10000.0;
const float PGA = 2.048;
const float DIGI_RANGE = 32767.0;

const float MAX_VOLTE = 3.3;
const float MIN_VOLTE = 0.0;

SOILSensor::SOILSensor(uint8_t ch, Adafruit_ADS1115 &ads)
  : channel(ch),
    ads(ads)
{}

void SOILSensor::begin() {
  if (!ads.begin()) {
    Serial.println("Failed to initialize ADS.");
    while (1);
  }
}

int SOILSensor::getPWM(){
  float raw = ads.readADC_SingleEnded(channel);
}

float SOILSensor::getVolteLDR() {
  float raw = getPWM();
  float volte = (raw * (Vin / DIGI_RANGE) * 2) - 0.05;
  volte = constrain(volte, MIN_VOLTE, MAX_VOLTE);
  return volte;
}

float SOILSensor::getSoilMoisturePercent() {
  float raw = getPWM();
  float volte = (raw * (Vin / DIGI_RANGE) * 2) - 0.05;
  volte = constrain(volte, MIN_VOLTE, MAX_VOLTE);
  return volte;
}







