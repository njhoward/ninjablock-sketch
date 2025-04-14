// --- RFReciever.cpp ---
#include "RFReceiver.h"
#include <Arduino.h>
#include <RCSwitch.h>
#include <ArduinoJson.h>

static RCSwitch mySwitch;
static bool receiverInitialized = false;

// call early
void RFReceiver::init() {
    if (!receiverInitialized) {
        mySwitch.enableReceive(0);
        receiverInitialized = true;
    }
}


void RFReceiver::poll() {

    unsigned long now = millis();
    if ((now - lastSensorPollTime >= 30000 || lastSensorPollTime == 0)) {
        Serial.println(F("[RFReceiver] poll running"));  // sanity check
        lastSensorPollTime = now;
    }

    if (mySwitch.available()) {
        unsigned long value = mySwitch.getReceivedValue();
        unsigned int protocol = mySwitch.getReceivedProtocol();


        StaticJsonDocument<256> doc;
        JsonArray arr = doc.createNestedArray("DEVICE");
        JsonObject obj = arr.createNestedObject();
        obj["G"] = "0";
        obj["V"] = protocol;
        obj["D"] = 11;
        obj["DA"] = value;

        serializeJson(doc, Serial);
        Serial.println();

        mySwitch.resetAvailable();
    }
}

void RFReceiver::transmit(const char* guid, const char* data) {
    int pin = getPinFromGUID(guid);
    mySwitch.enableTransmit(pin);
    mySwitch.setPulseLength(350);
    mySwitch.setRepeatTransmit(8);
    mySwitch.send(data);
    mySwitch.disableTransmit();
}

int RFReceiver::getPinFromGUID(const char* guid) {
    int port = atoi(guid);
    switch (port) {
        case 1: return IO_PIN_P1_1;
        case 2: return IO_PIN_P2_1;
        case 3: return IO_PIN_P3_1;
        default: return TX433_PIN;
    }
}
