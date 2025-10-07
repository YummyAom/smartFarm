#ifndef DHT_SENSOR_H
#define DHT_SENSOR_H

#include <DHT.h>

class DHTSensor
{
    DHT dht;
public:
    DHTSensor(uint8_t DHTpin, uint8_t type);
    void begin();
    void readAndPrint();
    float getHumidity();
    float getTemperature();
};

#endif
