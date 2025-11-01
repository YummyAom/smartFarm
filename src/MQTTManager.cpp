#include "../include/MQTTManager.h"
#include "../include/config.h"
#include "../include/Data/DeviceData.h"
#include "../include/Data/UserSettings.h"
#include <ArduinoJson.h>

UserSettings config;

MQTTManager::MQTTManager() : client(espClient) {}

// ------------------ WiFi ------------------
void MQTTManager::connectWiFi()
{
    Serial.print("Connecting WiFi...");
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\n✅ WiFi Connected!");
}

// ------------------ MQTT Connect ------------------
void MQTTManager::reconnectMQTT()
{
    while (!client.connected())
    {
        Serial.print("Connecting to MQTT...");
        if (client.connect(DEVICE_ID))
        {
            Serial.println("✅ Connected to MQTT!");

            client.subscribe("device/config");
            client.subscribe("device/pump/state");
            client.subscribe("device/led/state");
            client.subscribe("device/fan/state");
            client.subscribe("sensor/config");

            Serial.println("✅ Subscribed to topics!");
        }
        else
        {
            Serial.println("❌ MQTT failed, retrying...");
            delay(5000);
        }
    }
}

// ------------------ MQTT Callback ------------------
void MQTTManager::callback(char *topic, byte *payload, unsigned int length)
{
    String msg;
    for (unsigned int i = 0; i < length; i++)
        msg += (char)payload[i];

    Serial.printf("\n📩 [Topic: %s]\nPayload: %s\n", topic, msg.c_str());

    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, msg);
    if (error)
    {
        Serial.println("❌ JSON parse error");
        return;
    }

    String t = String(topic);

    if (t == "device/fan/state")
    {
        config.fanEnabled = doc["state"].as<bool>();
        Serial.printf("✅ Fan state updated: %d\n", config.fanEnabled);
    }
    else if (t == "device/pump/state")
    {
        config.pumpEnabled = doc["state"].as<bool>();
        Serial.printf("✅ Pump state updated: %d\n", config.pumpEnabled);
    }
    else if (t == "device/LED/state")
    {
        config.ledEnabled = doc["state"].as<bool>();
        Serial.printf("✅ LED state updated: %d\n", config.ledEnabled);
    }
    else if (t == "device/config")
    {
        config.fanEnabled = doc["fan"].as<bool>();
        config.pumpEnabled = doc["pump"].as<bool>();
        config.ledEnabled = doc["LED"].as<bool>();
        Serial.println("✅ Updated all deivce states from config!");
    }

    if (t == "sensor/config")
    {
        config.targetTemp = doc["DHT22"].as<int>();
        config.targetLux = doc["LDR Photosensitive Brightness"].as<int>();
        config.targetSoilMoisture = doc["Soil Moisture"].as<int>();
    }

    Serial.print("LUX: ");
    Serial.println(config.targetLux);
    Serial.print("TEMP: ");
    Serial.println(config.targetTemp);
    Serial.print("SOIL: ");
    Serial.println(config.targetSoilMoisture);
    Serial.printf("fan=%d | pump=%d | led=%d\n", config.fanEnabled, config.pumpEnabled, config.ledEnabled);
    Serial.println("=======================================================");
}

// ------------------ Setup MQTT ------------------
void MQTTManager::begin()
{
    connectWiFi();
    client.setServer(MQTT_SERVER, MQTT_PORT);
    client.setCallback([this](char *topic, byte *payload, unsigned int length)
                       { this->callback(topic, payload, length); });
}

// ------------------ Check & Loop ------------------
bool MQTTManager::isConnected()
{
    return client.connected();
}

void MQTTManager::loop()
{
    if (!client.connected())
    {
        reconnectMQTT();
    }
    client.loop();
}

//------------------ Publish Sensors ------------------
void MQTTManager::publishAllSensors(const SensorData &data)
{
    JsonDocument doc;

    // สร้าง object "sensors"
    JsonObject sensors = doc.createNestedObject("sensors");

    // ---------------- LDR ----------------
    JsonObject light = sensors.createNestedObject("LDR");
    light["value"] = data.lux;
    light["target"] = config.targetLux;
    light["unit"] = "lux";

    // ---------------- DHT22 ----------------
    JsonObject dht22 = sensors.createNestedObject("DHT22");
    dht22["value"] = data.temperature;
    dht22["target"] = config.targetTemp;
    dht22["unit"] = "C";

    // ---------------- Soil Moisture ----------------
    JsonObject soil = sensors.createNestedObject("SoilMoisture");
    soil["value"] = data.soilMoisture;
    soil["target"] = config.targetSoilMoisture;
    soil["unit"] = "%";

    // ---------------- Metadata (optional) ----------------
    doc["deviceId"] = DEVICE_ID;
    doc["timestamp"] = millis();

    String json;
    serializeJson(doc, json);
    client.publish("sensors/record", json.c_str());
    Serial.println("📤 " + json);
}


// ------------------ Get Motor State ------------------
void MQTTManager::getMotorState(UserSettings &state)
{
    state = config;
}
