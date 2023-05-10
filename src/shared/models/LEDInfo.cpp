
#include "LEDInfo.h"


LEDInfo::LEDInfo() {
	r = int(0);
	g = int(0);
	b = int(0);
}

LEDInfo::LEDInfo(String jsonString) {
	this->fromJson(jsonString);
}

LEDInfo::~LEDInfo() {

}

LEDInfo LEDInfo::fromJson(DynamicJsonDocument object) {
    const char *rKey = "r";

    if(object.containsKey(rKey)) {
        JsonVariant value = object[rKey];
        jsonToValue(&r, value, "int");
    }
    const char *gKey = "g";

    if(object.containsKey(gKey)) {
        JsonVariant value = object[gKey];
        jsonToValue(&g, value, "int");
    }
    const char *bKey = "b";

    if(object.containsKey(bKey)) {
        JsonVariant value = object[bKey];
        jsonToValue(&b, value, "int");
    }
    return *this;
}

LEDInfo LEDInfo::fromJson(String jsonObj) {
    DynamicJsonDocument object(200);
    deserializeJson(object, jsonObj);
    fromJson(object);
    return *this;
}

DynamicJsonDocument LEDInfo::toJson() {
    DynamicJsonDocument object(200);



    object["r"] = getR();





    object["g"] = getG();





    object["b"] = getB();



    return object;

}

int
LEDInfo::getR()
{
	return r;
}

void
LEDInfo::setR(int  r)
{
	this->r = r;
}

int
LEDInfo::getG()
{
	return g;
}

void
LEDInfo::setG(int  g)
{
	this->g = g;
}

int
LEDInfo::getB()
{
	return b;
}

void
LEDInfo::setB(int  b)
{
	this->b = b;
}



