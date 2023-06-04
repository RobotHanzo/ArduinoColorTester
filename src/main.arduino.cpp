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
int iteration = 0;

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
                    scanStep = RedLight;
                    sendAck(softwareSerial, StartScan);
                    Serial.println("test: " + message);
                    sendEvent(StartScan, scanProfile.toJson());
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
                break;
            }
            case RedRead: {
                scanningData.setR(analogRead(PHOTO_RESISTOR_PORT));
                scanStep = GreenLight;
                break;
            }
            case GreenLight: {
                ledInfo.setR(0);
                ledInfo.setG(scanProfile.getBrightness());
                ledInfo.setB(0);
                scanStep = GreenRead;
                break;
            }
            case GreenRead: {
                scanningData.setG(analogRead(PHOTO_RESISTOR_PORT));
                scanStep = BlueLight;
                break;
            }
            case BlueLight: {
                ledInfo.setR(0);
                ledInfo.setG(0);
                ledInfo.setB(scanProfile.getBrightness());
                scanStep = BlueRead;
                break;
            }
            case BlueRead: {
                scanningData.setB(analogRead(PHOTO_RESISTOR_PORT));
                scanStep = RedLight;
                sendEvent(Serial, CollectScanData, scanningData.toJson());
                sendEvent(softwareSerial, CollectScanData, scanningData.toJson());
                if (scanProfile.getScanTimes() - 1 > iteration) {
                    iteration++;
                } else {
                    ScanResult scanResult = ScanResult();
                    scanning = false;
                    scanResult.setProfile(scanProfile);
                    sendEvent(softwareSerial, ScanFinished, scanResult.toJson());
//                    delete &scanProfile;
//                    delete &scanResult;
                    ledInfo.setR(0);
                    ledInfo.setG(0);
                    ledInfo.setB(0);
                    iteration = 0;
                }
                break;
            }
        }
        delay(scanProfile.getScanInterval());
    }
//    We don't have memory for this
//    if (rickRolling) {
//        rickRoll(BUZZER_PORT);
//    }
}