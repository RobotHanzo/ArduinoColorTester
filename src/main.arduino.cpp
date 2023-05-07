#include <Arduino.h>
#include "shared/Configuration.hpp"
#include "arduino/RickRoll.hpp"

Configuration configuration;
short redLEDBrightness = 0;
short greenLEDBrightness = 0;
short blueLEDBrightness = 0;
bool rickRolling = false;

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
    delay(200);
    pinMode(configuration.redLedPort, OUTPUT);
    pinMode(configuration.greenLedPort, OUTPUT);
    pinMode(configuration.blueLedPort, OUTPUT);
    pinMode(configuration.buzzerPort, OUTPUT);
    pinMode(configuration.photoResistorPort, INPUT);
    EventCodes booted = Booted;
    sendEvent(booted);
}

void loop() {
    analogWrite(configuration.redLedPort, redLEDBrightness);
    analogWrite(configuration.greenLedPort, greenLEDBrightness);
    analogWrite(configuration.blueLedPort, blueLEDBrightness);
    if (Serial.available()) {
        DynamicJsonDocument document(200);
        deserializeJson(document, Serial.readStringUntil('\n'));
        if (document.containsKey("eventCode")) {
            int eventCode = document["eventCode"];
            JsonObject data = document.containsKey("data") ? document["data"] : JsonObject();
            switch (eventCode) {
                case SendLED:
                    if (data.containsKey("red")) {
                        redLEDBrightness = data["red"];
                    }
                    if (data.containsKey("green")) {
                        greenLEDBrightness = data["green"];
                    }
                    if (data.containsKey("blue")) {
                        blueLEDBrightness = data["blue"];
                    }
                    sendAck(SendLED);
                    break;
                case StartScan:
                    sendAck(StartScan);
                    break;
                case RickRoll:
                    rickRolling = !rickRolling;
                    sendAck(RickRoll);
                    break;
                default:
                    sendEvent(InvalidEvent);
                    break;
            }
        }
    }
    if (rickRolling) {
        rickRoll(configuration);
    }
}