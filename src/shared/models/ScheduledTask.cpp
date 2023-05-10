
#include "ScheduledTask.h"


ScheduledTask::ScheduledTask() {
	taskId = int(0);
	statusCode = int(0);
	details = null;
	estimatedBeginIn = long(0);
	elapsed = long(0);
	estimatedCompletionIn = long(0);
}

ScheduledTask::ScheduledTask(String jsonString) {
	this->fromJson(jsonString);
}

ScheduledTask::~ScheduledTask() {

}

ScheduledTask ScheduledTask::fromJson(DynamicJsonDocument object) {
    const char *taskIdKey = "taskId";

    if(object.containsKey(taskIdKey)) {
        JsonVariant value = object[taskIdKey];
        jsonToValue(&taskId, value, "int");
    }
    const char *statusCodeKey = "statusCode";

    if(object.containsKey(statusCodeKey)) {
        JsonVariant value = object[statusCodeKey];
        jsonToValue(&statusCode, value, "int");
    }
    const char *detailsKey = "details";

    if(object.containsKey(detailsKey)) {
        JsonVariant value = object[detailsKey];
        Serializable* obj = &details;
        String serializedValue;
        serializeJson(value, serializedValue);
		obj->fromJson(value.dump());
    }
    const char *estimatedBeginInKey = "estimatedBeginIn";

    if(object.containsKey(estimatedBeginInKey)) {
        JsonVariant value = object[estimatedBeginInKey];
        jsonToValue(&estimatedBeginIn, value, "long");
    }
    const char *elapsedKey = "elapsed";

    if(object.containsKey(elapsedKey)) {
        JsonVariant value = object[elapsedKey];
        jsonToValue(&elapsed, value, "long");
    }
    const char *estimatedCompletionInKey = "estimatedCompletionIn";

    if(object.containsKey(estimatedCompletionInKey)) {
        JsonVariant value = object[estimatedCompletionInKey];
        jsonToValue(&estimatedCompletionIn, value, "long");
    }
    return *this;
}

ScheduledTask ScheduledTask::fromJson(String jsonObj) {
    DynamicJsonDocument object(200);
    deserializeJson(object, jsonObj);
    fromJson(object);
    return *this;
}

DynamicJsonDocument ScheduledTask::toJson() {
    DynamicJsonDocument object(200);



    object["taskId"] = getTaskId();





    object["statusCode"] = getStatusCode();






	object["details"] = getDetails().toJson();




    object["estimatedBeginIn"] = getEstimatedBeginIn();





    object["elapsed"] = getElapsed();





    object["estimatedCompletionIn"] = getEstimatedCompletionIn();



    return object;

}

int
ScheduledTask::getTaskId()
{
	return taskId;
}

void
ScheduledTask::setTaskId(int  taskId)
{
	this->taskId = taskId;
}

int
ScheduledTask::getStatusCode()
{
	return statusCode;
}

void
ScheduledTask::setStatusCode(int  statusCode)
{
	this->statusCode = statusCode;
}

Serializable
ScheduledTask::getDetails()
{
	return details;
}

void
ScheduledTask::setDetails(Serializable  details)
{
	this->details = details;
}

long
ScheduledTask::getEstimatedBeginIn()
{
	return estimatedBeginIn;
}

void
ScheduledTask::setEstimatedBeginIn(long  estimatedBeginIn)
{
	this->estimatedBeginIn = estimatedBeginIn;
}

long
ScheduledTask::getElapsed()
{
	return elapsed;
}

void
ScheduledTask::setElapsed(long  elapsed)
{
	this->elapsed = elapsed;
}

long
ScheduledTask::getEstimatedCompletionIn()
{
	return estimatedCompletionIn;
}

void
ScheduledTask::setEstimatedCompletionIn(long  estimatedCompletionIn)
{
	this->estimatedCompletionIn = estimatedCompletionIn;
}



