#ifndef OPENAPI_GENERATED_SERIALIZABLE_H
#define OPENAPI_GENERATED_SERIALIZABLE_H

#include <WString.h>
#include "ArduinoJson.h"
template <typename T>
class Serializable {
public:
    /*! \brief Retrieve a ArduinoJson representation of this class.
	 */
    virtual DynamicJsonDocument toJson() = 0;
    /*! \brief Fills in members of this class from ArduinoJson object representing it.
	 */
    virtual T fromJson(DynamicJsonDocument object) = 0;
    /*! \brief Fills in members of this class from a Json string representing it.
	 */
    virtual T fromJson(String json) = 0;
};

#endif //ARDUINOCOLORTESTER_SERIALIZABLE_HPP
