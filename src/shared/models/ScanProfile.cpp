

#include "ScanProfile.h"


ScanProfile::ScanProfile() {
    brightness = int(0);
    scanTimes = int(0);
    scanInterval = int(0);
}

ScanProfile::ScanProfile(std::string jsonString) {
    this->fromJson(jsonString);
}

ScanProfile::~ScanProfile() {

}

void
ScanProfile::fromJson(std::string jsonObj) {
    bourne::json object = bourne::json::parse(jsonObj);

    const char *brightnessKey = "brightness";

    if (object.has_key(brightnessKey)) {
        bourne::json value = object[brightnessKey];


        jsonToValue(&brightness, value, "int");


    }

    const char *scanTimesKey = "scanTimes";

    if (object.has_key(scanTimesKey)) {
        bourne::json value = object[scanTimesKey];


        jsonToValue(&scanTimes, value, "int");


    }

    const char *scanIntervalKey = "scanInterval";

    if (object.has_key(scanIntervalKey)) {
        bourne::json value = object[scanIntervalKey];


        jsonToValue(&scanInterval, value, "int");


    }


}

bourne::json
ScanProfile::toJson() {
    bourne::json object = bourne::json::object();


    object["brightness"] = getBrightness();


    object["scanTimes"] = getScanTimes();


    object["scanInterval"] = getScanInterval();


    return object;

}

int
ScanProfile::getBrightness() {
    return brightness;
}

void
ScanProfile::setBrightness(int brightness) {
    this->brightness = brightness;
}

int
ScanProfile::getScanTimes() {
    return scanTimes;
}

void
ScanProfile::setScanTimes(int scanTimes) {
    this->scanTimes = scanTimes;
}

int
ScanProfile::getScanInterval() {
    return scanInterval;
}

void
ScanProfile::setScanInterval(int scanInterval) {
    this->scanInterval = scanInterval;
}



