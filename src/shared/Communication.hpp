//
// Created by natha on 5/7/2023.
//

#ifndef ARDUINOCOLORTESTER_COMMUNICATION_HPP
#define ARDUINOCOLORTESTER_COMMUNICATION_HPP

#include "ArduinoJson.h"

class Serializable {
public:
    virtual DynamicJsonDocument serialize() = 0;
};

enum EventCodes {
    Booted = 0,
    Acknowledged = 1, // This will be ignored in arduino_esp32 for now
//    ScanStarted = 10, This is replaced with Ack. for now, since tasks are handled in ESP32
    ScanFinished = 11,
    ScanCanceled = 12,
    ScanAborted = 13,
    StartScan = 100,
    CancelScan = 101,
    AbortScan = 102,
    Shutdown = 103,
    SendLED = 200,
    RickRoll = 201,
    InvalidEvent = 255
};

class LEDBrightness: public Serializable {
public:
    LEDBrightness(short r, short g, short b) {
        red = r;
        green = g;
        blue = b;
    }

    short red = 0;
    short green = 0;
    short blue = 0;

    DynamicJsonDocument serialize() override {
        DynamicJsonDocument document(200);
        document["red"] = red;
        document["green"] = green;
        document["blue"] = blue;
        return document;
    }
};

void sendEvent(EventCodes eventCode) {
    DynamicJsonDocument document(200);
    document["eventCode"] = eventCode;
    serializeJson(document, Serial);
    Serial.println();
}

void sendEvent(Stream &s, EventCodes eventCode) {
    DynamicJsonDocument document(200);
    document["eventCode"] = eventCode;
    serializeJson(document, s);
    s.println();
}

void sendAck(EventCodes eventCode) {
    DynamicJsonDocument document(200);
    document["eventCode"] = Acknowledged;
    document.createNestedObject("data")["code"] = eventCode;
    serializeJson(document, Serial);
    Serial.println();
}

void sendAck(Stream &s, EventCodes eventCode) {
    DynamicJsonDocument document(200);
    document["eventCode"] = Acknowledged;
    document.createNestedObject("data")["code"] = eventCode;
    serializeJson(document, s);
    s.println();
}

void sendEvent(EventCodes eventCode, Serializable& data) {
    DynamicJsonDocument document(200);
    document["eventCode"] = eventCode;
    document["data"] = data.serialize();
    serializeJson(document, Serial);
    Serial.println();
}

void sendEvent(Stream &s, EventCodes eventCode, Serializable& data) {
    DynamicJsonDocument document(200);
    document["eventCode"] = eventCode;
    document["data"] = data.serialize();
    serializeJson(document, s);
    s.println();
}

#endif //ARDUINOCOLORTESTER_COMMUNICATION_HPP


