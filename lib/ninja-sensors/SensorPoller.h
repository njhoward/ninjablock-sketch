
// --- SensorPoller.h ---
#pragma once

class SensorPoller {
public:
    void poll();
private:
    void sensorOutput(int id, char const* value);
};