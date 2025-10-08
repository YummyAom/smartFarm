#ifndef PUMP_CONTROLLER_H
#define PUMP_CONTROLLER_H
class PumpController
{
    int relayPin;
public:
    PumpController(int pin);
    void begin();
    void turnOn();
    void turnOff();
    void setSoilMoisture(int moisture, int target);
};
#endif