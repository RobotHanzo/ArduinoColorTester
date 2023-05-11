
/*
 * ScheduledTask.h
 *
 * A task that has not yet ended
 */

#ifndef OPENAPI_GENERATED_ScheduledTask_H_
#define OPENAPI_GENERATED_ScheduledTask_H_


#include <ArduinoJson.h>
#include <ArduinoJson.h>
#include "Helpers.h"
#include "Serializable.h"



/*! \brief A task that has not yet ended
 *
 *  \ingroup Models
 *
 */

class ScheduledTask : public Serializable<ScheduledTask> {
public:

    /*! \brief Constructor.
	 */
    ScheduledTask();
    ScheduledTask(String jsonString);


    /*! \brief Destructor.
	 */
    virtual ~ScheduledTask();


    /*! \brief Retrieve a ArduinJson representation of this class.
	 */
    DynamicJsonDocument toJson() override;


    /*! \brief Fills in members of this class from ArduinoJson object representing it.
	 */
    ScheduledTask fromJson(DynamicJsonDocument object) override;


    /*! \brief Fills in members of this class from a Json string representing it.
	 */
    ScheduledTask fromJson(String jsonObj) override;

	/*! \brief Get 
	 */
	int getTaskId();

	/*! \brief Set 
	 */
	void setTaskId(int  taskId);
	/*! \brief Get 0 - Queued 1 - Running 2 - Finalizing (The device can be moved safely)
	 */
	int getStatusCode();

	/*! \brief Set 0 - Queued 1 - Running 2 - Finalizing (The device can be moved safely)
	 */
	void setStatusCode(int  statusCode);
	/*! \brief Get 
	 */
	JsonObject getDetails();

	/*! \brief Set 
	 */
	void setDetails(JsonObject details);
	/*! \brief Get In milliseconds This will be -1 if the task has already began.
	 */
	long getEstimatedBeginIn();

	/*! \brief Set In milliseconds This will be -1 if the task has already began.
	 */
	void setEstimatedBeginIn(long  estimatedBeginIn);
	/*! \brief Get In milliseconds. This will be -1 if the task hasn't started yet
	 */
	long getElapsed();

	/*! \brief Set In milliseconds. This will be -1 if the task hasn't started yet
	 */
	void setElapsed(long  elapsed);
	/*! \brief Get In milliseconds
	 */
	long getEstimatedCompletionIn();

	/*! \brief Set In milliseconds
	 */
	void setEstimatedCompletionIn(long  estimatedCompletionIn);


    private:
    int taskId{};
    int statusCode{};
    JsonObject details;
    long estimatedBeginIn{};
    long elapsed{};
    long estimatedCompletionIn{};
};

#endif /* TINY_CPP_CLIENT_ScheduledTask_H_ */
