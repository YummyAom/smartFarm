#include "../include/Sensor/LDRSensor.h"
#include <math.h>

const float Vin = 3.3;
const float Rref = 10000.0;
const float PGA = 2.048;
const float DIGI_RANGE = 32767.0;

const float MAX_VOLTE = 3.3;
const float MIN_VOLTE = 0.0;

const int MAX_LUX = 3000;
const int MIN_LUX = 0;

LDRSensor::LDRSensor(uint8_t ch, Adafruit_ADS1115 &ads)
    : channel(ch),
      ads(ads)
{
}

// void LDRSensor::begin()
// {
//   if (!ads.begin())
//   {
//     Serial.println("Failed to initialize ads.");
//     while (1)
//       ;
//   }
// }

float LDRSensor::getVolteLDR()
{
  float raw = ads.readADC_SingleEnded(channel);
  float volte = (raw * (Vin / DIGI_RANGE) * 2) - 0.05;
  volte = constrain(volte, MIN_VOLTE, MAX_VOLTE);
  return volte;
}

int LDRSensor::claculateLux()
{
  float volt_LDR = getVolteLDR();
  int lux = 20.0 * pow(volt_LDR, -3);
  lux = constrain(lux, MIN_LUX, MAX_LUX);
  return lux;
}