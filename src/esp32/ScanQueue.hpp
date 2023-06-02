//
// Created by natha on 5/30/2023.
//

#ifndef ARDUINOCOLORTESTER_SCANQUEUE_HPP
#define ARDUINOCOLORTESTER_SCANQUEUE_HPP


#include "../shared/models/ScanProfile.h"
#include "shared/models/ScanResult.h"
#include <map>
#include <utility>

std::vector<ScanResultData> *resultCache = new std::vector<ScanResultData>;

class ScanQueue : public Serializable<ScanQueue> {
public:
    ScanQueue fromJson(JsonObject object) {
        name = object["name"].as<String>();
        profiles = std::vector<ScanProfile>();
        JsonArray array = object["profiles"].as<JsonArray>();
        for (JsonVariant p: array) {
            ScanProfile profile;
            profiles.push_back(profile.fromJson(p.as<JsonObject>()));
        }
        return *this;
    }

    ScanQueue fromJson(DynamicJsonDocument object) {
        return *this;
    }

    ScanQueue fromJson(String jsonObj) {
        DynamicJsonDocument object(200);
        deserializeJson(object, jsonObj);
        fromJson(object);
        return *this;
    }

    DynamicJsonDocument toJson() {
        DynamicJsonDocument object(500);
        object["name"] = getName();
        std::vector<ScanResult> results_list = getScanResults();
        JsonArray results_arr = JsonArray();

        for (ScanResult &var: results_list) {
            results_arr.add(var.toJson());
        }
        object["results"] = results_arr;
        std::vector<ScanProfile> profiles_list = getProfiles();
        JsonArray profiles_arr = JsonArray();

        for (ScanProfile &var: profiles_list) {
            profiles_arr.add(var.toJson());
        }
        object["profiles"] = profiles_arr;
        return object;
    }

private:
    String name;
public:
    const String &getName() const {
        return name;
    }

    void addScanResult(ScanResult &scanResult) {
        scanResult.setBrief(scanResult.getBrief().fromResults(*resultCache));
        resultCache = new std::vector<ScanResultData>;
        scanResult.setResults(*resultCache);
        scanResults.push_back(scanResult);
    }

    std::vector<ScanProfile> &getProfiles() {
        return profiles;
    }

    std::vector<ScanResult> &getScanResults() {
        return scanResults;
    }

    double getProgress() {
        //TODO: return detailed progress by asking arduino
        return (double) scanResults.size() / (double) profiles.size();
    }

    void removeFirstProfile() {
        profiles.erase(profiles.begin());
    }

private:
    std::vector<ScanProfile> profiles;
    std::vector<ScanResult> scanResults;
};

std::vector<ScanQueue> queues = std::vector<ScanQueue>();
std::map<String, std::vector<ScanResult>> results = std::map<String, std::vector<ScanResult>>(); //key is name

ScanQueue getFirstQueue() {
    return queues.front();
}

void writeFirstQueue(ScanQueue queue) {
    queues.front() = queue;
}

bool queued(const String &name) {
    for (const ScanQueue &queue: queues) {
        if (queue.getName() == name) {
            return true;
        }
    }
    return false;
}

void addQueue(ScanQueue &queue) {
    queues.push_back(queue);
    if (queues.size() == 1) {
        sendEvent(StartScan, queue.getProfiles().front().toJson());
        queue.removeFirstProfile();
        writeFirstQueue(queue);
    }
}

bool hasQueues() {
    return !queues.empty();
}

std::vector<ScanResult> getResult(String name) {
    if (results.find(name) == results.end()) {
        return {};
    }
    return results[name];
}

void finishFirstQueue() {
    ScanQueue queue = queues.front();
    results[queue.getName()] = queue.getScanResults();
    auto a = queue.getScanResults().front().toJson();
    serializeJson(a, Serial);
    queues.erase(queues.begin());
    if (queues.size() > 0) {
        sendEvent(StartScan, queue.getProfiles().front().toJson());
        queue.removeFirstProfile();
        writeFirstQueue(queue);
    }
}

void cacheResult(ScanResultData result) {
    resultCache->push_back(result);
}


#endif //ARDUINOCOLORTESTER_SCANQUEUE_HPP
