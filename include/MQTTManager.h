#ifndef MQTT_MANAGER_H
#define MQTT_MANAGER_H

#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "./Data/SensorData.h"
#include "Config.h"
#include "./Data/DeviceData.h"
#include "./Data/UserSettings.h"

class MQTTManager
{
public:
    MQTTManager();
    void begin();
    void loop();
    void publishAllSensors(const SensorData &data);
    void publishMotorStatus();
    bool isConnected();
    void getMotorState(UserSettings &state);

private:
    WiFiClient espClient;
    PubSubClient client;

    bool motorState;
    void connectWiFi();
    void reconnectMQTT();
    static void callback(char *topic, byte *payload, unsigned int length);
};

#endif
