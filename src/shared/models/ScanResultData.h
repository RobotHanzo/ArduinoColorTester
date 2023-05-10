
/*
 * ScanResultData.h
 *
 * The respective values represent the signals received from analog reading photoresistor under shining of the indicated color LED, varying from 0 to 1023
 */

#ifndef TINY_CPP_CLIENT_ScanResultData_H_
#define TINY_CPP_CLIENT_ScanResultData_H_


#include <string>
#include "bourne/json.hpp"
#include "Helpers.h"


/*! \brief The respective values represent the signals received from analog reading photoresistor under shining of the indicated color LED, varying from 0 to 1023
 *
 *  \ingroup models
 *
 */

class ScanResultData {
public:

    /*! \brief Constructor.
     */
    ScanResultData();

    ScanResultData(std::string jsonString);


    /*! \brief Destructor.
     */
    virtual ~ScanResultData();


    /*! \brief Retrieve a bourne JSON representation of this class.
     */
    bourne::json toJson();


    /*! \brief Fills in members of this class from bourne JSON object representing it.
     */
    void fromJson(std::string jsonObj);

    /*! \brief Get Red
     */
    int getR();

    /*! \brief Set Red
     */
    void setR(int r);

    /*! \brief Get Green
     */
    int getG();

    /*! \brief Set Green
     */
    void setG(int g);

    /*! \brief Get Blue
     */
    int getB();

    /*! \brief Set Blue
     */
    void setB(int b);


private:
    int r{};
    int g{};
    int b{};
};

#endif /* TINY_CPP_CLIENT_ScanResultData_H_ */
