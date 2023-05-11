//
// Created by natha on 5/6/2023.
//

#ifndef ARDUINOCOLORTESTER_CONFIGURATION_HPP
#define ARDUINOCOLORTESTER_CONFIGURATION_HPP


#include <pins_arduino.h>
#include "ArduinoJson.h"
#include "shared/Communication.hpp"

class ScanConfiguration : public Serializable {
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
