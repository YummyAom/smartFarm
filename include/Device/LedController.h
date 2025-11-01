#ifndef LED_CONTROLLER_H
#define LED_CONTROLLER_H

class LedController {
private:
    int ledPin;
    float Kp, Ki, Kd;
    float I_out;
    float lastError;

    const int MAXLUX = 10000;
    const int MINLUX = 0;

public:
    LedController(int ledPin, float kp, float ki, float kd);
    void begin();
    int calculatePWM(int currentLux, int targetLux);
    void setBrightness(int currentLux, int targetLux);
    void turnOff();
};

#endif
