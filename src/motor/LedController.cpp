#include "../include/Device/LedController.h"
#include <Arduino.h>

LedController::LedController(int ledPin, float kp, float ki, float kd)
    : ledPin(ledPin), Kp(kp), Ki(ki), Kd(kd), I_out(0), lastError(0)
{}

void LedController::begin() {
    pinMode(ledPin, OUTPUT);
    analogWrite(this->ledPin, 0);
}

int LedController::calculatePWM(int currentLux, int targetLux) {
    float error = targetLux - currentLux;
    float normalizedError = error / (MAXLUX - MINLUX) * 255.0;

    // PID calculation
    I_out += Ki * normalizedError;
    I_out = constrain(I_out, 0, 255);

    float P_out = Kp * normalizedError;
    float D_out = Kd * (normalizedError - lastError);
    lastError = normalizedError;

    int pwmOutput = P_out + I_out + D_out;
    pwmOutput = constrain(pwmOutput, 0, 255);
    Serial.print("Target Lux: "); Serial.print(targetLux);
    Serial.print(" Current Lux: "); Serial.print(currentLux);   
    Serial.print("P: "); Serial.print(P_out);
    Serial.print(" I: "); Serial.print(I_out);
    Serial.print(" D: "); Serial.print(D_out);
    Serial.print(" PWM: "); Serial.println(pwmOutput);

    return pwmOutput;
}

void LedController::setBrightness(int currentLux, int targetLux) {
    int pwm = calculatePWM(currentLux, targetLux);
    analogWrite(ledPin, pwm);
}

void LedController::turnOff() {
    analogWrite(ledPin, 0);
}
