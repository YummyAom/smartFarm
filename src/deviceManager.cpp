#include "../include/DeviceManager.h"

#define PUMP_Pin 25
#define LED_PIN 5
#define FAN_PIN 15

#define FAN_KP 2.0
#define FAN_KI 0.05
#define FAN_KD 1.0

#define LED_KP 2.0
#define LED_KI 0.05
#define LED_KD 1.0


DeviceManager::DeviceManager(SensorManager &sm)
    : fan(FAN_PIN, FAN_KP, FAN_KI, FAN_KD),
      pump(PUMP_Pin),
      led(LED_PIN),
      sensor(sm)
{}

void DeviceManager::begin() {
    fan.begin();
    pump.begin();
    led.begin();
}

void DeviceManager::startDevice(SensorData &data, UserSettings &settings) {
    led.setBrightness(data.lux, settings.targetLux);
    pump.setSoilMoisture(data.soilMoisture, settings.soilMoisture);
}
