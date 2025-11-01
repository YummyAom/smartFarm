#ifndef FAN_CONTROLLER_H
#define FAN_CONTROLLER_H

class FanController {
private:
    int fanPin;
    float Kp, Ki, Kd;
    float I_out, lastError;
    float integral;
    float prevError;
public:
    FanController(int pin, float kp, float ki, float kd);
    void begin();
    void setSpeed(float currentTemp, float targetTemp);
    void turnOff();
    int calculatePWM(float currentTemp, float targetTemp);
};

#endif
