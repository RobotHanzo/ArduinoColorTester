//
// Created by natha on 5/30/2023.
//

#ifndef ARDUINOCOLORTESTER_SCANQUEUE_HPP
#define ARDUINOCOLORTESTER_SCANQUEUE_HPP


#include "../shared/models/ScanProfile.h"
#include "shared/models/ScanResult.h"
#include <map>
std::vector<ScanResultData> resultCache = std::vector<ScanResultData>();

class ScanQueue {
public:
    ScanQueue fromJson(JsonObject object) {
        name = object["name"].as<String>();
        profiles = std::vector<ScanProfile>();
        JsonArray array = object["profiles"].as<JsonArray>();
        for (JsonVariant p : array) {
            ScanProfile profile;
            profiles.push_back(profile.fromJson(p.as<JsonObject>()));
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
        scanResult.setResults(resultCache);
        scanResult.setBrief(scanResult.getBrief().fromResults(resultCache));
        scanResults.push_back(scanResult);
    }

    std::vector<ScanProfile> &getProfiles() {
        return profiles;
    }

    const std::vector<ScanResult> &getScanResults() const {
        return scanResults;
    }

    double getProgress() {
        //TODO: return detailed progress by asking arduino
        return (double)scanResults.size() / (double)profiles.size();
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

ScanQueue* getFirstQueue() {
    return &queues.front();
}

bool queued(const String& name) {
    for (const ScanQueue& queue : queues) {
        if (queue.getName() == name) {
            return true;
        }
    }
    return false;
}

void addQueue(ScanQueue& queue) {
    queues.push_back(queue);
    if (queues.size() == 1) {
        sendEvent(StartScan, queue.getProfiles().front().toJson());
        queue.removeFirstProfile();
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
        sendEvent(StartScan, queue.getProfiles().front().toJson());
    }
}

void cacheResult(ScanResultData result) {
    resultCache.push_back(result);
}


#endif //ARDUINOCOLORTESTER_SCANQUEUE_HPP
