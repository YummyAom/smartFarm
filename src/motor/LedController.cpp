#include <Arduino.h>
#include "../include/Device/LedController.h"

const int MAXLUX = 10000;
const int MINLUX = 0;
int prevBrightness = 0;

// float P_out = 0;
float I_out = 0;
// float D_out = 0;
float lastError = 0;

float Kp = 0.8; 
float Ki = 0.2; 
float Kd = 0.1; 

LedController::LedController(int ledPin)
: ledPin(ledPin) {}

void LedController::begin() {
    pinMode(ledPin, OUTPUT);
}

int calculatePWM(int currentLux, int targetLux) {
    // 1. คำนวณ error
    float error = targetLux - currentLux;

    // 2. Normalize error ให้เหมาะกับ PWM scale (0-255)
    float normalizedError = error / (MAXLUX - MINLUX) * 255.0;

    // 3. PID calculation
    // Integral
    I_out += Ki * normalizedError;
    I_out = constrain(I_out, 0, 255);  // ป้องกัน integral windup

    // Proportional
    float P_out = Kp * normalizedError;

    // Derivative
    float D_out = Kd * (normalizedError - lastError);
    lastError = normalizedError;

    // รวม PID
    int pwmOutput = P_out + I_out + D_out;
    pwmOutput = constrain(pwmOutput, 0, 255);

    // Debug print
    Serial.print("P: "); Serial.print(P_out);
    Serial.print(" I: "); Serial.print(I_out);
    Serial.print(" D: "); Serial.print(D_out);
    Serial.print(" PWM: "); Serial.println(pwmOutput);

    return pwmOutput;
}

void LedController::setBrightness(int currentLux, int targetLux) {

    Serial.print("targetLux: ");Serial.print(targetLux);
    int newBrightness = calculatePWM(currentLux, targetLux);
    Serial.print("Brightness: ");Serial.println(newBrightness);
    analogWrite(this->ledPin, newBrightness);
    prevBrightness = newBrightness;
}



