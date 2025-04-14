#include "ProtocolHandler.h"
#include <ArduinoJson.h>
#include <BoardLED.h>
#include <SensorPoller.h>
#include <RFReceiver.h>

void ProtocolHandler::setSensorPoller(SensorPoller* s) {
    sensors = s;
}

void ProtocolHandler::setRFReceiver(RFReceiver* r) {
    rf = r;
}

void ProtocolHandler::handleJSON(const char* input) {
    Serial.println("[ProtocolHandler] handleJSON()");


    
    StaticJsonDocument<512> doc;
    DeserializationError error = deserializeJson(doc, input);
    if (error) return;

    JsonArray devices = doc["DEVICE"];
    if (!devices.isNull() && devices.size() > 0) {
        JsonObject device = devices[0];
        const char* guid = device["G"] | "0";
        int vid = device["V"] | -1;
        int did = device["D"] | -1;
       
        String dataStr = device["DA"].as<String>();
        const char* data = dataStr.c_str();


        if (vid >= 0 && did >= 0) {
            handleDeviceCommand(vid, did, guid, data);
        }
    }
}

void ProtocolHandler::handleDeviceCommand(int vid, int did, const char* guid, const char* data) {
    Serial.println("[Protocol] handleDeviceCommand()");



    if (vid != 0) {
        sendError(2);  // Unknown vendor
        return;
    }

    if (!data) {
        sendError(1);  // Missing data
        return;
    }

    switch (did) {
        case 11:
            rf->transmit(guid, data);
            break;
        case 999:
            BoardLED::setStatusColor(data);
            break;
        case 1007:
            BoardLED::setEyeColor(data);
            break;
        case 1003:
            Serial.println("[Protocol] Sending ACK...");
            sendAck("0", 0, 1003, "v0.3");
            break;
        default:
            sendError(3);
            break;
    }
}

void ProtocolHandler::sendAck(const char* guid, int vid, int did, const char* strData) {
    StaticJsonDocument<256> doc;
    JsonArray ack = doc.createNestedArray("ACK");
    JsonObject obj = ack.createNestedObject();
    obj["G"] = guid;
    obj["V"] = vid;
    obj["D"] = did;
    obj["DA"] = strData;

    serializeJson(doc, Serial);
    Serial.println();
}

void ProtocolHandler::sendError(int code) {
    sendError(code, "");
}

void ProtocolHandler::sendError(int code, const char* error) {
    StaticJsonDocument<256> doc;
    JsonArray err = doc.createNestedArray("ERROR");
    JsonObject obj = err.createNestedObject();
    obj["CODE"] = code;
    obj["ERR"] = error;

    serializeJson(doc, Serial);
    Serial.println();
}

void ProtocolHandler::sendObjects() {
    unsigned long now = millis();
    if (sensors && (now - lastSensorPollTime >= 30000 || lastSensorPollTime == 0)) {
        sensors->poll();
        lastSensorPollTime = now;
    }
    if (rf) rf->poll();
}

