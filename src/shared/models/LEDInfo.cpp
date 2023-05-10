

#include "LEDInfo.h"


LEDInfo::LEDInfo() {
    r = int(0);
    g = int(0);
    b = int(0);
}

LEDInfo::LEDInfo(std::string jsonString) {
    this->fromJson(jsonString);
}

LEDInfo::~LEDInfo() {

}

void
LEDInfo::fromJson(std::string jsonObj) {
    bourne::json object = bourne::json::parse(jsonObj);

    const char *rKey = "r";

    if (object.has_key(rKey)) {
        bourne::json value = object[rKey];


        jsonToValue(&r, value, "int");


    }

    const char *gKey = "g";

    if (object.has_key(gKey)) {
        bourne::json value = object[gKey];


        jsonToValue(&g, value, "int");


    }

    const char *bKey = "b";

    if (object.has_key(bKey)) {
        bourne::json value = object[bKey];


        jsonToValue(&b, value, "int");


    }


}

bourne::json
LEDInfo::toJson() {
    bourne::json object = bourne::json::object();


    object["r"] = getR();


    object["g"] = getG();


    object["b"] = getB();


    return object;

}

int
LEDInfo::getR() {
    return r;
}

void
LEDInfo::setR(int r) {
    this->r = r;
}

int
LEDInfo::getG() {
    return g;
}

void
LEDInfo::setG(int g) {
    this->g = g;
}

int
LEDInfo::getB() {
    return b;
}

void
LEDInfo::setB(int b) {
    this->b = b;
}



