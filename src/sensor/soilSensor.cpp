#include "../include/Sensor/SOILSensor.h"
#include <math.h>

const float Vin = 3.3;
const float Rref = 10000.0;
const float PGA = 2.048;

const float DIGI_RANGE = 32767.0;

// 👇 ปรับค่า Calibration ตามการวัดจริง
const float SOIL_DRY = 17426.0; // ค่า ADC เมื่อดินแห้ง
const float SOIL_WET = 2000.0;  // ค่า ADC เมื่อดินเปียก

const float MAX_VOLTE = 3.3;
const float MIN_VOLTE = 0.0;

SOILSensor::SOILSensor(uint8_t ch, Adafruit_ADS1115 &ads)
    : channel(ch),
      ads(ads)
{
}

int SOILSensor::getPWM()
{
  return ads.readADC_SingleEnded(channel);
}

float SOILSensor::getVolte()
{
  float raw = getPWM();
  float volte = ads.computeVolts(raw);
  volte = constrain(volte, MIN_VOLTE, MAX_VOLTE);
  return volte;
}

int SOILSensor::getSoilMoisturePercent()
{
  int raw = getPWM();
  int moisturePercent = map(raw, SOIL_DRY, SOIL_WET, 0, 100);
  moisturePercent = constrain(moisturePercent, 0, 100);

  return moisturePercent;
}
