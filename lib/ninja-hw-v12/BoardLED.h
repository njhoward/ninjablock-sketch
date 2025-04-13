// --- BoardLED.h ---
#pragma once

class BoardLED {
public:
    static void init();
    static void setEyeColor(const char* hex);
    static void setStatusColor(const char* hex);
    static const char* getEyeColor();
    static const char* getStatusColor();

private:
    static char lastEyeColor[7];
    static char lastStatusColor[7];
};
