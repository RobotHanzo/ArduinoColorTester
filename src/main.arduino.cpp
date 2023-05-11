#include <Arduino.h>
#include "shared/Configuration.hpp"
#include "arduino/RickRoll.hpp"
#include "arduino/ArduinoConfiguration.hpp"
#include "shared/Debug.hpp"
#include "shared/models/LEDInfo.h"
#include <SoftwareSerial.h>

ArduinoConfiguration configuration;
LEDInfo ledInfo;
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
    analogWrite(configuration.redLedPort, ledInfo.getR());
    analogWrite(configuration.greenLedPort, ledInfo.getG());
    analogWrite(configuration.blueLedPort, ledInfo.getB());
    if (softwareSerial.available()) { //TODO migrate to bourne for JSON parsing & use models
        String message = softwareSerial.readStringUntil('\n');
        bourne::json document = bourne::json::parse(message.c_str());
        if (document.has_key("eventCode")) {
            int eventCode = (int) document["eventCode"].to_int();
            bourne::json data = document.has_key("data") ? document["data"] : bourne::json();
            switch (eventCode) {
                case Booted:
                    sendAck(softwareSerial, Booted);
                    break;
                case SendLEDBrightness: {
                    LEDInfo ledInfo = LEDInfo();
                    ledInfo.fromJson(data.dump());
                    sendAck(softwareSerial, SendLEDBrightness);
                    break;
                }
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