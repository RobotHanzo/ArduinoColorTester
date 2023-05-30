
/*
 * ScanResult.h
 *
 * The result of a scan
 */

#ifndef OPENAPI_GENERATED_ScanResult_H_
#define OPENAPI_GENERATED_ScanResult_H_


#include <ArduinoJson.h>
#include <ArduinoJson.h>
#include "Helpers.h"
#include "Serializable.h"
#include "ScanProfile.h"
#include "ScanResultBrief.h"
#include "ScanResultData.h"


/*! \brief The result of a scan
 *
 *  \ingroup Models
 *
 */

class ScanResult : public Serializable<ScanResult> {
public:

    /*! \brief Constructor.
	 */
    ScanResult();
    ScanResult(String jsonString);


    /*! \brief Destructor.
	 */
    virtual ~ScanResult();


    /*! \brief Retrieve a ArduinJson representation of this class.
	 */
    DynamicJsonDocument toJson() override;


    /*! \brief Fills in members of this class from ArduinoJson object representing it.
	 */
    ScanResult fromJson(DynamicJsonDocument object) override;


    /*! \brief Fills in members of this class from a Json string representing it.
	 */
    ScanResult fromJson(String jsonObj) override;

	/*! \brief Get 
	 */
	ScanProfile getProfile();

	/*! \brief Set 
	 */
	void setProfile(ScanProfile  profile);
	/*! \brief Get The respective values represent the signals received from analog reading photoresistor under shining of the indicated color LED, varying from 0 to 1023
	 */
	std::list<ScanResultData> getResults();

	/*! \brief Set The respective values represent the signals received from analog reading photoresistor under shining of the indicated color LED, varying from 0 to 1023
	 */
	void setResults(std::list<ScanResultData> results);
	/*! \brief Get 
	 */
	ScanResultBrief getBrief();

	/*! \brief Set 
	 */
	void setBrief(ScanResultBrief  brief);


    private:
    ScanProfile profile;
    std::list<ScanResultData> results;
    ScanResultBrief brief;
};

#endif /* TINY_CPP_CLIENT_ScanResult_H_ */
