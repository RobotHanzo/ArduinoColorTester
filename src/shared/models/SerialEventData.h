
/*
 * SerialEventData.h
 *
 * 
 */

#ifndef OPENAPI_GENERATED_SerialEventData_H_
#define OPENAPI_GENERATED_SerialEventData_H_


#include <ArduinoJson.h>
#include <ArduinoJson.h>
#include "Helpers.h"
#include "Serializable.h"



/*! \brief 
 *
 *  \ingroup Models
 *
 */

class SerialEventData : public Serializable<SerialEventData> {
public:

    /*! \brief Constructor.
	 */
    SerialEventData();
    SerialEventData(String jsonString);


    /*! \brief Destructor.
	 */
    virtual ~SerialEventData();


    /*! \brief Retrieve a ArduinJson representation of this class.
	 */
    DynamicJsonDocument toJson() override;


    /*! \brief Fills in members of this class from ArduinoJson object representing it.
	 */
    SerialEventData fromJson(DynamicJsonDocument object) override;


    /*! \brief Fills in members of this class from a Json string representing it.
	 */
    SerialEventData fromJson(String jsonObj) override;

	/*! \brief Get 
	 */
	int getEventCode();

	/*! \brief Set 
	 */
	void setEventCode(int  eventCode);


    private:
    int eventCode{};
};

#endif /* TINY_CPP_CLIENT_SerialEventData_H_ */
