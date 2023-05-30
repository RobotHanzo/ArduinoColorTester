#include <Arduino.h>
#include "shared/Configuration.hpp"
#include "arduino/RickRoll.hpp"
#include "shared/Debug.hpp"
#include "shared/models/LEDInfo.h"
#include "../.pio/libdeps/uno/ArduinoSTL/src/serstream"
#include "shared/models/ScanProfile.h"
#include "shared/models/ScanResult.h"
#include "arduino/ScanStep.hpp"
#include <SoftwareSerial.h>
#define MAX_BRIGHTNESS 1024
#define RED_LED_PORT 3
#define GREEN_LED_PORT 5
#define BLUE_LED_PORT 6
#define BUZZER_PORT 9
#define PHOTO_RESISTOR_PORT A0

LEDInfo ledInfo;
bool rickRolling = false;
SoftwareSerial softwareSerial = *new SoftwareSerial(10, 11);
bool scanning = false;
ScanStep scanStep = RedLight;
ScanProfile scanProfile;
ScanResultData scanningData = ScanResultData();

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600); // For debugging
    softwareSerial.begin(9600);
    delay(200);
    pinMode(RED_LED_PORT, OUTPUT);
    pinMode(GREEN_LED_PORT, OUTPUT);
    pinMode(BLUE_LED_PORT, OUTPUT);
    pinMode(BUZZER_PORT, OUTPUT);
    pinMode(PHOTO_RESISTOR_PORT, INPUT);
    EventCodes booted = Booted;
    sendEvent(softwareSerial, booted);
    sendEvent(booted);
}

void loop() {
    analogWrite(RED_LED_PORT, ledInfo.getR());
    analogWrite(GREEN_LED_PORT, ledInfo.getG());
    analogWrite(BLUE_LED_PORT, ledInfo.getB());

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
                    ReadPhotoResistorReply reply(analogRead(PHOTO_RESISTOR_PORT));
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
                scanningData.setR(analogRead(PHOTO_RESISTOR_PORT) / MAX_BRIGHTNESS * 255);
                scanStep = GreenLight;
            }
            case GreenLight: {
                ledInfo.setR(0);
                ledInfo.setG(scanProfile.getBrightness());
                ledInfo.setB(0);
                scanStep = GreenRead;
            }
            case GreenRead: {
                scanningData.setG(analogRead(PHOTO_RESISTOR_PORT) / MAX_BRIGHTNESS * 255);
                scanStep = BlueLight;
            }
            case BlueLight: {
                ledInfo.setR(0);
                ledInfo.setG(0);
                ledInfo.setB(scanProfile.getBrightness());
                scanStep = BlueRead;
            }
            case BlueRead: {
                scanningData.setB(analogRead(PHOTO_RESISTOR_PORT) / MAX_BRIGHTNESS * 255);
                scanStep = RedLight;
                sendEvent(softwareSerial, CollectScanData, scanningData.toJson());
                if (scanProfile.getScanTimes() > 1) {
                    scanProfile.setScanTimes(scanProfile.getScanTimes() - 1);
                } else {
                    ScanResult scanResult = ScanResult();
                    scanning = false;
                    scanResult.setProfile(scanProfile);
                    scanResult.setBrief(ScanResultBrief().fromResults(scanResult.getResults()));
                    sendEvent(softwareSerial, ScanFinished, scanResult.toJson());
                    delete &scanProfile;
                }
            }
        }
        delay(scanProfile.getScanInterval());
    }
//    We don't have memory for this
//    if (rickRolling) {
//        rickRoll(BUZZER_PORT);
//    }
}