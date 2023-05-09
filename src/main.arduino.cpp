#include <Arduino.h>
#include "shared/Configuration.hpp"
#include "arduino/RickRoll.hpp"
#include "arduino/ArduinoConfiguration.hpp"
#include "shared/Debug.hpp"
#include <SoftwareSerial.h>

ArduinoConfiguration configuration;
short redLEDBrightness = 0;
short greenLEDBrightness = 0;
short blueLEDBrightness = 0;
bool rickRolling = false;
SoftwareSerial softwareSerial = *new SoftwareSerial(10, 11);

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600); // For debugging
    softwareSerial.begin(9600);
    delay(200);
    pinMode(configuration.redLedPort, OUTPUT);
    pinMode(configuration.greenLedPort, OUTPUT);
    pinMode(configuration.blueLedPort, OUTPUT);
    pinMode(configuration.buzzerPort, OUTPUT);
    pinMode(configuration.photoResistorPort, INPUT);
    EventCodes booted = Booted;
    sendEvent(softwareSerial, booted);
    sendEvent(booted);
}

void loop() {
    analogWrite(configuration.redLedPort, redLEDBrightness);
    analogWrite(configuration.greenLedPort, greenLEDBrightness);
    analogWrite(configuration.blueLedPort, blueLEDBrightness);
    if (softwareSerial.available()) {
        DynamicJsonDocument document(200);
        String message = softwareSerial.readStringUntil('\n');
        deserializeJson(document, message);
        if (document.containsKey("eventCode")) {
            int eventCode = document["eventCode"];
            JsonObject data = document.containsKey("data") ? document["data"] : JsonObject();
            switch (eventCode) {
                case Booted:
                    sendAck(softwareSerial, Booted);
                    break;
                case SendLEDBrightness:
                    if (data.containsKey("red")) {
                        redLEDBrightness = data["red"];
                    }
                    if (data.containsKey("green")) {
                        greenLEDBrightness = data["green"];
                    }
                    if (data.containsKey("blue")) {
                        blueLEDBrightness = data["blue"];
                    }
                    sendAck(softwareSerial, SendLEDBrightness);
                    break;
                case StartScan:
                    sendAck(softwareSerial, StartScan);
                    break;
                case RickRoll:
                    rickRolling = !rickRolling;
                    sendAck(softwareSerial, RickRoll);
                    break;
                case ReadPhotoResistor:
                    sendReply(softwareSerial, ReadPhotoResistor,
                              *new ReadPhotoResistorReply(analogRead(configuration.photoResistorPort)));
                    break;
                case InvalidEvent://TODO
                    break;
                default:
                    sendEvent(softwareSerial, InvalidEvent, *new InvalidEventReply(message));
                    break;
            }
        }
    }
    if (rickRolling) {
        rickRoll(configuration);
    }
}