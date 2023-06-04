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

class ScanQueue {
public:
    ScanQueue fromJson(JsonObject object) {
        name = object["name"].as<String>();
        profiles = std::vector<ScanProfile>();
        JsonArray array = object["profiles"].as<JsonArray>();
        for (JsonVariant p: array) {
            ScanProfile profile;
            profiles.push_back(profile.fromJson(p.as<JsonObject>()));
            totalSteps += profile.getScanTimes();
        }
        return *this;
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
        completedSteps += scanResult.getProfile().getScanTimes();
    }

    std::vector<ScanProfile> &getProfiles() {
        return profiles;
    }

    std::vector<ScanResult> &getScanResults() {
        return scanResults;
    }

    double getProgress() const {
        return (double) (completedSteps + resultCache->size()) / (double) totalSteps;
    }

    void removeFirstProfile() {
        profiles.erase(profiles.begin());
    }

private:
    int totalSteps = 0;
    int completedSteps = 0;
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
    queues.erase(queues.begin());
    if (queues.size() > 0) {
        queue = queues.front();
        sendEvent(StartScan, queue.getProfiles().front().toJson());
        queue.removeFirstProfile();
        writeFirstQueue(queue);
    }
}

void cacheResult(ScanResultData result) {
    resultCache->push_back(result);
}

std::vector<String> getResultKeys() {
    std::vector<String> keys;
    for (auto it = results.begin(); it != results.end(); ++it) {
        keys.push_back(it->first);
    }
    return keys;
}

std::vector<String> getQueuedNames() {
    std::vector<String> names;
    for (auto &queue: queues) {
        names.push_back(queue.getName());
    }
    return names;
}


#endif //ARDUINOCOLORTESTER_SCANQUEUE_HPP
