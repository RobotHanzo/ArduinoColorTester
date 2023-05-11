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
#define WS_MAX_QUEUED_MESSAGES 256

ESP32Configuration configuration;
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

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
            switch (eventCode) {
                case Booted:
                    sendAck(Booted);
                    break;
                case ScanFinished:
                    sendAck(ScanFinished);
                    break;
                case Acknowledged:
                    //blink LED
                    break;
                case Reply:
                    data = data.containsKey("data") ? data["data"] : JsonObject();
                    switch (data["code"].as<short>()) {
                        case ReadPhotoResistor: {
                            DynamicJsonDocument websocketReply(200);
                            websocketReply["eventCode"] = enum_to_int(REPLY_DEBUG_READ_PHOTO_RESISTOR);
                            websocketReply["data"]["value"] = data["value"];
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
                default:
                    sendEvent(InvalidEvent, (new InvalidEventReply(message))->toJson());
                    break;
            }
        }
    }
}
