//
// Created by natha on 5/8/2023.
//

#ifndef ARDUINOCOLORTESTER_ARDUINOCONFIGURATION_HPP
#define ARDUINOCOLORTESTER_ARDUINOCONFIGURATION_HPP

#include "shared/Communication.hpp"
#include "ArduinoJson.h"
#include "ArduinoConfiguration.hpp"
#include <pins_arduino.h>

class ArduinoConfiguration {
public:
    unsigned char redLedPort = 3;
    unsigned char greenLedPort = 5;
    unsigned char blueLedPort = 6;
    unsigned char buzzerPort = 9;
    unsigned char photoResistorPort = A0;
};

#endif //ARDUINOCOLORTESTER_ARDUINOCONFIGURATION_HPP
