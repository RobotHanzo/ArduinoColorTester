
#include "ScanResultBrief.h"


ScanResultBrief::ScanResultBrief() {
	median = int(0);
	average = float(0);
}

ScanResultBrief::ScanResultBrief(String jsonString) {
	this->fromJson(jsonString);
}

ScanResultBrief::~ScanResultBrief() {

}

ScanResultBrief ScanResultBrief::fromJson(DynamicJsonDocument object) {
    const char *medianKey = "median";

    if(object.containsKey(medianKey)) {
        JsonVariant value = object[medianKey];
        jsonToValue(&median, value, "int");
    }
    const char *averageKey = "average";

    if(object.containsKey(averageKey)) {
        JsonVariant value = object[averageKey];
        jsonToValue(&average, value, "double");
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



    object["median"] = getMedian();





    object["average"] = getAverage();



    return object;

}

int
ScanResultBrief::getMedian()
{
	return median;
}

void
ScanResultBrief::setMedian(int  median)
{
	this->median = median;
}

double
ScanResultBrief::getAverage()
{
	return average;
}

void
ScanResultBrief::setAverage(double  average)
{
	this->average = average;
}



