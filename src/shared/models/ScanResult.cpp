

#include "ScanResult.h"
#include "ScanResultBrief.h"


ScanResult::ScanResult() {
    profile = ScanProfile();
    results = std::list<bourne::json>();
    brief = ScanResultBrief();
}

ScanResult::ScanResult(std::string jsonString) {
    this->fromJson(jsonString);
}

ScanResult::~ScanResult() {

}

void ScanResult::fromJson(std::string jsonObj) {
    bourne::json object = bourne::json::parse(jsonObj);

    const char *profileKey = "profile";

    if (object.has_key(profileKey)) {
        bourne::json value = object[profileKey];


        ScanProfile *obj = &profile;
        obj->fromJson(value.dump());

    }

    const char *resultsKey = "results";

    if (object.has_key(resultsKey)) {
        bourne::json value = object[resultsKey];


        std::list<bourne::json> results_list;
        bourne::json element;
        for (auto &var: value.array_range()) {


            element = bourne::json(var); //TODO test if this works

            results_list.push_back(element);
        }
        results = results_list;


    }

    const char *briefKey = "brief";

    if (object.has_key(briefKey)) {
        bourne::json value = object[briefKey];


        ScanResultBrief *obj = &brief;
        obj->fromJson(value.dump());

    }


}

bourne::json ScanResult::toJson() {
    bourne::json object = bourne::json::object();


    object["profile"] = getProfile().toJson();


    std::list<bourne::json> results_list = getResults();
    bourne::json results_arr = bourne::json::array();

    for (auto &var: results_list) {
        bourne::json obj = var;
        results_arr.append(obj);
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

std::list<bourne::json> ScanResult::getResults() {
    return results;
}

void ScanResult::setResults(std::list<bourne::json> results) {
    this->results = results;
}

ScanResultBrief ScanResult::getBrief() {
    return brief;
}

void ScanResult::setBrief(ScanResultBrief brief) {
    this->brief = brief;
}



