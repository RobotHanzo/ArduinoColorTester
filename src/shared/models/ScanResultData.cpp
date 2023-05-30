
#include "ScanResultData.h"


ScanResultData::ScanResultData() {
    r = new int(0);
    g = new int(0);
    b = new int(0);
}

ScanResultData::ScanResultData(String jsonString) {
    this->fromJson(jsonString);
}

ScanResultData::~ScanResultData() {
    delete r;
    delete g;
    delete b;
}

ScanResultData ScanResultData::fromJson(DynamicJsonDocument object) {
    const char *rKey = "r";

    if (object.containsKey(rKey)) {
        JsonVariant value = object[rKey];
        jsonToValue(&r, value, "int");
    }
    const char *gKey = "g";

    if (object.containsKey(gKey)) {
        JsonVariant value = object[gKey];
        jsonToValue(&g, value, "int");
    }
    const char *bKey = "b";

    if (object.containsKey(bKey)) {
        JsonVariant value = object[bKey];
        jsonToValue(&b, value, "int");
    }
    return *this;
}

ScanResultData ScanResultData::fromJson(String jsonObj) {
    DynamicJsonDocument object(200);
    deserializeJson(object, jsonObj);
    fromJson(object);
    return *this;
}

DynamicJsonDocument ScanResultData::toJson() {
    DynamicJsonDocument object(200);


    object["r"] = *getR();


    object["g"] = *getG();


    object["b"] = *getB();


    return object;

}

int*
ScanResultData::getR() {
    return r;
}

void
ScanResultData::setR(int* r) {
    this->r = r;
}

int*
ScanResultData::getG() {
    return g;
}

void
ScanResultData::setG(int* g) {
    this->g = g;
}

int*
ScanResultData::getB() {
    return b;
}

void
ScanResultData::setB(int* b) {
    this->b = b;
}

ScanResultData::ScanResultData(int *r, int *g, int *b) : r(r), g(g), b(b) {}



