

#include "DebugInfo.h"


DebugInfo::DebugInfo() {
    brightness = LEDInfo();
    photoresistorReading = int(0);
    esp32 = BoardInfo();
    arduino = BoardInfo();
}

DebugInfo::DebugInfo(std::string jsonString) {
    this->fromJson(jsonString);
}

DebugInfo::~DebugInfo() {

}

void
DebugInfo::fromJson(std::string jsonObj) {
    bourne::json object = bourne::json::parse(jsonObj);

    const char *brightnessKey = "brightness";

    if (object.has_key(brightnessKey)) {
        bourne::json value = object[brightnessKey];


        LEDInfo *obj = &brightness;
        obj->fromJson(value.dump());

    }

    const char *photoresistorReadingKey = "photoresistorReading";

    if (object.has_key(photoresistorReadingKey)) {
        bourne::json value = object[photoresistorReadingKey];


        jsonToValue(&photoresistorReading, value, "int");


    }

    const char *esp32Key = "esp32";

    if (object.has_key(esp32Key)) {
        bourne::json value = object[esp32Key];


        BoardInfo *obj = &esp32;
        obj->fromJson(value.dump());

    }

    const char *arduinoKey = "arduino";

    if (object.has_key(arduinoKey)) {
        bourne::json value = object[arduinoKey];


        BoardInfo *obj = &arduino;
        obj->fromJson(value.dump());

    }


}

bourne::json
DebugInfo::toJson() {
    bourne::json object = bourne::json::object();


    object["brightness"] = getBrightness().toJson();


    object["photoresistorReading"] = getPhotoresistorReading();


    object["esp32"] = getEsp32().toJson();


    object["arduino"] = getArduino().toJson();


    return object;

}

LEDInfo
DebugInfo::getBrightness() {
    return brightness;
}

void
DebugInfo::setBrightness(LEDInfo brightness) {
    this->brightness = brightness;
}

int
DebugInfo::getPhotoresistorReading() {
    return photoresistorReading;
}

void
DebugInfo::setPhotoresistorReading(int photoresistorReading) {
    this->photoresistorReading = photoresistorReading;
}

BoardInfo
DebugInfo::getEsp32() {
    return esp32;
}

void
DebugInfo::setEsp32(BoardInfo esp32) {
    this->esp32 = esp32;
}

BoardInfo
DebugInfo::getArduino() {
    return arduino;
}

void
DebugInfo::setArduino(BoardInfo arduino) {
    this->arduino = arduino;
}



