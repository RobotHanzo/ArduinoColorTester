
#include "ScanResult.h"


ScanResult::ScanResult() {
	profile = ScanProfile();
	results = std::list<Serializable>();
	brief = ScanResultBrief();
}

ScanResult::ScanResult(String jsonString) {
	this->fromJson(jsonString);
}

ScanResult::~ScanResult() {

}

ScanResult ScanResult::fromJson(DynamicJsonDocument object) {
    const char *profileKey = "profile";

    if(object.containsKey(profileKey)) {
        JsonVariant value = object[profileKey];
        ScanProfile* obj = &profile;
        String serializedValue;
        serializeJson(value, serializedValue);
		obj->fromJson(value.dump());
    }
    const char *resultsKey = "results";

    if(object.containsKey(resultsKey)) {
        JsonVariant value = object[resultsKey];

        std::list<Serializable> results_list;
        Serializable element;
        for(JsonVariant var : value.as<JsonArray>())
            String serialized;
            serializeJson(var, serialized);
            element.fromJson(serialized);
            results_list.push_back(element);
        }
        results = results_list;

    }
    const char *briefKey = "brief";

    if(object.containsKey(briefKey)) {
        JsonVariant value = object[briefKey];
        ScanResultBrief* obj = &brief;
        String serializedValue;
        serializeJson(value, serializedValue);
		obj->fromJson(value.dump());
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


    std::list<Serializable> results_list = getResults();
    JsonArray results_arr = JsonArray();

    for(auto& var : results_list)
    {
        Serializable obj = var;
        results_arr.add(obj.toJson());
    }
    object["results"] = results_arr;







	object["brief"] = getBrief().toJson();


    return object;

}

ScanProfile
ScanResult::getProfile()
{
	return profile;
}

void
ScanResult::setProfile(ScanProfile  profile)
{
	this->profile = profile;
}

std::list<Serializable>
ScanResult::getResults()
{
	return results;
}

void
ScanResult::setResults(std::list <Serializable> results)
{
	this->results = results;
}

ScanResultBrief
ScanResult::getBrief()
{
	return brief;
}

void
ScanResult::setBrief(ScanResultBrief  brief)
{
	this->brief = brief;
}



