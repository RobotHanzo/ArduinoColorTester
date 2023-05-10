
/*
 * ScheduledTask.h
 *
 * A task that has not yet ended
 */

#ifndef TINY_CPP_CLIENT_ScheduledTask_H_
#define TINY_CPP_CLIENT_ScheduledTask_H_


#include <string>
#include "bourne/json.hpp"
#include "Helpers.h"


/*! \brief A task that has not yet ended
 *
 *  \ingroup models
 *
 */

class ScheduledTask {
public:

    /*! \brief Constructor.
     */
    ScheduledTask();

    ScheduledTask(std::string jsonString);


    /*! \brief Destructor.
     */
    virtual ~ScheduledTask();


    /*! \brief Retrieve a bourne JSON representation of this class.
     */
    bourne::json toJson();


    /*! \brief Fills in members of this class from bourne JSON object representing it.
     */
    void fromJson(std::string jsonObj);

    /*! \brief Get
     */
    int getTaskId();

    /*! \brief Set
     */
    void setTaskId(int taskId);

    /*! \brief Get 0 - Queued 1 - Running 2 - Finalizing (The device can be moved safely)
     */
    int getStatusCode();

    /*! \brief Set 0 - Queued 1 - Running 2 - Finalizing (The device can be moved safely)
     */
    void setStatusCode(int statusCode);

    /*! \brief Get
     */
    bourne::json getDetails();

    /*! \brief Set
     */
    void setDetails(bourne::json details);

    /*! \brief Get In milliseconds This will be -1 if the task has already began.
     */
    long getEstimatedBeginIn();

    /*! \brief Set In milliseconds This will be -1 if the task has already began.
     */
    void setEstimatedBeginIn(long estimatedBeginIn);

    /*! \brief Get In milliseconds. This will be -1 if the task hasn't started yet
     */
    long getElapsed();

    /*! \brief Set In milliseconds. This will be -1 if the task hasn't started yet
     */
    void setElapsed(long elapsed);

    /*! \brief Get In milliseconds
     */
    long getEstimatedCompletionIn();

    /*! \brief Set In milliseconds
     */
    void setEstimatedCompletionIn(long estimatedCompletionIn);


private:
    int taskId{};
    int statusCode{};
    bourne::json details;
    long estimatedBeginIn{};
    long elapsed{};
    long estimatedCompletionIn{};
};

#endif /* TINY_CPP_CLIENT_ScheduledTask_H_ */
