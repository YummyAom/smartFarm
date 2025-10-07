#include "../include/Sensor/DHTSensor.h"

DHTSensor::DHTSensor(uint8_t DHTpin, uint8_t type) : dht(DHTpin, type) {}

void DHTSensor::begin(){
    dht.begin();
}
float DHTSensor::getHumidity(){
    return dht.readHumidity();
}

float DHTSensor::getTemperature(){
    return dht.readTemperature();
}


void DHTSensor::readAndPrint(){
    float h = getHumidity();
    float t = getTemperature();
    if( isnan(h) || isnan(t) ){
        Serial.println("Failed to read DHT22 value");
    }
    else{
        Serial.print(F("Humidity: "));
        Serial.print(h, 1);
        Serial.print(F("%  Temparature: "));
        Serial.print(t, 1);
        Serial.println(F("°C"));
    }
}
