#ifndef SENSOR_DATA_H
#define SENSOR_DATA_H

struct SensorData {
    int lux;            // ค่าความสว่างจาก LDR
    int humidity;       // ความชื้นอากาศจาก DHT22
    float temperature;  // อุณหภูมิจาก DHT22
    int soilMoisture;   // ความชื้นดิน soil
};

#endif