
/*
 * ScanResultBrief.h
 *
 * 
 */

#ifndef TINY_CPP_CLIENT_ScanResultBrief_H_
#define TINY_CPP_CLIENT_ScanResultBrief_H_


#include <string>
#include "bourne/json.hpp"
#include "Helpers.h"


/*! \brief
 *
 *  \ingroup models
 *
 */

class ScanResultBrief {
public:

    /*! \brief Constructor.
     */
    ScanResultBrief();

    ScanResultBrief(std::string jsonString);


    /*! \brief Destructor.
     */
    virtual ~ScanResultBrief();


    /*! \brief Retrieve a bourne JSON representation of this class.
     */
    bourne::json toJson();


    /*! \brief Fills in members of this class from bourne JSON object representing it.
     */
    void fromJson(std::string jsonObj);

    /*! \brief Get
     */
    int getMedian();

    /*! \brief Set
     */
    void setMedian(int median);

    /*! \brief Get
     */
    double getAverage();

    /*! \brief Set
     */
    void setAverage(double average);


private:
    int median{};
    double average{};
};

#endif /* TINY_CPP_CLIENT_ScanResultBrief_H_ */
