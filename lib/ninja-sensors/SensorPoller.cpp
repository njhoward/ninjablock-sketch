#include "SensorPoller.h"
#include <Arduino.h>
#include <Sensors.h>
#include <ArduinoJson.h>

void SensorPoller::poll() {
    int id = Sensors.idTheType(A0, false);
    if (id >= 0) {
        char* value = Sensors.getSensorValue(1, id);
        this->sensorOutput(id, value);
    }
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
