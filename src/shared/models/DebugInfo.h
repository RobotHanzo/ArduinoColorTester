
/*
 * DebugInfo.h
 *
 * Basic information about the current status of ESP32, Arduino UNO and the sensors
 */

#ifndef TINY_CPP_CLIENT_DebugInfo_H_
#define TINY_CPP_CLIENT_DebugInfo_H_


#include <string>
#include "bourne/json.hpp"
#include "Helpers.h"
#include "BoardInfo.h"
#include "LEDInfo.h"


/*! \brief Basic information about the current status of ESP32, Arduino UNO and the sensors
 *
 *  \ingroup models
 *
 */

class DebugInfo {
public:

    /*! \brief Constructor.
     */
    DebugInfo();

    DebugInfo(std::string jsonString);


    /*! \brief Destructor.
     */
    virtual ~DebugInfo();


    /*! \brief Retrieve a bourne JSON representation of this class.
     */
    bourne::json toJson();


    /*! \brief Fills in members of this class from bourne JSON object representing it.
     */
    void fromJson(std::string jsonObj);

    /*! \brief Get
     */
    LEDInfo getBrightness();

    /*! \brief Set
     */
    void setBrightness(LEDInfo brightness);

    /*! \brief Get
     */
    int getPhotoresistorReading();

    /*! \brief Set
     */
    void setPhotoresistorReading(int photoresistorReading);

    /*! \brief Get
     */
    BoardInfo getEsp32();

    /*! \brief Set
     */
    void setEsp32(BoardInfo esp32);

    /*! \brief Get
     */
    BoardInfo getArduino();

    /*! \brief Set
     */
    void setArduino(BoardInfo arduino);


private:
    LEDInfo brightness;
    int photoresistorReading{};
    BoardInfo esp32;
    BoardInfo arduino;
};

#endif /* TINY_CPP_CLIENT_DebugInfo_H_ */
