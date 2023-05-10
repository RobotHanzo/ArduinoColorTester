

#include "BoardInfo.h"


BoardInfo::BoardInfo() {
    uptime = int(0);
    temperature = float(0);
}

BoardInfo::BoardInfo(std::string jsonString) {
    this->fromJson(jsonString);
}

BoardInfo::~BoardInfo() {

}

void BoardInfo::fromJson(std::string jsonObj) {
    bourne::json object = bourne::json::parse(jsonObj);

    const char *uptimeKey = "uptime";

    if (object.has_key(uptimeKey)) {
        bourne::json value = object[uptimeKey];


        jsonToValue(&uptime, value, "int");


    }

    const char *temperatureKey = "temperature";

    if (object.has_key(temperatureKey)) {
        bourne::json value = object[temperatureKey];


        jsonToValue(&temperature, value, "float");


    }


}

bourne::json BoardInfo::toJson() {
    bourne::json object = bourne::json::object();


    object["uptime"] = getUptime();


    object["temperature"] = getTemperature();


    return object;

}

int BoardInfo::getUptime() {
    return uptime;
}

void BoardInfo::setUptime(int uptime) {
    this->uptime = uptime;
}

float BoardInfo::getTemperature() {
    return temperature;
}

void BoardInfo::setTemperature(float temperature) {
    this->temperature = temperature;
}



