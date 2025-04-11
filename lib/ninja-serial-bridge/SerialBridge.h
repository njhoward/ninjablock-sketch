// --- SerialBridge.h ---
#pragma once
#include "ProtocolHandler.h"

class SerialBridge {
public:
    void setProtocol(ProtocolHandler* p);
    void loop();

private:
    ProtocolHandler* protocol = nullptr;
    char serialBuffer[128];
    int readSerial();
};