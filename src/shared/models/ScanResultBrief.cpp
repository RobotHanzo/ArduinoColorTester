
#include <vector>
#include "ScanResultBrief.h"


int static median(std::vector<int> values) {
    std::sort(values.begin(), values.end());
    if (values.size() % 2 == 0) {
        return (values[values.size() / 2 - 1] + values[values.size() / 2]) / 2;
    } else {
        return values[values.size() / 2];
    }
}

double static average(std::vector<int> values) {
    int sum = 0;
    for (int value: values) {
        sum += value;
    }
    return double(sum) / values.size();
}

ScanResultBrief::ScanResultBrief() {
    medianR = int(0);
    medianG = int(0);
    medianB = int(0);
    averageR = float(0);
    averageG = float(0);
    averageB = float(0);
}

ScanResultBrief::ScanResultBrief(String jsonString) {
    this->fromJson(jsonString);
}

ScanResultBrief::~ScanResultBrief() = default;

ScanResultBrief ScanResultBrief::fromJson(DynamicJsonDocument object) {
    const char *medianRKey = "medianR";
    if (object.containsKey(medianRKey)) {
        JsonVariant value = object[medianRKey];
        jsonToValue(&medianR, value, "int");
    }

    const char *medianGKey = "medianG";
    if (object.containsKey(medianGKey)) {
        JsonVariant value = object[medianGKey];
        jsonToValue(&medianG, value, "int");
    }

    const char *medianBKey = "medianB";
    if (object.containsKey(medianBKey)) {
        JsonVariant value = object[medianBKey];
        jsonToValue(&medianB, value, "int");
    }

    const char *averageRKey = "averageR";
    if (object.containsKey(averageRKey)) {
        JsonVariant value = object[averageRKey];
        jsonToValue(&averageR, value, "double");
    }

    const char *averageGKey = "averageG";
    if (object.containsKey(averageGKey)) {
        JsonVariant value = object[averageGKey];
        jsonToValue(&averageG, value, "double");
    }

    const char *averageBKey = "averageB";
    if (object.containsKey(averageBKey)) {
        JsonVariant value = object[averageBKey];
        jsonToValue(&averageB, value, "double");
    }
    return *this;
}

ScanResultBrief ScanResultBrief::fromJson(String jsonObj) {
    DynamicJsonDocument object(200);
    deserializeJson(object, jsonObj);
    fromJson(object);
    return *this;
}

DynamicJsonDocument ScanResultBrief::toJson() {
    DynamicJsonDocument object(200);
    object["medianR"] = getMedianR();
    object["medianG"] = getMedianG();
    object["medianB"] = getMedianB();
    object["averageR"] = getAverageR();
    object["averageG"] = getAverageG();
    object["averageB"] = getAverageB();
    return object;

}

ScanResultBrief ScanResultBrief::fromResults(std::vector<ScanResultData> results) {
    std::vector<int> rValues;
    std::vector<int> gValues;
    std::vector<int> bValues;
    for (auto &result: results) {
        rValues.push_back(result.getR());
        gValues.push_back(result.getG());
        bValues.push_back(result.getB());
    }
    medianR = median(rValues);
    medianG = median(gValues);
    medianB = median(bValues);
    averageR = average(rValues);
    averageG = average(gValues);
    averageB = average(bValues);
    return *this;
}

int ScanResultBrief::getMedianR() const {
    return medianR;
}

int ScanResultBrief::getMedianG() const {
    return medianG;
}

int ScanResultBrief::getMedianB() const {
    return medianB;
}

double ScanResultBrief::getAverageR() const {
    return averageR;
}

double ScanResultBrief::getAverageG() const {
    return averageG;
}

double ScanResultBrief::getAverageB() const {
    return averageB;
}



