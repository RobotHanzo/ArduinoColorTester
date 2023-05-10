//
// Created by natha on 5/9/2023.
//

#ifndef ARDUINOCOLORTESTER_DEBUG_HPP
#define ARDUINOCOLORTESTER_DEBUG_HPP

#include "Communication.hpp"

class ReadPhotoResistorReply : public Serializable {
public:
    explicit ReadPhotoResistorReply(int value) {
        this->value = value;
    }

    int value = 0;

    bourne::json toJson() override {
        bourne::json object = bourne::json();
        object["value"] = value;
        return object;
    }

    void fromJson(std::string jsonObj) override {
        bourne::json object = bourne::json::parse(jsonObj);
        value = (int) object["value"].to_int();
    }
};

class InvalidEventReply : public Serializable {
public:
    explicit InvalidEventReply(String value) {
        this->received = value;
    }

    String received;

    bourne::json toJson() override {
        bourne::json object = bourne::json();
        object["received"] = received.c_str();
        return object;
    }

    void fromJson(std::string jsonObj) override {
        bourne::json object = bourne::json::parse(jsonObj);
        received = object["received"].to_string().c_str();
    }
};

#endif //ARDUINOCOLORTESTER_DEBUG_HPP
