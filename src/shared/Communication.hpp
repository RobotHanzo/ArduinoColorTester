//
// Created by natha on 5/7/2023.
//

#ifndef ARDUINOCOLORTESTER_COMMUNICATION_HPP
#define ARDUINOCOLORTESTER_COMMUNICATION_HPP

#include "ArduinoJson.h"
#include "shared/models/Serializable.h"

enum EventCodes {
    Booted = 0,
    Acknowledged = 1,
    Reply = 2,
//    ScanStarted = 10, This is replaced with Ack. for now, since tasks are handled in ESP32
    ScanFinished = 11,
    ScanCanceled = 12,
    ScanAborted = 13,
    StartScan = 100,
    CancelScan = 101,
    AbortScan = 102,
    Shutdown = 103,
    SendLEDBrightness = 200,
    RickRoll = 201,
    ReadLEDBrightness = 212,
    ReadPhotoResistor = 213,
    InvalidEvent = 255
};

class LEDBrightness : public Serializable<LEDBrightness> {
public:
    LEDBrightness(short r, short g, short b) {
        red = r;
        green = g;
        blue = b;
    }

    short red = 0;
    short green = 0;
    short blue = 0;

    DynamicJsonDocument toJson() override {
        DynamicJsonDocument document(200);
        document["red"] = red;
        document["green"] = green;
        document["blue"] = blue;
        return document;
    }

    LEDBrightness fromJson(String json) override {
        DynamicJsonDocument document(200);
        deserializeJson(document, json);
        red = document["red"];
        green = document["green"];
        blue = document["blue"];
        return *this;
    }

    LEDBrightness fromJson(DynamicJsonDocument doc) override {
        red = doc["red"];
        green = doc["green"];
        blue = doc["blue"];
        return *this;
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

void sendReply(EventCodes eventCode, Serializable<JsonObject> &data) {
    DynamicJsonDocument document(200);
    document["eventCode"] = Reply;
    JsonObject d = document.createNestedObject("data");
    d["code"] = eventCode;
    d["data"] = data.toJson();
    serializeJson(document, Serial);
    Serial.println();
}

void sendReply(Stream &s, EventCodes eventCode, Serializable<JsonObject> &data) {
    DynamicJsonDocument document(200);
    document["eventCode"] = Reply;
    JsonObject d = document.createNestedObject("data");
    d["code"] = eventCode;
    d["data"] = data.toJson();
    serializeJson(document, s);
    s.println();
}

void sendEvent(EventCodes eventCode, Serializable<JsonObject> &data) {
    DynamicJsonDocument document(200);
    document["eventCode"] = eventCode;
    document["data"] = data.toJson();
    serializeJson(document, Serial);
    Serial.println();
}

void sendEvent(Stream &s, EventCodes eventCode, Serializable<JsonObject> &data) {
    DynamicJsonDocument document(200);
    document["eventCode"] = eventCode;
    document["data"] = data.toJson();
    serializeJson(document, s);
    s.println();
}

#endif //ARDUINOCOLORTESTER_COMMUNICATION_HPP


