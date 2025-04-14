// --- RFReceiver.h ---
#pragma once

#define RX433_INT 		0
#define TX433_PIN 		4

// Analog PIN Port 1
#define ADC_PIN_P1_1	A0
#define ADC_PIN_P1_2	A3

// Analog PIN Port 2
#define ADC_PIN_P2_1	A1
#define ADC_PIN_P2_2	A6

// Analog PIN Port 3
#define ADC_PIN_P3_1 	A2
#define ADC_PIN_P3_2 	A7

// ID PIN - to identify sensor type based on voltage divider
#define ID_PIN_P1			A3
#define ID_PIN_P2			A6
#define ID_PIN_P3			A7

// Digital PIN Port 1
#define IO_PIN_P1_1		14
#define IO_PIN_P1_2		17
#define IO_PIN_P1_3		3

// Digital PIN Port 2.  NOTE: There is no digitalRead on IO_PIN_P2_2 because this is a pure analog pin ADC6
#define IO_PIN_P2_1		15
#define IO_PIN_P2_2		A6
#define IO_PIN_P2_3		5

// Digital PIN Port 3.  NOTE: There is no digitalRead on IO_PIN_P3_2 because this is a pure analog pin ADC7
#define IO_PIN_P3_1		16
#define IO_PIN_P3_2		A7
#define IO_PIN_P3_3		6


class RFReceiver {
public:
    void init();
    void poll();
    void transmit(const char* guid, const char* data) ;   

private:
    int getPinFromGUID(const char* guid);
    unsigned long lastSensorPollTime = 0;
};