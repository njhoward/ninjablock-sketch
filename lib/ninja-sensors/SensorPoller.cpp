#include "SensorPoller.h"
#include <Arduino.h>
#include <Sensors.h>
#include <ArduinoJson.h>
#include <BoardLED.h>

void SensorPoller::poll() {
    this->colorOutput("1007", BoardLED::getEyeColor());    // Eye color
    this->colorOutput("999",  BoardLED::getStatusColor()); // Status color
}

void SensorPoller::sensorOutput(int id, char const* value) {
    StaticJsonDocument<256> doc;
    JsonArray arr = doc.createNestedArray("DEVICE");
    JsonObject obj = arr.createNestedObject();
    obj["G"] = "1";
    obj["V"] = 0;
    obj["D"] = id;
    obj["DA"] = value;

    serializeJson(doc, Serial);
    Serial.println();
}

void SensorPoller::colorOutput(const char* deviceId, const char* hex) {
    StaticJsonDocument<256> doc;
    JsonArray arr = doc.createNestedArray("DEVICE");
    JsonObject obj = arr.createNestedObject();
    obj["G"] = "1";
    obj["V"] = 0;
    obj["D"] = atoi(deviceId);
    obj["DA"] = hex;

    serializeJson(doc, Serial);
    Serial.println();
}
