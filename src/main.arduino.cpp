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
ScanProfile scanProfile;
ScanResult scanResult;
ScanResultData scanningData = ScanResultData();

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
                    scanProfile = ScanProfile();
                    scanProfile.fromJson(data);
                    scanResult = ScanResult();
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
    if (scanning) {
        switch (scanStep) {
            case RedLight: {
                ledInfo.setR(scanProfile.getBrightness());
                ledInfo.setG(0);
                ledInfo.setB(0);
                scanStep = RedRead;
            }
            case RedRead: {
                scanningData.setR(analogRead(configuration.photoResistorPort) / MAX_BRIGHTNESS * 255);
                scanStep = GreenLight;
            }
            case GreenLight: {
                ledInfo.setR(0);
                ledInfo.setG(scanProfile.getBrightness());
                ledInfo.setB(0);
                scanStep = GreenRead;
            }
            case GreenRead: {
                scanningData.setG(analogRead(configuration.photoResistorPort) / MAX_BRIGHTNESS * 255);
                scanStep = BlueLight;
            }
            case BlueLight: {
                ledInfo.setR(0);
                ledInfo.setG(0);
                ledInfo.setB(scanProfile.getBrightness());
                scanStep = BlueRead;
            }
            case BlueRead: {
                scanningData.setB(analogRead(configuration.photoResistorPort) / MAX_BRIGHTNESS * 255);
                scanStep = RedLight;
                scanResult.getResults().push_back(scanningData);
                if (scanProfile.getScanTimes() > 1) {
                    scanProfile.setScanTimes(scanProfile.getScanTimes() - 1);
                } else {
                    scanning = false;
                    scanResult.setProfile(scanProfile);
                    scanResult.setBrief(ScanResultBrief().fromResults(scanResult.getResults()));
                    sendEvent(softwareSerial, ScanFinished, scanResult.toJson());
                    delete &scanResult;
                    delete &scanProfile;
                }
            }
        }
        delay(scanProfile.getScanInterval());
    }
    if (rickRolling) {
        rickRoll(configuration);
    }
}