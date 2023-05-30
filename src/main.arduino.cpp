#include <Arduino.h>
#include "shared/Configuration.hpp"
#include "arduino/RickRoll.hpp"
#include "arduino/ArduinoConfiguration.hpp"
#include "shared/Debug.hpp"
#include "shared/models/LEDInfo.h"
#include "../.pio/libdeps/uno/ArduinoSTL/src/serstream"
#include "shared/models/ScanProfile.h"
#include "shared/models/ScanResult.h"
#include "arduino/ScanStep.hpp"
#include <SoftwareSerial.h>

#define MAX_BRIGHTNESS 1024

ArduinoConfiguration configuration;
LEDInfo ledInfo;
bool rickRolling = false;
SoftwareSerial softwareSerial = *new SoftwareSerial(10, 11);
bool scanning = false;
ScanStep scanStep = RedLight;
ScanResult *scanResult;
int currentR = 0;
int currentG = 0;
int currentB = 0;

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
    Serial.println(analogRead(configuration.photoResistorPort));
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
                case Booted: {
                    sendAck(softwareSerial, Booted);
                    break;
                }
                case SendLEDBrightness: {
                    ledInfo.fromJson(data);
                    sendAck(softwareSerial, SendLEDBrightness);
                    break;
                }
                case StartScan: {
                    auto scanProfile = new ScanProfile;
                    scanProfile->fromJson(data);
                    scanResult = new ScanResult;
                    scanning = true;
                    sendAck(softwareSerial, StartScan);
                    break;
                }
                case RickRoll: {
                    rickRolling = !rickRolling;
                    sendAck(softwareSerial, RickRoll);
                    break;
                }
                case ReadPhotoResistor: {
                    // We can't use the new keyword since it will cause heap fragmentation
                    ReadPhotoResistorReply reply(analogRead(configuration.photoResistorPort));
                    sendReply(Serial, ReadPhotoResistor, reply.toJson());
                    sendReply(softwareSerial, ReadPhotoResistor, reply.toJson());
                    break;
                }
                case ReadBoardInfo: {
                    // temperature sensor is not accurate, we use 0 as a placeholder for now
                    ReadBoardInfoReply reply(millis(), 0);
                    sendReply(softwareSerial, ReadBoardInfo, reply.toJson());
                    break;
                }
                case InvalidEvent://TODO
                    break;
                default: {
                    InvalidEventReply reply(message);
                    sendEvent(softwareSerial, InvalidEvent, reply.toJson());
                    break;
                }
            }
        }
    }
//    if (scanning) {
//        switch (scanStep) {
//            case RedLight: {
//                ledInfo.setR(scanResult->getProfile()->getBrightness());
//                ledInfo.setG(0);
//                ledInfo.setB(0);
//                scanStep = RedRead;
//                break;
//            }
//            case RedRead: {
//                Serial.println("a: " + String(analogRead(configuration.photoResistorPort) / MAX_BRIGHTNESS * 255));
//                currentR = analogRead(configuration.photoResistorPort) / MAX_BRIGHTNESS * 255;
//                scanStep = GreenLight;
//                break;
//            }
//            case GreenLight: {
//                ledInfo.setR(0);
//                ledInfo.setG(scanResult->getProfile()->getBrightness());
//                ledInfo.setB(0);
//                scanStep = GreenRead;
//                break;
//            }
//            case GreenRead: {
//                currentG = analogRead(configuration.photoResistorPort) / MAX_BRIGHTNESS * 255;
//                scanStep = BlueLight;
//                break;
//            }
//            case BlueLight: {
//                ledInfo.setR(0);
//                ledInfo.setG(0);
//                ledInfo.setB(scanResult->getProfile()->getBrightness());
//                scanStep = BlueRead;
//                break;
//            }
//            case BlueRead: {
//                currentB = analogRead(configuration.photoResistorPort) / MAX_BRIGHTNESS * 255;
//                scanStep = RedLight;
//                Serial.println(currentR);
//                Serial.println(currentG);
//                Serial.println(currentB);
//                auto scanningData = new ScanResultData(&currentR, &currentG, &currentB);
//                scanResult->getResults()->push_back(*scanningData);
//                serializeJson(scanningData->toJson(), Serial);
//                Serial.println();
//                if (scanResult->getProfile()->getScanTimes() >= 1) {
//                    scanResult->getProfile()->setScanTimes(scanResult->getProfile()->getScanTimes() - 1);
//                } else {
//                    scanning = false;
//                    ScanResultBrief *brief = new ScanResultBrief();
//                    sendEvent(Serial, ScanFinished, brief->toJson());
//                    auto test = scanResult->getResults();
//                    sendEvent(Serial, ScanFinished, test->begin()->toJson());
//                    brief->fromResults(scanResult->getResults());
//                    scanResult->setBrief(brief);
//                    sendEvent(Serial, ScanFinished, brief->toJson());
//                    sendEvent(Serial, ScanFinished, scanResult->toJson());
//                    sendEvent(softwareSerial, ScanFinished, scanResult->toJson());
//                    delete scanResult;
//                }
//                break;
//            }
//        }
//        delay(scanResult->getProfile()->getScanInterval());
//    }
    if (rickRolling) {
        rickRoll(configuration);
    }
}