
#include "SerialEvent.h"


SerialEvent::SerialEvent() {
	eventCode = int(0);
	data = SerialEventData();
}

SerialEvent::SerialEvent(String jsonString) {
	this->fromJson(jsonString);
}

SerialEvent::~SerialEvent() {

}

SerialEvent SerialEvent::fromJson(DynamicJsonDocument object) {
    const char *eventCodeKey = "eventCode";

    if(object.containsKey(eventCodeKey)) {
        JsonVariant value = object[eventCodeKey];
        jsonToValue(&eventCode, value, "int");
    }
    const char *dataKey = "data";

    if(object.containsKey(dataKey)) {
        data.fromJson(object[dataKey].as<JsonObject>());
    }
    return *this;
}

SerialEvent SerialEvent::fromJson(String jsonObj) {
    DynamicJsonDocument object(200);
    deserializeJson(object, jsonObj);
    fromJson(object);
    return *this;
}

DynamicJsonDocument SerialEvent::toJson() {
    DynamicJsonDocument object(200);



    object["eventCode"] = getEventCode();






	object["data"] = getData().toJson();


    return object;

}

int
SerialEvent::getEventCode()
{
	return eventCode;
}

void
SerialEvent::setEventCode(int  eventCode)
{
	this->eventCode = eventCode;
}

SerialEventData
SerialEvent::getData()
{
	return data;
}

void
SerialEvent::setData(SerialEventData  data)
{
	this->data = data;
}



