
/*
 * BoardInfo.h
 *
 * 
 */

#ifndef TINY_CPP_CLIENT_BoardInfo_H_
#define TINY_CPP_CLIENT_BoardInfo_H_


#include <string>
#include "bourne/json.hpp"
#include "Helpers.h"


/*! \brief
 *
 *  \ingroup models
 *
 */

class BoardInfo {
public:

    /*! \brief Constructor.
     */
    BoardInfo();

    BoardInfo(std::string jsonString);


    /*! \brief Destructor.
     */
    virtual ~BoardInfo();


    /*! \brief Retrieve a bourne JSON representation of this class.
     */
    bourne::json toJson();


    /*! \brief Fills in members of this class from bourne JSON object representing it.
     */
    void fromJson(std::string jsonObj);

    /*! \brief Get In milliseconds
     */
    int getUptime();

    /*! \brief Set In milliseconds
     */
    void setUptime(int uptime);

    /*! \brief Get In Celsius
     */
    float getTemperature();

    /*! \brief Set In Celsius
     */
    void setTemperature(float temperature);


private:
    int uptime{};
    float temperature{};
};


#endif /* TINY_CPP_CLIENT_BoardInfo_H_ */
