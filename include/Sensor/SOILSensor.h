#ifndef SOIL_SENSOR_H
#define SOIL_SENSOR_H

#include <Arduino.h>
#include <Adafruit_ADS1X15.h>

class SOILSensor {
private:
    Adafruit_ADS1115 &ads;
    uint8_t channel;

public:
    SOILSensor(uint8_t ch, Adafruit_ADS1115 &ads);
    void begin();
    int getPWM();
    int getSoilMoisturePercent();
    float getVolte();
};

#endif
