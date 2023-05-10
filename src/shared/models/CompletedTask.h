
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
	Serializable getDetails();

	/*! \brief Set 
	 */
	void setDetails(Serializable  details);
	/*! \brief Get 
	 */
	Serializable getResult();

	/*! \brief Set 
	 */
	void setResult(Serializable  result);


    private:
    int taskId{};
    Serializable details;
    Serializable result;
};

#endif /* TINY_CPP_CLIENT_CompletedTask_H_ */
