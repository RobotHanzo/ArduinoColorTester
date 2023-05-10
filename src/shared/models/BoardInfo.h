
/*
 * BoardInfo.h
 *
 * 
 */

#ifndef OPENAPI_GENERATED_BoardInfo_H_
#define OPENAPI_GENERATED_BoardInfo_H_


#include <ArduinoJson.h>
#include <ArduinoJson.h>
#include "Helpers.h"
#include "Serializable.h"



/*! \brief 
 *
 *  \ingroup Models
 *
 */

class BoardInfo : public Serializable<BoardInfo> {
public:

    /*! \brief Constructor.
	 */
    BoardInfo();
    BoardInfo(String jsonString);


    /*! \brief Destructor.
	 */
    virtual ~BoardInfo();


    /*! \brief Retrieve a ArduinJson representation of this class.
	 */
    DynamicJsonDocument toJson() override;


    /*! \brief Fills in members of this class from ArduinoJson object representing it.
	 */
    BoardInfo fromJson(DynamicJsonDocument object) override;


    /*! \brief Fills in members of this class from a Json string representing it.
	 */
    BoardInfo fromJson(String jsonObj) override;

	/*! \brief Get In milliseconds
	 */
	int getUptime();

	/*! \brief Set In milliseconds
	 */
	void setUptime(int  uptime);
	/*! \brief Get In Celsius
	 */
	float getTemperature();

	/*! \brief Set In Celsius
	 */
	void setTemperature(float  temperature);


    private:
    int uptime{};
    float temperature{};
};

#endif /* TINY_CPP_CLIENT_BoardInfo_H_ */
