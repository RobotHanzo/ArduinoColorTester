
#include "SerialEventData.h"


SerialEventData::SerialEventData() {
	eventCode = int(0);
}

SerialEventData::SerialEventData(String jsonString) {
	this->fromJson(jsonString);
}

SerialEventData::~SerialEventData() {

}

SerialEventData SerialEventData::fromJson(DynamicJsonDocument object) {
    const char *eventCodeKey = "eventCode";

    if(object.containsKey(eventCodeKey)) {
        JsonVariant value = object[eventCodeKey];
        jsonToValue(&eventCode, value, "int");
    }
    return *this;
}

SerialEventData SerialEventData::fromJson(String jsonObj) {
    DynamicJsonDocument object(200);
    deserializeJson(object, jsonObj);
    fromJson(object);
    return *this;
}

DynamicJsonDocument SerialEventData::toJson() {
    DynamicJsonDocument object(200);



    object["eventCode"] = getEventCode();



    return object;

}

int
SerialEventData::getEventCode()
{
	return eventCode;
}

void
SerialEventData::setEventCode(int  eventCode)
{
	this->eventCode = eventCode;
}



