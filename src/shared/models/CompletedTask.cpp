
#include "CompletedTask.h"


CompletedTask::CompletedTask() {
	taskId = int(0);
	details = JsonObject();
	result = JsonObject();
}

CompletedTask::CompletedTask(String jsonString) {
	this->fromJson(jsonString);
}

CompletedTask::~CompletedTask() {

}

CompletedTask CompletedTask::fromJson(DynamicJsonDocument object) {
    const char *taskIdKey = "taskId";

    if(object.containsKey(taskIdKey)) {
        JsonVariant value = object[taskIdKey];
        jsonToValue(&taskId, value, "int");
    }
    const char *detailsKey = "details";

    if(object.containsKey(detailsKey)) {
        details = object[detailsKey];
    }
    const char *resultKey = "result";

    if(object.containsKey(resultKey)) {
        result = object[resultKey];
    }
    return *this;
}

CompletedTask CompletedTask::fromJson(String jsonObj) {
    DynamicJsonDocument object(200);
    deserializeJson(object, jsonObj);
    fromJson(object);
    return *this;
}

DynamicJsonDocument CompletedTask::toJson() {
    DynamicJsonDocument object(200);



    object["taskId"] = getTaskId();






	object["details"] = getDetails();





	object["result"] = getResult();


    return object;

}

int
CompletedTask::getTaskId()
{
	return taskId;
}

void
CompletedTask::setTaskId(int  taskId)
{
	this->taskId = taskId;
}

JsonObject CompletedTask::getDetails()
{
	return details;
}

void
CompletedTask::setDetails(JsonObject details)
{
	this->details = details;
}

JsonObject
CompletedTask::getResult()
{
	return result;
}

void
CompletedTask::setResult(JsonObject result)
{
	this->result = result;
}



