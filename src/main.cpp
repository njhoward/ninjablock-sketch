#include <SerialBridge.h>
#include <ProtocolHandler.h>
#include <BoardLED.h>
#include <SensorPoller.h>
#include <RFReceiver.h>
#include <Arduino.h>


SerialBridge bridge;
ProtocolHandler protocol;
SensorPoller sensors;
RFReceiver rf;

void setup() {
    Serial.begin(9600);

    // Init RF receiver early
    rf.init();

    BoardLED::init();

    bridge.setProtocol(&protocol);
    protocol.setSensorPoller(&sensors);
    protocol.setRFReceiver(&rf);
}

void loop() {
    bridge.loop();
}