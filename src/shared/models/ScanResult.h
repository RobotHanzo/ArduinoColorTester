
/*
 * ScanResult.h
 *
 * The result of a scan
 */

#ifndef TINY_CPP_CLIENT_ScanResult_H_
#define TINY_CPP_CLIENT_ScanResult_H_


#include <string>
#include "bourne/json.hpp"
#include "Helpers.h"

#include "ScanProfile.h"
#include "ScanResultBrief.h"
#include <list>


/*! \brief The result of a scan
 *
 *  \ingroup models
 *
 */

class ScanResult {
public:

    /*! \brief Constructor.
     */
    ScanResult();

    ScanResult(std::string jsonString);


    /*! \brief Destructor.
     */
    virtual ~ScanResult();


    /*! \brief Retrieve a bourne JSON representation of this class.
     */
    bourne::json toJson();


    /*! \brief Fills in members of this class from bourne JSON object representing it.
     */
    void fromJson(std::string jsonObj);

    /*! \brief Get
     */
    ScanProfile getProfile();

    /*! \brief Set
     */
    void setProfile(ScanProfile profile);

    /*! \brief Get The respective values represent the signals received from analog reading photoresistor under shining of the indicated color LED, varying from 0 to 1023
     */
    std::list<bourne::json> getResults();

    /*! \brief Set The respective values represent the signals received from analog reading photoresistor under shining of the indicated color LED, varying from 0 to 1023
     */
    void setResults(std::list<bourne::json> results);

    /*! \brief Get
     */
    ScanResultBrief getBrief();

    /*! \brief Set
     */
    void setBrief(ScanResultBrief brief);


private:
    ScanProfile profile;
    std::list<bourne::json> results;
    ScanResultBrief brief;
};

#endif /* TINY_CPP_CLIENT_ScanResult_H_ */
