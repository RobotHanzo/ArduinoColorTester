
/*
 * DebugInfo.h
 *
 * Basic information about the current status of ESP32, Arduino UNO and the sensors
 */

#ifndef OPENAPI_GENERATED_DebugInfo_H_
#define OPENAPI_GENERATED_DebugInfo_H_


#include <ArduinoJson.h>
#include <ArduinoJson.h>
#include "Helpers.h"
#include "Serializable.h"
#include "BoardInfo.h"
#include "LEDInfo.h"



/*! \brief Basic information about the current status of ESP32, Arduino UNO and the sensors
 *
 *  \ingroup Models
 *
 */

class DebugInfo : public Serializable<DebugInfo> {
public:

    /*! \brief Constructor.
	 */
    DebugInfo();
    DebugInfo(String jsonString);


    /*! \brief Destructor.
	 */
    virtual ~DebugInfo();


    /*! \brief Retrieve a ArduinJson representation of this class.
	 */
    DynamicJsonDocument toJson() override;


    /*! \brief Fills in members of this class from ArduinoJson object representing it.
	 */
    DebugInfo fromJson(DynamicJsonDocument object) override;


    /*! \brief Fills in members of this class from a Json string representing it.
	 */
    DebugInfo fromJson(String jsonObj) override;

	/*! \brief Get 
	 */
	LEDInfo getBrightness();

	/*! \brief Set 
	 */
	void setBrightness(LEDInfo  brightness);
	/*! \brief Get 
	 */
	int getPhotoresistorReading();

	/*! \brief Set 
	 */
	void setPhotoresistorReading(int  photoresistorReading);
	/*! \brief Get 
	 */
	BoardInfo getEsp32();

	/*! \brief Set 
	 */
	void setEsp32(BoardInfo  esp32);
	/*! \brief Get 
	 */
	BoardInfo getArduino();

	/*! \brief Set 
	 */
	void setArduino(BoardInfo  arduino);


    private:
    LEDInfo brightness;
    int photoresistorReading{};
    BoardInfo esp32;
    BoardInfo arduino;
};

#endif /* TINY_CPP_CLIENT_DebugInfo_H_ */
