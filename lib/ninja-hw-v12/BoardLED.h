// --- BoardLED.h ---
#pragma once

class BoardLED {
public:
    static void init();
    static void setStatusColor(const char* hex);
    static void setEyeColor(const char* hex);
};