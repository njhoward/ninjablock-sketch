// lib/ninja-sensors/Sensors.h
#ifndef SENSORS_H
#define SENSORS_H

class SensorsClass {
public:
    char* getSensorValue(int port, int type) { return 0; }
    int idTheType(int analogValue, bool debug = false) { return 0; }
};

extern SensorsClass Sensors;

#endif
