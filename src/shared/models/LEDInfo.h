
/*
 * LEDInfo.h
 *
 * 
 */

#ifndef OPENAPI_GENERATED_LEDInfo_H_
#define OPENAPI_GENERATED_LEDInfo_H_


#include <ArduinoJson.h>
#include <ArduinoJson.h>
#include "Helpers.h"
#include "Serializable.h"



/*! \brief 
 *
 *  \ingroup Models
 *
 */

class LEDInfo : public Serializable<LEDInfo> {
public:

    /*! \brief Constructor.
	 */
    LEDInfo();
    LEDInfo(String jsonString);


    /*! \brief Destructor.
	 */
    virtual ~LEDInfo();


    /*! \brief Retrieve a ArduinJson representation of this class.
	 */
    DynamicJsonDocument toJson() override;


    /*! \brief Fills in members of this class from ArduinoJson object representing it.
	 */
    LEDInfo fromJson(DynamicJsonDocument object) override;


    /*! \brief Fills in members of this class from a Json string representing it.
	 */
    LEDInfo fromJson(String jsonObj) override;

	/*! \brief Get Blue
	 */
	int getR();

	/*! \brief Set Blue
	 */
	void setR(int  r);
	/*! \brief Get Green
	 */
	int getG();

	/*! \brief Set Green
	 */
	void setG(int  g);
	/*! \brief Get Blue
	 */
	int getB();

	/*! \brief Set Blue
	 */
	void setB(int  b);


    private:
    int r{};
    int g{};
    int b{};
};

#endif /* TINY_CPP_CLIENT_LEDInfo_H_ */
