// --- SerialBridge.cpp ---
#include "SerialBridge.h"
#include <Arduino.h>

void SerialBridge::setProtocol(ProtocolHandler* p) {
    protocol = p;
}

int SerialBridge::readSerial() {
    int i = 0;
    while (Serial.available() > 0 && i < sizeof(serialBuffer) - 1) {
        serialBuffer[i++] = Serial.read();
        delay(2);
    }
    serialBuffer[i] = '\0';
    return i;
}

void SerialBridge::loop() {
    if (Serial.available() > 0) {
        int len = readSerial();
        if (len > 0 && protocol) {
            protocol->handleJSON(serialBuffer);
        }
    }
    protocol->sendObjects();
}