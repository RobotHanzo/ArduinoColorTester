//
// Created by natha on 5/11/2023.
//

#ifndef ARDUINOCOLORTESTER_SERIALIZABLE_H
#define ARDUINOCOLORTESTER_SERIALIZABLE_H

#include "bourne/json.hpp"

class Serializable {
public:
    virtual bourne::json toJson() = 0;

    /*! \brief Fills in members of this class from bourne JSON object representing it.
         */
    virtual void fromJson(std::string jsonObj) = 0;
};
#endif //ARDUINOCOLORTESTER_SERIALIZABLE_H
