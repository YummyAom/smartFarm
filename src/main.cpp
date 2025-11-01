#include "SensorManager.h"
#include "DeviceManager.h"
#include "../include/Data/SensorData.h"
#include "../include/Data/UserSettings.h"
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "../include/MQTTManager.h"
#include "../include/config.h"
#include "../include/Data/DeviceData.h"

SensorManager sensor;
DeviceManager device(sensor);
UserSettings settings;
SensorData data;
// DeviceState devState;
MQTTManager mqtt;

unsigned long previousMillis = 0;
const long interval = 2000;

WiFiClient espClient;
PubSubClient client(espClient);

void setup()
{
  Serial.begin(115200);
  sensor.begin();
  mqtt.begin();
}

void loop()
{
  unsigned long currentMillis = millis();
  mqtt.loop();

  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;
    mqtt.getMotorState(settings);
    data = sensor.readSensors();
    device.startDevice(data, settings);
  }
}