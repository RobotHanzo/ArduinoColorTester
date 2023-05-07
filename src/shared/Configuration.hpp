//
// Created by natha on 5/6/2023.
//

#ifndef ARDUINOCOLORTESTER_CONFIGURATION_HPP
#define ARDUINOCOLORTESTER_CONFIGURATION_HPP


#include <pins_arduino.h>
#include "ArduinoJson.h"
#include "shared/Communication.hpp"

class Configuration {
public:
    uint8_t redLedPort = 3;
    uint8_t greenLedPort = 5;
    uint8_t blueLedPort = 6;
    uint8_t buzzerPort = 9;
    uint8_t photoResistorPort = A0;
};

class ScanConfiguration: public Serializable{
public:
    short scanTimes = 20;
    int scanInterval = 50; // ms
    short brightness = 255;

    DynamicJsonDocument serialize() override {
        DynamicJsonDocument document(200);
        document["scanTimes"] = scanTimes;
        document["scanInterval"] = scanInterval;
        document["brightness"] = brightness;
        return document;
    }

    static ScanConfiguration deserialize(JsonDocument document) {
        ScanConfiguration config;
        config.scanTimes = document["scanTimes"];
        config.scanInterval = document["scanInterval"];
        config.brightness = document["brightness"];
        return config;
    }
};

#endif //ARDUINOCOLORTESTER_CONFIGURATION_HPP
