//
// Created by natha on 5/7/2023.
//

#ifndef ARDUINOCOLORTESTER_COMMUNICATION_HPP
#define ARDUINOCOLORTESTER_COMMUNICATION_HPP

#include "bourne/json.hpp"
#include "Arduino.h"
#include "Serializable.h"

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

int enum_to_int(EventCodes eventCode) {
    return static_cast<int>(eventCode);
}

void sendEvent(Stream &s, EventCodes eventCode) {
    bourne::json j = {"eventCode", &eventCode};
    s.println(j.dump().c_str());
}

void sendEvent(EventCodes eventCode) {
    sendEvent(Serial, eventCode);
}

void sendAck(Stream &s, EventCodes eventCode) {
    bourne::json j = {"eventCode", enum_to_int(Acknowledged), "data", bourne::json({"code", &eventCode})};
    s.println(j.dump().c_str());
}

void sendAck(EventCodes eventCode) {
    sendAck(Serial, eventCode);
}

void sendReply(Stream &s, EventCodes eventCode, Serializable &data) {
    bourne::json j = {"eventCode", enum_to_int(Reply), "data",
                      bourne::json({"code", enum_to_int(eventCode), "data", data.toJson()})};
    s.println(j.dump().c_str());
}

void sendReply(EventCodes eventCode, Serializable &data) {
    sendReply(Serial, eventCode, data);
}

void sendEvent(Stream &s, EventCodes eventCode, Serializable &data) {
    bourne::json j = {"eventCode", enum_to_int(eventCode), "data", data.toJson()};
    s.println(j.dump().c_str());
}

void sendEvent(EventCodes eventCode, Serializable &data) {
    sendEvent(Serial, eventCode, data);
}


#endif //ARDUINOCOLORTESTER_COMMUNICATION_HPP


