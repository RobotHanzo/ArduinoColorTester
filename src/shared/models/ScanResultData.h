
/*
 * ScanResultData.h
 *
 * The respective values represent the signals received from analog reading photoresistor under shining of the indicated color LED, varying from 0 to 1023
 */

#ifndef OPENAPI_GENERATED_ScanResultData_H_
#define OPENAPI_GENERATED_ScanResultData_H_


#include <ArduinoJson.h>
#include <ArduinoJson.h>
#include "Helpers.h"
#include "Serializable.h"



/*! \brief The respective values represent the signals received from analog reading photoresistor under shining of the indicated color LED, varying from 0 to 1023
 *
 *  \ingroup Models
 *
 */

class ScanResultData : public Serializable<ScanResultData> {
public:

    /*! \brief Constructor.
	 */
    ScanResultData();
    ScanResultData(String jsonString);


    /*! \brief Destructor.
	 */
    virtual ~ScanResultData();


    /*! \brief Retrieve a ArduinJson representation of this class.
	 */
    DynamicJsonDocument toJson() override;


    /*! \brief Fills in members of this class from ArduinoJson object representing it.
	 */
    ScanResultData fromJson(DynamicJsonDocument object) override;


    /*! \brief Fills in members of this class from a Json string representing it.
	 */
    ScanResultData fromJson(String jsonObj) override;

	/*! \brief Get Red
	 */
	int getR();

	/*! \brief Set Red
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

#endif /* TINY_CPP_CLIENT_ScanResultData_H_ */
