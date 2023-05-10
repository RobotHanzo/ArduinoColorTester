

#include "ScheduledTask.h"


ScheduledTask::ScheduledTask() {
    taskId = int(0);
    statusCode = int(0);
    details = bourne::json();
    estimatedBeginIn = long(0);
    elapsed = long(0);
    estimatedCompletionIn = long(0);
}

ScheduledTask::ScheduledTask(std::string jsonString) {
    this->fromJson(jsonString);
}

ScheduledTask::~ScheduledTask() {

}

void
ScheduledTask::fromJson(std::string jsonObj) {
    bourne::json object = bourne::json::parse(jsonObj);

    const char *taskIdKey = "taskId";

    if (object.has_key(taskIdKey)) {
        bourne::json value = object[taskIdKey];


        jsonToValue(&taskId, value, "int");


    }

    const char *statusCodeKey = "statusCode";

    if (object.has_key(statusCodeKey)) {
        bourne::json value = object[statusCodeKey];


        jsonToValue(&statusCode, value, "int");


    }

    const char *detailsKey = "details";

    if (object.has_key(detailsKey)) {
        details = bourne::json(object[detailsKey]);
    }

    const char *estimatedBeginInKey = "estimatedBeginIn";

    if (object.has_key(estimatedBeginInKey)) {
        bourne::json value = object[estimatedBeginInKey];


        jsonToValue(&estimatedBeginIn, value, "long");


    }

    const char *elapsedKey = "elapsed";

    if (object.has_key(elapsedKey)) {
        bourne::json value = object[elapsedKey];


        jsonToValue(&elapsed, value, "long");


    }

    const char *estimatedCompletionInKey = "estimatedCompletionIn";

    if (object.has_key(estimatedCompletionInKey)) {
        bourne::json value = object[estimatedCompletionInKey];


        jsonToValue(&estimatedCompletionIn, value, "long");


    }


}

bourne::json
ScheduledTask::toJson() {
    bourne::json object = bourne::json::object();


    object["taskId"] = getTaskId();


    object["statusCode"] = getStatusCode();


    object["details"] = getDetails();


    object["estimatedBeginIn"] = getEstimatedBeginIn();


    object["elapsed"] = getElapsed();


    object["estimatedCompletionIn"] = getEstimatedCompletionIn();


    return object;

}

int
ScheduledTask::getTaskId() {
    return taskId;
}

void
ScheduledTask::setTaskId(int taskId) {
    this->taskId = taskId;
}

int
ScheduledTask::getStatusCode() {
    return statusCode;
}

void
ScheduledTask::setStatusCode(int statusCode) {
    this->statusCode = statusCode;
}

bourne::json
ScheduledTask::getDetails() {
    return details;
}

void
ScheduledTask::setDetails(bourne::json details) {
    this->details = details;
}

long
ScheduledTask::getEstimatedBeginIn() {
    return estimatedBeginIn;
}

void
ScheduledTask::setEstimatedBeginIn(long estimatedBeginIn) {
    this->estimatedBeginIn = estimatedBeginIn;
}

long
ScheduledTask::getElapsed() {
    return elapsed;
}

void
ScheduledTask::setElapsed(long elapsed) {
    this->elapsed = elapsed;
}

long
ScheduledTask::getEstimatedCompletionIn() {
    return estimatedCompletionIn;
}

void
ScheduledTask::setEstimatedCompletionIn(long estimatedCompletionIn) {
    this->estimatedCompletionIn = estimatedCompletionIn;
}



