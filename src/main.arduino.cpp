#include <Arduino.h>
#include "shared/Configuration.hpp"
#include "arduino/RickRoll.hpp"
#include "arduino/ArduinoConfiguration.hpp"
#include <SoftwareSerial.h>

ArduinoConfiguration configuration;
short redLEDBrightness = 0;
short greenLEDBrightness = 0;
short blueLEDBrightness = 0;
bool rickRolling = false;
SoftwareSerial softwareSerial = *new SoftwareSerial(10, 11);

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    softwareSerial.begin(9600);
//    delay(200);
    pinMode(configuration.redLedPort, OUTPUT);
    pinMode(configuration.greenLedPort, OUTPUT);
    pinMode(configuration.blueLedPort, OUTPUT);
    pinMode(configuration.buzzerPort, OUTPUT);
    pinMode(configuration.photoResistorPort, INPUT);
    EventCodes booted = Booted;
    sendEvent(softwareSerial, booted);
}

void loop() {
    analogWrite(configuration.redLedPort, redLEDBrightness);
    analogWrite(configuration.greenLedPort, greenLEDBrightness);
    analogWrite(configuration.blueLedPort, blueLEDBrightness);
    if (softwareSerial.available()) {
        DynamicJsonDocument document(200);
        deserializeJson(document, softwareSerial.readStringUntil('\n'));
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
                    sendAck(softwareSerial, SendLED);
                    break;
                case StartScan:
                    sendAck(softwareSerial, StartScan);
                    break;
                case RickRoll:
                    rickRolling = !rickRolling;
                    sendAck(softwareSerial, RickRoll);
                    break;
                default:
                    sendEvent(softwareSerial, InvalidEvent);
                    break;
            }
        }
    }
    if (rickRolling) {
        rickRoll(configuration);
    }
}