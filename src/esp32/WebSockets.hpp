//
// Created by natha on 5/11/2023.
//

#ifndef ARDUINOCOLORTESTER_WEBSOCKETS_HPP
#define ARDUINOCOLORTESTER_WEBSOCKETS_HPP

#include "ESPAsyncWebServer.h"
#include "shared/models/LEDInfo.h"

enum WebSocketEventCodes {
    ACK = 0, INVALID_MESSAGE = 1, INVALID_EVENT_CODE = 2, INVALID_DATA = 3,
    HELLO = 10,
    DEBUG_SET_LED_BRIGHTNESS = 200, DEBUG_READ_PHOTO_RESISTOR = 201 , DEBUG_ARDUINO_INCOMING_MESSAGE = 202

};

int enum_to_int(WebSocketEventCodes eventCode) {
    return static_cast<int>(eventCode);
}

void
onWebSocketEvent(AsyncWebSocket *webSocket, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data,
                 size_t len) {
    switch (type) {
        case WS_EVT_CONNECT:
            client->text(bourne::json({"eventCode", enum_to_int(HELLO)}).dump().c_str());
            break;
        case WS_EVT_DATA:
            AwsFrameInfo *info = (AwsFrameInfo *) arg;
            String msg = "";
            if (info->final && info->index == 0 && info->len == len) {
                //the whole message is in a single frame and we got all of it's data
                if (info->opcode == WS_TEXT) {
                    for (size_t i = 0; i < info->len; i++) {
                        msg += (char) data[i];
                    }
                } else {
                    char buff[3];
                    for (size_t i = 0; i < info->len; i++) {
                        sprintf(buff, "%02x ", (uint8_t) data[i]);
                        msg += buff;
                    }
                }
                Serial.printf("%s\n", msg.c_str());
            } else {
                //message is comprised of multiple frames or the frame is split into multiple packets
                if (info->opcode == WS_TEXT) {
                    for (size_t i = 0; i < len; i++) {
                        msg += (char) data[i];
                    }
                } else {
                    char buff[3];
                    for (size_t i = 0; i < len; i++) {
                        sprintf(buff, "%02x ", (uint8_t) data[i]);
                        msg += buff;
                    }
                }
            }
            client->text(msg);
            bourne::json object = bourne::json::parse(msg.c_str());
            if (object.has_key("eventCode")) {
                client->text("a");
                switch (WebSocketEventCodes(object["eventCode"].to_int())) {
                    case ACK:
                        break;
                    case DEBUG_SET_LED_BRIGHTNESS: {
                        client->text("b");
                        if (!object.has_key("data")) {
                            client->text(bourne::json(
                                    {"eventCode", enum_to_int(INVALID_DATA), "data", msg.c_str()}).dump().c_str());
                            break;
                        }
                        client->text("c");
                        LEDInfo ledInfo = LEDInfo(object["data"].dump());
                        sendEvent(SendLEDBrightness, ledInfo);
                        client->text("d");
                        break;
                    }
                    default:
                        client->text(bourne::json(
                                {"eventCode", enum_to_int(INVALID_EVENT_CODE), "data", msg.c_str()}).dump().c_str());
                        break;
                }
            } else {
                client->text(
                        bourne::json({"eventCode", enum_to_int(INVALID_MESSAGE), "data", msg.c_str()}).dump().c_str());
            }
            break;
    }
}

#endif //ARDUINOCOLORTESTER_WEBSOCKETS_HPP
