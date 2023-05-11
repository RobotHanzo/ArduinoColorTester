//
// Created by natha on 5/6/2023.
//

#ifndef ARDUINOCOLORTESTER_CONFIGURATION_HPP
#define ARDUINOCOLORTESTER_CONFIGURATION_HPP


#include <pins_arduino.h>
#include "ArduinoJson.h"
#include "shared/Communication.hpp"
#include "shared/models/Serializable.h"

class ScanConfiguration : public Serializable<ScanConfiguration> {
public:
    short scanTimes = 20;
    int scanInterval = 50; // ms
    short brightness = 255;

    DynamicJsonDocument toJson() override {
        DynamicJsonDocument document(200);
        document["scanTimes"] = scanTimes;
        document["scanInterval"] = scanInterval;
        document["brightness"] = brightness;
        return document;
    }

    ScanConfiguration fromJson(DynamicJsonDocument document) override {
        scanTimes = document["scanTimes"];
        scanInterval = document["scanInterval"];
        brightness = document["brightness"];
        return *this;
    }

    ScanConfiguration fromJson(String json) override {
        DynamicJsonDocument document(200);
        deserializeJson(document, json);
        return fromJson(document);
    }
};

#endif //ARDUINOCOLORTESTER_CONFIGURATION_HPP
