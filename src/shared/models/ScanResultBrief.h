
/*
 * ScanResultBrief.h
 *
 * 
 */

#ifndef OPENAPI_GENERATED_ScanResultBrief_H_
#define OPENAPI_GENERATED_ScanResultBrief_H_


#include <ArduinoJson.h>
#include <ArduinoJson.h>
#include "Helpers.h"
#include "Serializable.h"
#include <vector>
#include "ScanResultData.h"


/*! \brief
 *
 *  \ingroup Models
 *
 */

class ScanResultBrief : public Serializable<ScanResultBrief> {
public:

    /*! \brief Constructor.
	 */
    ScanResultBrief();
    ScanResultBrief(String jsonString);


    /*! \brief Destructor.
	 */
    virtual ~ScanResultBrief();


    /*! \brief Retrieve a ArduinJson representation of this class.
	 */
    DynamicJsonDocument toJson() override;


    /*! \brief Fills in members of this class from ArduinoJson object representing it.
	 */
    ScanResultBrief fromJson(DynamicJsonDocument object) override;


    /*! \brief Fills in members of this class from a Json string representing it.
	 */
    ScanResultBrief fromJson(String jsonObj) override;

    ScanResultBrief fromResults(std::vector<ScanResultData>);


    private:
    int medianR;
    int medianG;
    int medianB;
    double averageR;
    double averageG;
    double averageB;
public:
    int getMedianR() const;

    int getMedianG() const;

    int getMedianB() const;

    double getAverageR() const;

    double getAverageG() const;

    double getAverageB() const;
};

#endif /* TINY_CPP_CLIENT_ScanResultBrief_H_ */
