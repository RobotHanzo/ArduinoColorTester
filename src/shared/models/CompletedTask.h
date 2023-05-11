
/*
 * CompletedTask.h
 *
 * A task that has ended
 */

#ifndef OPENAPI_GENERATED_CompletedTask_H_
#define OPENAPI_GENERATED_CompletedTask_H_


#include <ArduinoJson.h>
#include <ArduinoJson.h>
#include "Helpers.h"
#include "Serializable.h"



/*! \brief A task that has ended
 *
 *  \ingroup Models
 *
 */

class CompletedTask : public Serializable<CompletedTask> {
public:

    /*! \brief Constructor.
	 */
    CompletedTask();
    CompletedTask(String jsonString);


    /*! \brief Destructor.
	 */
    virtual ~CompletedTask();


    /*! \brief Retrieve a ArduinJson representation of this class.
	 */
    DynamicJsonDocument toJson() override;


    /*! \brief Fills in members of this class from ArduinoJson object representing it.
	 */
    CompletedTask fromJson(DynamicJsonDocument object) override;


    /*! \brief Fills in members of this class from a Json string representing it.
	 */
    CompletedTask fromJson(String jsonObj) override;

	/*! \brief Get 
	 */
	int getTaskId();

	/*! \brief Set 
	 */
	void setTaskId(int  taskId);
	/*! \brief Get 
	 */
	JsonObject getDetails();

	/*! \brief Set 
	 */
	void setDetails(JsonObject details);
	/*! \brief Get 
	 */
	JsonObject getResult();

	/*! \brief Set 
	 */
	void setResult(JsonObject result);


    private:
    int taskId{};
    JsonObject details;
    JsonObject result;
};

#endif /* TINY_CPP_CLIENT_CompletedTask_H_ */
