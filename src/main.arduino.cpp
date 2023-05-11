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
                    ledInfo.fromJson(data);
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
                              (new ReadPhotoResistorReply(analogRead(configuration.photoResistorPort)))->toJson());
                    break;
                case InvalidEvent://TODO
                    break;
                default:
                    sendEvent(softwareSerial, InvalidEvent, ((new InvalidEventReply(message))->toJson()));
                    break;
            }
        }
    }
    if (rickRolling) {
        rickRoll(configuration);
    }
}