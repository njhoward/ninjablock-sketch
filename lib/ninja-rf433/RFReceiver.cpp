#include "RFReceiver.h"
#include <Arduino.h>
#include <RCSwitch.h>
#include <ArduinoJson.h>

static RCSwitch mySwitch;

void RFReceiver::poll() {
    mySwitch.enableReceive(0); // interrupt 0 on pin 2 typically

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
