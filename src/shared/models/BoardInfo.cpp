
#include "BoardInfo.h"


BoardInfo::BoardInfo() {
	uptime = int(0);
	temperature = float(0);
}

BoardInfo::BoardInfo(String jsonString) {
	this->fromJson(jsonString);
}

BoardInfo::~BoardInfo() {

}

BoardInfo BoardInfo::fromJson(DynamicJsonDocument object) {
    const char *uptimeKey = "uptime";

    if(object.containsKey(uptimeKey)) {
        JsonVariant value = object[uptimeKey];
        jsonToValue(&uptime, value, "int");
    }
    const char *temperatureKey = "temperature";

    if(object.containsKey(temperatureKey)) {
        JsonVariant value = object[temperatureKey];
        jsonToValue(&temperature, value, "float");
    }
    return *this;
}

BoardInfo BoardInfo::fromJson(String jsonObj) {
    DynamicJsonDocument object(200);
    deserializeJson(object, jsonObj);
    fromJson(object);
    return *this;
}

DynamicJsonDocument BoardInfo::toJson() {
    DynamicJsonDocument object(200);



    object["uptime"] = getUptime();





    object["temperature"] = getTemperature();



    return object;

}

int
BoardInfo::getUptime()
{
	return uptime;
}

void
BoardInfo::setUptime(int  uptime)
{
	this->uptime = uptime;
}

float
BoardInfo::getTemperature()
{
	return temperature;
}

void
BoardInfo::setTemperature(float  temperature)
{
	this->temperature = temperature;
}



