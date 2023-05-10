
/*
 * LEDInfo.h
 *
 * 
 */

#ifndef TINY_CPP_CLIENT_LEDInfo_H_
#define TINY_CPP_CLIENT_LEDInfo_H_


#include <string>
#include "bourne/json.hpp"
#include "Helpers.h"
#include "shared/Serializable.h"


/*! \brief
 *
 *  \ingroup models
 *
 */

class LEDInfo : public Serializable {
public:

    /*! \brief Constructor.
     */
    LEDInfo();

    explicit LEDInfo(std::string jsonString);


    /*! \brief Destructor.
     */
    virtual ~LEDInfo();


    /*! \brief Retrieve a bourne JSON representation of this class.
     */
    bourne::json toJson() override;


    /*! \brief Fills in members of this class from bourne JSON object representing it.
     */
    void fromJson(std::string jsonObj) override;

    /*! \brief Get Blue
     */
    int getR();

    /*! \brief Set Blue
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


#endif /* TINY_CPP_CLIENT_LEDInfo_H_ */
