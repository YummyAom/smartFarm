#include "../include/Device/FanController.h"
#include <Arduino.h>

const int MAXTEMP = 50;
const int MINTEMP = 0;

float prevTemp = 0;

FanController::FanController(int pin, float kp, float ki, float kd)
    : fanPin(pin), Kp(kp), Ki(ki), Kd(kd), I_out(0), lastError(0)
{
}

void FanController::begin()
{
    pinMode(fanPin, OUTPUT);
    analogWrite(fanPin, 0);
}

int FanController::calculatePWM(float currentTemp, float targetTemp)
{
    float error = currentTemp - targetTemp;
    
    float normalizedError = error / (MAXTEMP - MINTEMP) * 255.0;

    // PID calculation
    I_out += Ki * normalizedError;
    I_out = constrain(I_out, 0, 255); // integral windup protection

    float P_out = Kp * normalizedError;
    float D_out = Kd * (normalizedError - lastError);
    lastError = normalizedError;

    int pwmOutput = P_out + I_out + D_out;
    pwmOutput = constrain(pwmOutput, 0, 255);

    Serial.print("P: ");
    Serial.print(P_out);
    Serial.print(" I: ");
    Serial.print(I_out);
    Serial.print(" D: ");
    Serial.print(D_out);
    Serial.print(" PWM: ");
    Serial.println(pwmOutput);

    return pwmOutput;
}

void FanController::setSpeed(float currentTemp, float targetTemp)
{
    int pwm = calculatePWM(currentTemp, targetTemp);
    Serial.print("Current Temp: ");
    Serial.print(currentTemp);
    Serial.print("target Temp: ");
    Serial.print(targetTemp);
    analogWrite(fanPin, pwm);
    prevTemp = pwm;
}

void FanController::turnOff()
{
    analogWrite(fanPin, 0);
}
