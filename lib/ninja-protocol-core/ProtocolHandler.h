
// --- ProtocolHandler.h ---
#pragma once

class SensorPoller;
class RFReceiver;

class ProtocolHandler {
public:
    void handleJSON(const char* input);
    void sendObjects();
    void setSensorPoller(SensorPoller* s);
    void setRFReceiver(RFReceiver* r);

private:
    SensorPoller* sensors = nullptr;
    RFReceiver* rf = nullptr;
    unsigned long lastSensorPollTime = 0;
    void handleReactor();
    void handleDeviceCommand(int vid, int did, const char* guid, const char* data);
    void sendAck(const char* guid, int vid, int did, const char* strData);
    void sendError(int code);
    void sendError(int code, const char* error);
};

