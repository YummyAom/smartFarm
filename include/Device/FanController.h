#ifndef FAN_CONTROLLER_H
#define FAN_CONTROLLER_H

class FanController {
private:
    int pwmPin;
    float Kp, Ki, Kd;
    float integral;
    float prevError;

public:
    // constructor ใหม่: ใส่ค่า PID
    FanController(int pin, float kp, float ki, float kd);

    void begin();

    // ใช้ float สำหรับ sensor 16-bit หรือ scaled value
    int calculatePWM(float sensorValue, float setPoint);

    void setSpeed(float sensorValue, float setPoint);

    // ถ้าต้องการ reset PID
    void resetPID();
};

#endif
