//
// Created by natha on 5/30/2023.
//

#ifndef ARDUINOCOLORTESTER_SCANQUEUE_HPP
#define ARDUINOCOLORTESTER_SCANQUEUE_HPP


#include "../shared/models/ScanProfile.h"
#include "shared/models/ScanResult.h"
#include <map>

class ScanQueue {
public:
    ScanQueue fromJson(JsonObject object) {
        name = object["name"].as<String>();
        profiles = object["profiles"].as<JsonArray>();
        return *this;
    }

private:
    String name;
public:
    const String &getName() const {
        return name;
    }

    void addScanResult(const ScanResult &scanResult) {
        scanResults.push_back(scanResult);
    }

    const JsonArray &getProfiles() const {
        return profiles;
    }

    const std::vector<ScanResult> &getScanResults() const {
        return scanResults;
    }

    double getProgress() {
        //TODO: return detailed progress by asking arduino
        return (double)scanResults.size() / (double)profiles.size();
    }

private:
    JsonArray profiles;
    std::vector<ScanResult> scanResults;
};

std::vector<ScanQueue> *queues = new std::vector<ScanQueue>();
std::map<String, std::vector<ScanResult>> *results = new std::map<String, std::vector<ScanResult>>(); //key is name

ScanQueue *getFirstQueue() {
    return &queues->front();
}

bool queued(const String& name) {
    for (const ScanQueue& queue : *queues) {
        if (queue.getName() == name) {
            return true;
        }
    }
    return false;
}

void addQueue(const ScanQueue& queue) {
    queues->push_back(queue);
}

bool hasQueues() {
    return !queues->empty();
}

std::vector<ScanResult> getResult(String name) {
    if (results->find(name) == results->end()) {
        return {};
    }
    return (*results)[name];
}

void finishFirstQueue() {
    ScanQueue queue = queues->front();
    (*results)[queue.getName()] = queue.getScanResults();
    queues->erase(queues->begin());
}


#endif //ARDUINOCOLORTESTER_SCANQUEUE_HPP
