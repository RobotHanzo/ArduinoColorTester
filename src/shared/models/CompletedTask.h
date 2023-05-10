
/*
 * CompletedTask.h
 *
 * A task that has ended
 */

#ifndef TINY_CPP_CLIENT_CompletedTask_H_
#define TINY_CPP_CLIENT_CompletedTask_H_


#include <string>
#include "bourne/json.hpp"
#include "Helpers.h"


/*! \brief A task that has ended
 *
 *  \ingroup models
 *
 */

class CompletedTask {
public:

    /*! \brief Constructor.
     */
    CompletedTask();

    CompletedTask(std::string jsonString);


    /*! \brief Destructor.
     */
    virtual ~CompletedTask();


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

    /*! \brief Get
     */
    bourne::json getDetails();

    /*! \brief Set
     */
    void setDetails(bourne::json details);

    /*! \brief Get
     */
    bourne::json getResult();

    /*! \brief Set
     */
    void setResult(bourne::json result);


private:
    int taskId{};
    bourne::json details;
    bourne::json result;
};

#endif /* TINY_CPP_CLIENT_CompletedTask_H_ */
