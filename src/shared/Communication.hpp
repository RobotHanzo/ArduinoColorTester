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
    CollectScanData = 14, // We have to let ESP32 store the vector because arduino doesn't have enough RAM
    StartScan = 100,
    CancelScan = 101,
    AbortScan = 102,
    Shutdown = 103,
    SendLEDBrightness = 200,
    RickRoll = 201,
    ReadLEDBrightness = 212,
    ReadPhotoResistor = 213,
    ReadBoardInfo = 214,
    InvalidEvent = 255
};

int enum_to_int(EventCodes eventCode) {
    return static_cast<int>(eventCode);
}

void sendEvent(Stream &s, EventCodes eventCode) {
    DynamicJsonDocument document(200);
    document["eventCode"] = enum_to_int(eventCode);
    serializeJson(document, s);
    s.println();
}

void sendEvent(EventCodes eventCode) {
    sendEvent(Serial, eventCode);
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

void sendReply(EventCodes eventCode, const JsonVariant &data) {
    DynamicJsonDocument document(200);
    document["eventCode"] = Reply;
    document["code"] = eventCode;
    document["data"] = data;
    serializeJson(document, Serial);
    Serial.println();
}

void sendReply(Stream &s, EventCodes eventCode, const JsonVariant &data) {
    DynamicJsonDocument document(200);
    document["eventCode"] = Reply;
    document["code"] = eventCode;
    document["data"] = data;
    serializeJson(document, s);
    s.println();
}

void sendEvent(EventCodes eventCode, const JsonVariant &data) {
    DynamicJsonDocument document(200);
    document["eventCode"] = enum_to_int(eventCode);
    document["data"] = data;
    serializeJson(document, Serial);
    Serial.println();
}

void sendEvent(Stream &s, EventCodes eventCode, const JsonDocument &data) {
    DynamicJsonDocument document(200);
    document["eventCode"] = enum_to_int(eventCode);
    document["data"] = data;
    serializeJson(document, s);
    s.println();
}

#endif //ARDUINOCOLORTESTER_COMMUNICATION_HPP


