#include <../include/Device/PumpController.h>
#include <Arduino.h>

const unsigned int MAX_SOIL_MOISTURE = 100;
const unsigned int MIN_SOIL_MOISTURE = 0;
const unsigned int PUMP_RUN_TIME = 2000;
const unsigned int PUMP_WAIT_TIME = 2000;

enum PumpState {IDLE, RUN, WAIT};
PumpState pumpState = IDLE;

PumpController::PumpController(int pin):
    relayPin(pin)
{}

void PumpController::begin(){
    pinMode(relayPin, OUTPUT);
    digitalWrite(relayPin, LOW);    
}

void PumpController::turnOn(){
    digitalWrite(relayPin, HIGH);
}

void PumpController::turnOff(){
    digitalWrite(relayPin, LOW);
}

void PumpController::setSoilMoisture(int moisture, int target){
    unsigned long PumpStartTime = 0;
    unsigned long pumpCyclewait = 0;
    
    unsigned long now = millis();
    switch (pumpState)
    {
    case IDLE:
        if(moisture < target){
            turnOn();
            pumpState = RUN;
            PumpStartTime = now;
        }
        break;
    case RUN: 
        if(now - PumpStartTime >= PUMP_RUN_TIME){
            turnOff();
            pumpState = WAIT;
            pumpCyclewait = now;
        }
        break;
    case WAIT:
        if(now - PumpStartTime >= PUMP_WAIT_TIME) {
            pumpState = IDLE;
        }
        break;
    }
}
