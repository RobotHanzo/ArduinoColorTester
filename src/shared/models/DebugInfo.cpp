
#include "DebugInfo.h"


DebugInfo::DebugInfo() {
	brightness = LEDInfo();
	photoresistorReading = int(0);
	esp32 = BoardInfo();
	arduino = BoardInfo();
}

DebugInfo::DebugInfo(String jsonString) {
	this->fromJson(jsonString);
}

DebugInfo::~DebugInfo() {

}

DebugInfo DebugInfo::fromJson(DynamicJsonDocument object) {
    const char *brightnessKey = "brightness";

    if(object.containsKey(brightnessKey)) {
        brightness.fromJson(object[brightnessKey].as<JsonObject>());
    }
    const char *photoresistorReadingKey = "photoresistorReading";

    if(object.containsKey(photoresistorReadingKey)) {
        JsonVariant value = object[photoresistorReadingKey];
        jsonToValue(&photoresistorReading, value, "int");
    }
    const char *esp32Key = "esp32";

    if(object.containsKey(esp32Key)) {
        esp32.fromJson(object[esp32Key].as<JsonObject>());
    }
    const char *arduinoKey = "arduino";

    if(object.containsKey(arduinoKey)) {
        arduino.fromJson(object[arduinoKey].as<JsonObject>());
    }
    return *this;
}

DebugInfo DebugInfo::fromJson(String jsonObj) {
    DynamicJsonDocument object(200);
    deserializeJson(object, jsonObj);
    fromJson(object);
    return *this;
}

DynamicJsonDocument DebugInfo::toJson() {
    DynamicJsonDocument object(200);




	object["brightness"] = getBrightness().toJson();




    object["photoresistorReading"] = getPhotoresistorReading();






	object["esp32"] = getEsp32().toJson();





	object["arduino"] = getArduino().toJson();


    return object;

}

LEDInfo
DebugInfo::getBrightness()
{
	return brightness;
}

void
DebugInfo::setBrightness(LEDInfo  brightness)
{
	this->brightness = brightness;
}

int
DebugInfo::getPhotoresistorReading()
{
	return photoresistorReading;
}

void
DebugInfo::setPhotoresistorReading(int  photoresistorReading)
{
	this->photoresistorReading = photoresistorReading;
}

BoardInfo
DebugInfo::getEsp32()
{
	return esp32;
}

void
DebugInfo::setEsp32(BoardInfo  esp32)
{
	this->esp32 = esp32;
}

BoardInfo
DebugInfo::getArduino()
{
	return arduino;
}

void
DebugInfo::setArduino(BoardInfo  arduino)
{
	this->arduino = arduino;
}



