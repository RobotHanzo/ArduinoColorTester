//
// Created by natha on 5/11/2023.
//

#ifndef ARDUINOCOLORTESTER_WEBSOCKET_HPP
#define ARDUINOCOLORTESTER_WEBSOCKET_HPP

#include "ESPAsyncWebServer.h"
#include "shared/models/LEDInfo.h"
#include "ScanQueue.hpp"

enum WebSocketEventCodes {
    ACK = 0,
    INVALID_MESSAGE = 1,
    INVALID_EVENT_CODE = 2,
    INVALID_DATA = 3,
    HELLO = 10,
    SCHEDULE_SCAN = 100,
    QUERY_SCAN_PROGRESS = 101,
    READ_SCAN_RESULT = 102,
    DEBUG_SET_LED_BRIGHTNESS = 200,
    DEBUG_READ_PHOTO_RESISTOR = 201,
    DEBUG_ARDUINO_INCOMING_MESSAGE = 202,
    DEBUG_READ_BOARD_INFO = 203,
    REPLY_QUERY_SCAN_PROGRESS = 1101,
    REPLY_READ_SCAN_RESULT = 1102,
    REPLY_DEBUG_READ_BOARD_INFO = 1203,
    REPLY_DEBUG_READ_PHOTO_RESISTOR = 1201,
};

int enum_to_int(WebSocketEventCodes eventCode) {
    return static_cast<int>(eventCode);
}

void sendWebSocketEvent(AsyncWebSocketClient *client, WebSocketEventCodes eventCode) {
    DynamicJsonDocument document(200);
    document["eventCode"] = enum_to_int(eventCode);
    String json;
    serializeJson(document, json);
    client->text(json);
}

void sendWebSocketEvent(AsyncWebSocketClient *client, WebSocketEventCodes eventCode, JsonDocument &data) {
    DynamicJsonDocument document(200);
    document["eventCode"] = enum_to_int(eventCode);
    document["data"] = data;
    String json;
    serializeJson(document, json);
    client->text(json);
}

void sendWebSocketAck(AsyncWebSocketClient *client, WebSocketEventCodes eventCode) {
    DynamicJsonDocument document(200);
    document["eventCode"] = enum_to_int(WebSocketEventCodes::ACK);
    document["data"]["code"] = enum_to_int(eventCode);
    String json;
    serializeJson(document, json);
    client->text(json);
}

void
onWebSocketEvent(AsyncWebSocket *webSocket, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data,
                 size_t len) {
    switch (type) {
        case WS_EVT_CONNECT: {
            sendWebSocketEvent(client, WebSocketEventCodes::HELLO);
            break;
        }
        case WS_EVT_DATA: {
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
            DynamicJsonDocument object(200);
            deserializeJson(object, msg);
            if (object.containsKey("eventCode")) {
                switch (WebSocketEventCodes(object["eventCode"].as<int>())) {
                    case ACK:
                        break;
                    case SCHEDULE_SCAN: {
                        if (!object.containsKey("data")) {
                            DynamicJsonDocument document(200);
                            document["data"] = msg;
                            sendWebSocketEvent(client, WebSocketEventCodes::INVALID_DATA, document);
                            break;
                        }
                        ScanQueue queue = ScanQueue();
                        queue.fromJson(object["data"].as<JsonObject>());
                        addQueue(queue);
                        sendWebSocketAck(client, WebSocketEventCodes::SCHEDULE_SCAN);
                        break;
                    }
                    case QUERY_SCAN_PROGRESS: {
                        if (!object.containsKey("data")) {
                            DynamicJsonDocument document(200);
                            document["data"] = msg;
                            sendWebSocketEvent(client, WebSocketEventCodes::INVALID_DATA, document);
                            break;
                        }
                        DynamicJsonDocument document(200);
                        document["scheduled"] = queued(object["data"]["name"].as<String>());
                        document["running"] = document["scheduled"] &&
                                              getFirstQueue()->getName().equals(object["data"]["name"].as<String>());
                        if (document["running"]) {
                            document["progress"] = getFirstQueue()->getProgress();
                        } else {
                            document["progress"] = 0;
                        }
                        document["queueRunning"] = hasQueues();
                        if (document["queueRunning"]) {
                            document["runningQueue"] = getFirstQueue()->getName();
                        }
                        sendWebSocketEvent(client, WebSocketEventCodes::REPLY_QUERY_SCAN_PROGRESS, document);
                        break;
                    }
                    case READ_SCAN_RESULT: {
                        if (!object.containsKey("data")) {
                            DynamicJsonDocument document(200);
                            document["data"] = msg;
                            sendWebSocketEvent(client, WebSocketEventCodes::INVALID_DATA, document);
                            break;
                        }
                        DynamicJsonDocument document(200);
                        std::vector<ScanResult> result = getResult(object["data"]["name"].as<String>());
                        document["success"] = !result.empty();
                        if (document["success"]) {
                            document["data"] = result[0].toJson();
                        }
                        sendWebSocketEvent(client, WebSocketEventCodes::REPLY_READ_SCAN_RESULT, document);
                    }

                    case DEBUG_SET_LED_BRIGHTNESS: {
                        if (!object.containsKey("data")) {
                            DynamicJsonDocument document(200);
                            document["data"] = msg;
                            sendWebSocketEvent(client, WebSocketEventCodes::INVALID_DATA, document);
                            break;
                        }
                        LEDInfo ledInfo = LEDInfo().fromJson(object["data"].as<JsonObject>());
                        sendEvent(SendLEDBrightness, ledInfo.toJson());
                        sendWebSocketAck(client, WebSocketEventCodes::DEBUG_SET_LED_BRIGHTNESS);
                        break;
                    }
                    case DEBUG_READ_PHOTO_RESISTOR: {
                        sendEvent(ReadPhotoResistor);
                        sendWebSocketAck(client, WebSocketEventCodes::DEBUG_READ_PHOTO_RESISTOR);
                        break;
                    }
                    case DEBUG_READ_BOARD_INFO: {
                        sendEvent(ReadBoardInfo);
                        sendWebSocketAck(client, WebSocketEventCodes::DEBUG_READ_BOARD_INFO);
                        break;
                    }
                    default:
                        DynamicJsonDocument document(200);
                        document["data"] = msg;
                        sendWebSocketEvent(client, WebSocketEventCodes::INVALID_EVENT_CODE, document);
                        break;
                }
            } else {
                DynamicJsonDocument document(200);
                document["data"] = msg;
                sendWebSocketEvent(client, WebSocketEventCodes::INVALID_MESSAGE, document);
            }
            break;
        }
    }
}

#endif //ARDUINOCOLORTESTER_WEBSOCKET_HPP
