#ifndef SOIL_SENSOR_H
#define SOIL_SENSOR_H

#include <Arduino.h>
#include <Adafruit_ADS1X15.h>

class SOILSensor {
private:
    Adafruit_ADS1115 &ads;   // ใช้ reference แทน copy
    uint8_t channel;

public:
    // constructor รับ reference ของ ADS1115
    SOILSensor(uint8_t ch, Adafruit_ADS1115 &ads);

    void begin();

    int getPWM();             // อ่านค่า ADC raw
    float getVolteLDR();       // แปลง ADC → Volt
    float getSoilMoisturePercent();
};

#endif
