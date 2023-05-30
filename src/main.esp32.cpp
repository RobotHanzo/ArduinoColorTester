//
// Created by natha on 5/8/2023.
//
#include <Arduino.h>
#include <WiFi.h>
#include <SPIFFS.h>
#include "esp32/ESP32Configuration.hpp"
#include "ESPAsyncWebServer.h"
#include "SPIFFSEditor.h"
#include "AsyncElegantOTA.h"
#include <ArduinoJson.h>
#include "shared/Communication.hpp"
#include "shared/Debug.hpp"
#include "esp32/WebSocket.hpp"
#include "shared/models/BoardInfo.h"

#define WS_MAX_QUEUED_MESSAGES 256

ESP32Configuration configuration;
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");
bool isScanning = false;

void setup() {
    pinMode(2, OUTPUT);
    Serial.begin(9600);
    WiFi.mode(WIFI_AP);
    WiFi.softAP(configuration.ssid, configuration.password, 6, 0, 8);
    AsyncElegantOTA.begin(&server);
    SPIFFS.begin();


    ws.onEvent(onWebSocketEvent);
    server.addHandler(&ws);
    server.addHandler(new SPIFFSEditor(SPIFFS, "admin", "adminadmin")); // /edit

    server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");
    server.serveStatic("/favicon.ico", SPIFFS, "/favicon.ico").setDefaultFile("favicon.ico");
    server.serveStatic("/icons/", SPIFFS, "/");
    server.serveStatic("/assets/", SPIFFS, "/");
    server.on("/read_photo_resistor", HTTP_GET, [](AsyncWebServerRequest *request) {
        sendEvent(ReadPhotoResistor);
        request->send(200, "text/plain", "Reading photo resistor");
    });
    server.begin();
    sendEvent(Booted);
}

void loop() {
    ws.cleanupClients();
    if (Serial.available()) {
        DynamicJsonDocument document(200);
        String message = Serial.readStringUntil('\n');
        deserializeJson(document, message);
        if (document.containsKey("eventCode")) {
            int eventCode = document["eventCode"];
            JsonObject data = document.containsKey("data") ? document["data"] : JsonObject();

            DynamicJsonDocument websocketReply(200);
            websocketReply["eventCode"] = enum_to_int(DEBUG_ARDUINO_INCOMING_MESSAGE);
            websocketReply["data"] = document;
            String json;
            serializeJson(websocketReply, json);
            ws.textAll(json);
            switch (eventCode) {
                case Booted:
                    sendAck(Booted);
                    break;
                case ScanFinished: {
                    if (isScanning) {
                        ScanResult result = ScanResult();
                        result.fromJson(data);
                        getFirstQueue()->addScanResult(result);
                        isScanning = false;
                    }
                    break;
                }
                case Acknowledged:
                    //blink LED
                    break;
                case Reply:
                    switch (document["code"].as<short>()) {
                        case ReadPhotoResistor: {
                            DynamicJsonDocument websocketReply(200);
                            websocketReply["eventCode"] = enum_to_int(REPLY_DEBUG_READ_PHOTO_RESISTOR);
                            websocketReply["data"]["value"] = data["value"];
                            String json;
                            serializeJson(websocketReply, json);
                            ws.textAll(json);
                            break;
                        }
                        case ReadBoardInfo: {
                            DynamicJsonDocument websocketReply(200);
                            websocketReply["eventCode"] = enum_to_int(REPLY_DEBUG_READ_BOARD_INFO);
                            websocketReply["data"]["arduino"] = data;
                            BoardInfo esp32Info;
                            esp32Info.setTemperature(temperatureRead());
                            esp32Info.setUptime(millis());
                            websocketReply["data"]["esp32"] = esp32Info.toJson();
                            String json;
                            serializeJson(websocketReply, json);
                            ws.textAll(json);
                            break;
                        }
                        default:
                            break;
                    }
                case InvalidEvent://TODO
                    break;
                default: {
                    InvalidEventReply reply(message);
                    sendEvent(InvalidEvent, reply.toJson());
                    break;
                }
            }
        }
    }
    if (hasQueues() && !isScanning) {
        isScanning = true;
        ScanQueue *queue = getFirstQueue();
        if (queue->getProfiles().size() > 0) {
            DynamicJsonDocument document(200);
            document = queue->getProfiles()[0];
            queue->getProfiles().remove(0);
            sendEvent(StartScan, document);
        } else {
            finishFirstQueue();
            isScanning = false;
        }
    }
}
