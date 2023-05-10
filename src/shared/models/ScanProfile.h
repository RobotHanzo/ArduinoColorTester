
/*
 * ScanProfile.h
 *
 * A scan profile containing the settings of a scan
 */

#ifndef OPENAPI_GENERATED_ScanProfile_H_
#define OPENAPI_GENERATED_ScanProfile_H_


#include <ArduinoJson.h>
#include <ArduinoJson.h>
#include "Helpers.h"
#include "Serializable.h"



/*! \brief A scan profile containing the settings of a scan
 *
 *  \ingroup Models
 *
 */

class ScanProfile : public Serializable<ScanProfile> {
public:

    /*! \brief Constructor.
	 */
    ScanProfile();
    ScanProfile(String jsonString);


    /*! \brief Destructor.
	 */
    virtual ~ScanProfile();


    /*! \brief Retrieve a ArduinJson representation of this class.
	 */
    DynamicJsonDocument toJson() override;


    /*! \brief Fills in members of this class from ArduinoJson object representing it.
	 */
    ScanProfile fromJson(DynamicJsonDocument object) override;


    /*! \brief Fills in members of this class from a Json string representing it.
	 */
    ScanProfile fromJson(String jsonObj) override;

	/*! \brief Get 
	 */
	int getBrightness();

	/*! \brief Set 
	 */
	void setBrightness(int  brightness);
	/*! \brief Get 
	 */
	int getScanTimes();

	/*! \brief Set 
	 */
	void setScanTimes(int  scanTimes);
	/*! \brief Get 
	 */
	int getScanInterval();

	/*! \brief Set 
	 */
	void setScanInterval(int  scanInterval);


    private:
    int brightness{};
    int scanTimes{};
    int scanInterval{};
};

#endif /* TINY_CPP_CLIENT_ScanProfile_H_ */
