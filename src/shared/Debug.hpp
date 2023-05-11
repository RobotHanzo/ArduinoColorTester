//
// Created by natha on 5/9/2023.
//

#ifndef ARDUINOCOLORTESTER_DEBUG_HPP
#define ARDUINOCOLORTESTER_DEBUG_HPP
#include "Communication.hpp"
#include "ArduinoJson.h"

class ReadPhotoResistorReply : public Serializable {
public:
    ReadPhotoResistorReply(int value) {
        this->value = value;
    }

    int value = 0;

    DynamicJsonDocument serialize() override {
        DynamicJsonDocument document(200);
        document["value"] = value;
        return document;
    }
};

class InvalidEventReply : public Serializable {
public:
    InvalidEventReply(String value) {
        this->received = value;
    }

    String received;

    DynamicJsonDocument serialize() override {
        DynamicJsonDocument document(200);
        document["received"] = received;
        return document;
    }
};

#endif //ARDUINOCOLORTESTER_DEBUG_HPP
