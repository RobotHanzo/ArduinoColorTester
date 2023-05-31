#include <list>
#include "ScanResult.h"


ScanResult::ScanResult() {
    profile = ScanProfile();
    results = std::vector<ScanResultData>();
    brief = *new ScanResultBrief();
}

ScanResult::ScanResult(String jsonString) {
    this->fromJson(jsonString);
}

ScanResult::~ScanResult() {

}

ScanResult ScanResult::fromJson(DynamicJsonDocument object) {
    const char *profileKey = "profile";

    if (object.containsKey(profileKey)) {
        profile.fromJson(object[profileKey].as<JsonObject>());
    }
    const char *resultsKey = "results";

    if (object.containsKey(resultsKey)) {
        JsonVariant value = object[resultsKey];

        std::vector<ScanResultData> results_list;
        ScanResultData element;
        for (JsonVariant var: value.as<JsonArray>()) {
            String serialized;
            serializeJson(var, serialized);
            element.fromJson(serialized);
            results_list.push_back(element);
        }
        results = results_list;

    }
    const char *briefKey = "brief";

    if (object.containsKey(briefKey)) {
        brief.fromJson(object[briefKey].as<JsonObject>());
    }
    return *this;
}

ScanResult ScanResult::fromJson(String jsonObj) {
    DynamicJsonDocument object(200);
    deserializeJson(object, jsonObj);
    fromJson(object);
    return *this;
}

DynamicJsonDocument ScanResult::toJson() {
    DynamicJsonDocument object(200);


    object["profile"] = getProfile().toJson();


    std::vector<ScanResultData> results_list = getResults();
    JsonArray results_arr = JsonArray();

    for (ScanResultData &var: results_list) {
        results_arr.add(var.toJson());
    }
    object["results"] = results_arr;


    object["brief"] = getBrief().toJson();


    return object;

}

ScanProfile ScanResult::getProfile() {
    return profile;
}

void ScanResult::setProfile(ScanProfile profile) {
    this->profile = profile;
}

std::vector<ScanResultData> ScanResult::getResults() {
    return results;
}

void ScanResult::setResults(std::vector<ScanResultData> results) {
    this->results = results;
}

ScanResultBrief ScanResult::getBrief() {
    return brief;
}

void ScanResult::setBrief(ScanResultBrief brief) {
    this->brief = brief;
}



