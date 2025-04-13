// --- BoardLED.cpp ---
#include "BoardLED.h"
#include <Arduino.h>
#include <string.h>

#define RED_LED_PIN     10
#define GREEN_LED_PIN   11
#define BLUE_LED_PIN    9

#define RED_STAT_LED_PIN    12
#define GREEN_STAT_LED_PIN  8
#define BLUE_STAT_LED_PIN   7

char BoardLED::lastEyeColor[7] = "000000";
char BoardLED::lastStatusColor[7] = "000000";

void BoardLED::init() {
    pinMode(RED_LED_PIN, OUTPUT);
    pinMode(GREEN_LED_PIN, OUTPUT);
    pinMode(BLUE_LED_PIN, OUTPUT);
    digitalWrite(RED_LED_PIN, HIGH);
    digitalWrite(GREEN_LED_PIN, HIGH);
    digitalWrite(BLUE_LED_PIN, HIGH);
}

void BoardLED::setEyeColor(const char* hex) {
    strncpy(lastEyeColor, hex, 6);
    lastEyeColor[6] = '\0';

    long color = strtol(hex, nullptr, 16);
    analogWrite(RED_LED_PIN, 255 - ((color >> 16) & 0xFF));
    analogWrite(GREEN_LED_PIN, 255 - ((color >> 8) & 0xFF));
    analogWrite(BLUE_LED_PIN, 255 - (color & 0xFF));
}

void BoardLED::setStatusColor(const char* hex) {
    strncpy(lastStatusColor, hex, 6);
    lastStatusColor[6] = '\0';

    long color = strtol(hex, nullptr, 16);
    analogWrite(RED_STAT_LED_PIN,   255 - ((color >> 16) & 0xFF));
    analogWrite(GREEN_STAT_LED_PIN, 255 - ((color >> 8)  & 0xFF));
    analogWrite(BLUE_STAT_LED_PIN,  255 - (color & 0xFF));
}

const char* BoardLED::getEyeColor() {
    return lastEyeColor;
}

const char* BoardLED::getStatusColor() {
    return lastStatusColor;
}
