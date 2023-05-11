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
        DynamicJsonDocument document(200);
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

#endif //ARDUINOCOLORTESTER_DEBUG_HPP
