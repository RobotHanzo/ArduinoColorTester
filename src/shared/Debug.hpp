//
// Created by natha on 5/9/2023.
//

#ifndef ARDUINOCOLORTESTER_DEBUG_HPP
#define ARDUINOCOLORTESTER_DEBUG_HPP
#include "Communication.hpp"
#include "ArduinoJson.h"

class ReadPhotoResistorReply : public Serializable<ReadPhotoResistorReply> {
public:
    ReadPhotoResistorReply(int value) {
        this->value = value;
    }

    int value = 0;

    DynamicJsonDocument toJson() override {
        DynamicJsonDocument document(100);
        document["value"] = value;
        return document;
    }

    ReadPhotoResistorReply fromJson(DynamicJsonDocument document) override {
        value = document["value"].as<int>();
        return *this;
    }

    ReadPhotoResistorReply fromJson(String json) override {
        DynamicJsonDocument document(200);
        deserializeJson(document, json);
        return fromJson(document);
    }
};

class InvalidEventReply : public Serializable<InvalidEventReply> {
public:
    InvalidEventReply(String value) {
        this->received = value;
    }

    String received;

    DynamicJsonDocument toJson() override {
        DynamicJsonDocument document(200);
        document["received"] = received;
        return document;
    }

    InvalidEventReply fromJson(DynamicJsonDocument document) override {
        received = document["received"].as<String>();
        return *this;
    }

    InvalidEventReply fromJson(String json) override {
        DynamicJsonDocument document(200);
        deserializeJson(document, json);
        return fromJson(document);
    }
};

class ReadBoardInfoReply : public Serializable<ReadBoardInfoReply> {
public:
    ReadBoardInfoReply(unsigned long uptime, float temperature) {
        this->uptime = uptime;
        this->temperature = temperature;
    }

    unsigned long uptime = 0;
    float temperature = 0;

    DynamicJsonDocument toJson() override {
        DynamicJsonDocument document(100);
        document["uptime"] = uptime;
        document["temperature"] = temperature;
        return document;
    }

    ReadBoardInfoReply fromJson(DynamicJsonDocument document) override {
        uptime = document["uptime"].as<unsigned long>();
        temperature = document["temperature"].as<float>();
        return *this;
    }

    ReadBoardInfoReply fromJson(String json) override {
        DynamicJsonDocument document(200);
        deserializeJson(document, json);
        return fromJson(document);
    }
};

#endif //ARDUINOCOLORTESTER_DEBUG_HPP
