
/*
 * ScanProfile.h
 *
 * A scan profile containing the settings of a scan
 */

#ifndef TINY_CPP_CLIENT_ScanProfile_H_
#define TINY_CPP_CLIENT_ScanProfile_H_


#include <string>
#include "bourne/json.hpp"
#include "Helpers.h"


/*! \brief A scan profile containing the settings of a scan
 *
 *  \ingroup models
 *
 */

class ScanProfile {
public:

    /*! \brief Constructor.
     */
    ScanProfile();

    ScanProfile(std::string jsonString);


    /*! \brief Destructor.
     */
    virtual ~ScanProfile();


    /*! \brief Retrieve a bourne JSON representation of this class.
     */
    bourne::json toJson();


    /*! \brief Fills in members of this class from bourne JSON object representing it.
     */
    void fromJson(std::string jsonObj);

    /*! \brief Get
     */
    int getBrightness();

    /*! \brief Set
     */
    void setBrightness(int brightness);

    /*! \brief Get
     */
    int getScanTimes();

    /*! \brief Set
     */
    void setScanTimes(int scanTimes);

    /*! \brief Get
     */
    int getScanInterval();

    /*! \brief Set
     */
    void setScanInterval(int scanInterval);


private:
    int brightness{};
    int scanTimes{};
    int scanInterval{};
};

#endif /* TINY_CPP_CLIENT_ScanProfile_H_ */
