#include "../include/Device/FanController.h"
#include <Arduino.h>

FanController::FanController(int pin, float kp, float ki, float kd):
    pwmPin(pin), Kp(kp), Ki(ki), Kd(kd), integral(0), prevError(0)
{}

void FanController::begin(){
    pinMode(pwmPin, OUTPUT);
}

// ใช้ float แทน int สำหรับ ADC 16-bit
int FanController::calculatePWM(float sensorValue, float setPoint){
    // แปลง sensorValue เป็น %RH หรือ scaled value ก่อนก็ได้
    float error = setPoint - sensorValue;

    // สะสม integral
    integral += error;

    // derivative
    float derivative = error - prevError;

    // PID output
    float output = Kp * error + Ki * integral + Kd * derivative;

    // บันทึก error ปัจจุบัน
    prevError = error;

    // clamp output 0-255 สำหรับ analogWrite
    output = constrain(output, 0, 255);

    return (int)output;
}

void FanController::setSpeed(float sensorValue, float setPoint){    
    int duty = calculatePWM(sensorValue, setPoint);
    analogWrite(pwmPin, duty);
}
