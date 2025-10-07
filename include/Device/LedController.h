#ifndef LED_CONTROLLER_H
#define LED_CONTROLLER_H
class LedController
{
    int ledPin;
public:
    LedController(int ledPin);
    void begin();
    void setBrightness(int lux, int dataLux);
};
#endif
// #ifndef LED_CONTROLLER_H
// #define LED_CONTROLLER_H

// class LedController {
// private:
//     int ledPin;
//     float Kp, Ki, Kd;
//     float integral;
//     float prevError;

// public:
//     LedController(int ledPin, float kp, float ki, float kd);

//     void begin();
//     int calculatePWM(float currentLux, float targetLux);
//     void setBrightness(float currentLux, float targetLux);
//     void resetPID();
// };

// #endif
