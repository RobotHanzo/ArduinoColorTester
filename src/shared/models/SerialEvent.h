
/*
 * SerialEvent.h
 *
 * Used for debugging to directly send serial messages to the arduino
 */

#ifndef OPENAPI_GENERATED_SerialEvent_H_
#define OPENAPI_GENERATED_SerialEvent_H_


#include <ArduinoJson.h>
#include <ArduinoJson.h>
#include "Helpers.h"
#include "Serializable.h"
#include "SerialEventData.h"



/*! \brief Used for debugging to directly send serial messages to the arduino
 *
 *  \ingroup Models
 *
 */

class SerialEvent : public Serializable<SerialEvent> {
public:

    /*! \brief Constructor.
	 */
    SerialEvent();
    SerialEvent(String jsonString);


    /*! \brief Destructor.
	 */
    virtual ~SerialEvent();


    /*! \brief Retrieve a ArduinJson representation of this class.
	 */
    DynamicJsonDocument toJson() override;


    /*! \brief Fills in members of this class from ArduinoJson object representing it.
	 */
    SerialEvent fromJson(DynamicJsonDocument object) override;


    /*! \brief Fills in members of this class from a Json string representing it.
	 */
    SerialEvent fromJson(String jsonObj) override;

	/*! \brief Get 
	 */
	int getEventCode();

	/*! \brief Set 
	 */
	void setEventCode(int  eventCode);
	/*! \brief Get 
	 */
	SerialEventData getData();

	/*! \brief Set 
	 */
	void setData(SerialEventData  data);


    private:
    int eventCode{};
    SerialEventData data;
};

#endif /* TINY_CPP_CLIENT_SerialEvent_H_ */
