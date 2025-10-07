#include <../include/Device/PumpController.h>
#include <Arduino.h>

const int MAX_SOIL_MOISTURE = 100;
const int MIN_SOIL_MOISTURE = 0;

PumpController::PumpController(int pin):
    relayPin(pin)
{}

void PumpController::begin(){
    pinMode(relayPin, OUTPUT);
    digitalWrite(relayPin, LOW);    
}

void PumpController::on(){
    digitalWrite(relayPin, HIGH);
}

void PumpController::off(){
    digitalWrite(relayPin, LOW);
}

void PumpController::setSoilMoisture(int moisture, int target){
    int error = target - moisture;
    float nomalizedError = error / (MAX_SOIL_MOISTURE - MIN_SOIL_MOISTURE) * 255;
}