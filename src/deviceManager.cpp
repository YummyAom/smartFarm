#include "../include/DeviceManager.h"

#define PUMP_Pin 25
#define LED_PIN 5
#define FAN_PIN 15

#define FAN_KP 0.8
#define FAN_KI 0.2
#define FAN_KD 0.1

#define LED_KP 0.8
#define LED_KI 0.2
#define LED_KD 0.1

DeviceManager::DeviceManager(SensorManager &sm)
    : fan(FAN_PIN, FAN_KP, FAN_KI, FAN_KD),
      pump(PUMP_Pin),
      led(LED_PIN, LED_KP, LED_KI, LED_KD),
      sensor(sm),
      ledState(true),
      fanState(true),
      pumpState(true)
{
}

void DeviceManager::begin()
{
    fan.begin();
    pump.begin();
    led.begin();
}

void DeviceManager::startDevice(SensorData &data, UserSettings &settings)
{
    this->ledState = settings.ledEnabled;
    this->pumpState = settings.pumpEnabled;
    this->fanState = settings.fanEnabled;
    Serial.println("\n--- Device Control Start ---");
    Serial.print("LED State: ");
    Serial.println(this->ledState);
    Serial.print("Pump State: ");  
    Serial.println(this->pumpState);
    Serial.print("Fan State: ");
    Serial.println(this->fanState);

    // --- ควบคุม LED ---
    if (this->ledState)
    {
        led.setBrightness(data.lux, settings.targetLux);
        state.ledOn = true;
        
    }
    else
    {
        led.turnOff();
        state.ledOn = false;
    }

    // --- ควบคุม Pump ---
    if (this->pumpState)
    {
        pump.setSoilMoisture(data.soilMoisture, settings.targetSoilMoisture);
        state.pumpOn = true;
    }
    else
    {
        pump.turnOff();
        state.pumpOn = false;
    }

    // --- ควบคุม Fan ---
    if (this->fanState)
    {
        fan.setSpeed(data.temperature, settings.targetTemp);
        state.fanOn = true;
    }
    else
    {
        fan.turnOff();
        state.fanOn = false;
    }
}

DeviceState DeviceManager::getState()
{
    return state;
}
