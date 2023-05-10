

#include "ScanResultBrief.h"


ScanResultBrief::ScanResultBrief() {
    median = int(0);
    average = float(0);
}

ScanResultBrief::ScanResultBrief(std::string jsonString) {
    this->fromJson(jsonString);
}

ScanResultBrief::~ScanResultBrief() {

}

void
ScanResultBrief::fromJson(std::string jsonObj) {
    bourne::json object = bourne::json::parse(jsonObj);

    const char *medianKey = "median";

    if (object.has_key(medianKey)) {
        bourne::json value = object[medianKey];


        jsonToValue(&median, value, "int");


    }

    const char *averageKey = "average";

    if (object.has_key(averageKey)) {
        bourne::json value = object[averageKey];


        jsonToValue(&average, value, "double");


    }


}

bourne::json
ScanResultBrief::toJson() {
    bourne::json object = bourne::json::object();


    object["median"] = getMedian();


    object["average"] = getAverage();


    return object;

}

int
ScanResultBrief::getMedian() {
    return median;
}

void
ScanResultBrief::setMedian(int median) {
    this->median = median;
}

double
ScanResultBrief::getAverage() {
    return average;
}

void
ScanResultBrief::setAverage(double average) {
    this->average = average;
}



