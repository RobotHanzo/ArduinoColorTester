
#include "CompletedTask.h"


CompletedTask::CompletedTask() {
	taskId = int(0);
	details = null;
	result = null;
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
        JsonVariant value = object[detailsKey];
        Serializable* obj = &details;
        String serializedValue;
        serializeJson(value, serializedValue);
		obj->fromJson(value.dump());
    }
    const char *resultKey = "result";

    if(object.containsKey(resultKey)) {
        JsonVariant value = object[resultKey];
        Serializable* obj = &result;
        String serializedValue;
        serializeJson(value, serializedValue);
		obj->fromJson(value.dump());
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






	object["details"] = getDetails().toJson();





	object["result"] = getResult().toJson();


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

Serializable
CompletedTask::getDetails()
{
	return details;
}

void
CompletedTask::setDetails(Serializable  details)
{
	this->details = details;
}

Serializable
CompletedTask::getResult()
{
	return result;
}

void
CompletedTask::setResult(Serializable  result)
{
	this->result = result;
}



