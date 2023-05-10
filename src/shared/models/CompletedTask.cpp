

#include "CompletedTask.h"


CompletedTask::CompletedTask() {
    taskId = int(0);
    details = bourne::json();
    result = bourne::json();
}

CompletedTask::CompletedTask(std::string jsonString) {
    this->fromJson(jsonString);
}

CompletedTask::~CompletedTask() {

}

void
CompletedTask::fromJson(std::string jsonObj) {
    bourne::json object = bourne::json::parse(jsonObj);

    const char *taskIdKey = "taskId";

    if (object.has_key(taskIdKey)) {
        bourne::json value = object[taskIdKey];


        jsonToValue(&taskId, value, "int");


    }

    const char *detailsKey = "details";

    if (object.has_key(detailsKey)) {
        details = bourne::json(object[detailsKey]);
    }

    const char *resultKey = "result";

    if (object.has_key(resultKey)) {
        result = bourne::json(object[resultKey]);
    }


}

bourne::json
CompletedTask::toJson() {
    bourne::json object = bourne::json::object();
    object["taskId"] = getTaskId();
    object["details"] = getDetails();
    object["result"] = getResult();
    return object;
}

int
CompletedTask::getTaskId() {
    return taskId;
}

void
CompletedTask::setTaskId(int taskId) {
    this->taskId = taskId;
}

bourne::json
CompletedTask::getDetails() {
    return details;
}

void
CompletedTask::setDetails(bourne::json details) {
    this->details = details;
}

bourne::json
CompletedTask::getResult() {
    return result;
}

void
CompletedTask::setResult(bourne::json result) {
    this->result = result;
}



