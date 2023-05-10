

#include "ScanResultData.h"


ScanResultData::ScanResultData() {
    r = int(0);
    g = int(0);
    b = int(0);
}

ScanResultData::ScanResultData(std::string jsonString) {
    this->fromJson(jsonString);
}

ScanResultData::~ScanResultData() {

}

void
ScanResultData::fromJson(std::string jsonObj) {
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
ScanResultData::toJson() {
    bourne::json object = bourne::json::object();


    object["r"] = getR();


    object["g"] = getG();


    object["b"] = getB();


    return object;

}

int
ScanResultData::getR() {
    return r;
}

void
ScanResultData::setR(int r) {
    this->r = r;
}

int
ScanResultData::getG() {
    return g;
}

void
ScanResultData::setG(int g) {
    this->g = g;
}

int
ScanResultData::getB() {
    return b;
}

void
ScanResultData::setB(int b) {
    this->b = b;
}



