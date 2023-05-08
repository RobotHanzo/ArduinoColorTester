//
// Created by natha on 5/8/2023.
//
#include <Arduino.h>
#include <WiFi.h>
#include <ESPmDNS.h>
#include <SPIFFS.h>
#include "esp32/ESP32Configuration.hpp"
#include "ESPAsyncWebServer.h"
#include "SPIFFSEditor.h"
#include "AsyncElegantOTA.h"
ESP32Configuration configuration;
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

void setup() {
    Serial.begin(115200);
    
    WiFi.mode(WIFI_AP);
    WiFi.softAP(configuration.ssid, configuration.password, 6, 0, 8);
    AsyncElegantOTA.begin(&server);
    MDNS.addService("http", "tcp", 80);
    SPIFFS.begin();

//    ws.onEvent(onWsEvent);
    server.addHandler(&ws);

//    events.onConnect([](AsyncEventSourceClient *client) {
//        client->send("hello!", NULL, millis(), 1000);
//    });
//    server.addHandler(&events);

    server.addHandler(new SPIFFSEditor(SPIFFS, "admin", "adminadmin")); // /edit

    server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");
    server.serveStatic("/favicon.ico", SPIFFS, "/favicon.ico").setDefaultFile("favicon.ico");
    server.serveStatic("/icons/", SPIFFS, "/");
    server.serveStatic("/assets/", SPIFFS, "/");
    server.begin();
}

void loop() {
    ws.cleanupClients();
    if (Serial.available()) {
        DynamicJsonDocument document(200);
        deserializeJson(document, Serial.readStringUntil('\n'));
        if (document.containsKey("eventCode")) {
            int eventCode = document["eventCode"];
            JsonObject data = document.containsKey("data") ? document["data"] : JsonObject();
            switch (eventCode) {
                case ScanCompleted:
                default:
                    sendEvent(InvalidEvent);
                    break;
            }
        }
    }
}
