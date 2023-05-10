//
// Created by natha on 5/6/2023.
//

#ifndef ARDUINOCOLORTESTER_CONFIGURATION_HPP
#define ARDUINOCOLORTESTER_CONFIGURATION_HPP


#include <pins_arduino.h>
#include "shared/Communication.hpp"

class ScanConfiguration : public Serializable {
public:
    short scanTimes = 20;
    int scanInterval = 50; // ms
    short brightness = 255;

    bourne::json toJson() override {
        bourne::json object = bourne::json();
        object["scanTimes"] = scanTimes;
        object["scanInterval"] = scanInterval;
        object["brightness"] = brightness;
        return object;
    }

    void fromJson(std::string jsonObj) override {
        bourne::json object = bourne::json::parse(jsonObj);
        scanTimes = (short) object["scanTimes"].to_int();
        scanInterval = (int) object["scanInterval"].to_int();
        brightness = (short) object["brightness"].to_int();
    }
};

#endif //ARDUINOCOLORTESTER_CONFIGURATION_HPP
