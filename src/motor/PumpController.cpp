#include <../include/Device/PumpController.h>
#include <Arduino.h>

const int MAX_SOIL_MOISTURE = 100;
const int MIN_SOIL_MOISTURE = 0;
const int pumpMaxTime = 10000;

int pumpTime = 0;
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
    // if(moisture < target && digitalRead(this->relayPin) == LOW){
    //     on();
    //     pumpTime = millis();
    // // } if (digitalRead(relayPin) == HIGH && millis() - pumpStartTime > pumpMaxTime) {
    //     off();
    // }
}  