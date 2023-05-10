
#include "ScanProfile.h"


ScanProfile::ScanProfile() {
	brightness = int(0);
	scanTimes = int(0);
	scanInterval = int(0);
}

ScanProfile::ScanProfile(String jsonString) {
	this->fromJson(jsonString);
}

ScanProfile::~ScanProfile() {

}

ScanProfile ScanProfile::fromJson(DynamicJsonDocument object) {
    const char *brightnessKey = "brightness";

    if(object.containsKey(brightnessKey)) {
        JsonVariant value = object[brightnessKey];
        jsonToValue(&brightness, value, "int");
    }
    const char *scanTimesKey = "scanTimes";

    if(object.containsKey(scanTimesKey)) {
        JsonVariant value = object[scanTimesKey];
        jsonToValue(&scanTimes, value, "int");
    }
    const char *scanIntervalKey = "scanInterval";

    if(object.containsKey(scanIntervalKey)) {
        JsonVariant value = object[scanIntervalKey];
        jsonToValue(&scanInterval, value, "int");
    }
    return *this;
}

ScanProfile ScanProfile::fromJson(String jsonObj) {
    DynamicJsonDocument object(200);
    deserializeJson(object, jsonObj);
    fromJson(object);
    return *this;
}

DynamicJsonDocument ScanProfile::toJson() {
    DynamicJsonDocument object(200);



    object["brightness"] = getBrightness();





    object["scanTimes"] = getScanTimes();





    object["scanInterval"] = getScanInterval();



    return object;

}

int
ScanProfile::getBrightness()
{
	return brightness;
}

void
ScanProfile::setBrightness(int  brightness)
{
	this->brightness = brightness;
}

int
ScanProfile::getScanTimes()
{
	return scanTimes;
}

void
ScanProfile::setScanTimes(int  scanTimes)
{
	this->scanTimes = scanTimes;
}

int
ScanProfile::getScanInterval()
{
	return scanInterval;
}

void
ScanProfile::setScanInterval(int  scanInterval)
{
	this->scanInterval = scanInterval;
}



