#include "Helpers.h"
#include <Arduino.h>
#include <ArduinoJson.h>

bool isprimitive(String type) {
    if (type == "String" || type == "int" || type == "float" || type == "long" || type == "double" || type == "bool" ||
        type == "std::map" || type == "std::list") {
        return true;
    }
    return false;
}


void jsonToValue(void *target, JsonVariant value, String type) {
    if (target == NULL || value.isNull() || type == "") {
        return;
    } else if (type.equals("bool")) {
        bool *val = static_cast<bool *> (target);
        *val = value.as<bool>();
    } else if (type.equals("int")) {
        int *val = static_cast<int *> (target);
        *val = value.as<int>();
    } else if (type.equals("float")) {
        float *val = static_cast<float *> (target);
        *val = (float) (value.as<float>());
    } else if (type.equals("long")) {
        long *val = static_cast<long *> (target);
        *val = (long) (value.as<long>());
    } else if (type.equals("double")) {
        double *val = static_cast<double *> (target);
        *val = value.as<double>();
    } else if (type.equals("String") == 0) {
        String *val = static_cast<String *> (target);
        *val = value.as<String>();
    } else {
        return;
    }
}