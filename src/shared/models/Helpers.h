#ifndef TINY_CPP_CLIENT_HELPERS_H_
#define TINY_CPP_CLIENT_HELPERS_H_

#include <Arduino.h>
#include <ArduinoJson.h>

bool isprimitive(String type);

void jsonToValue(void* target, JsonVariant value, String type);

#endif /* TINY_CPP_CLIENT_HELPERS_H_ */
