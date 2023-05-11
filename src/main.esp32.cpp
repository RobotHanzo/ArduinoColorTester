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
#include <ArduinoJson.h>
#include "shared/Communication.hpp"
#include "shared/Debug.hpp"

ESP32Configuration configuration;
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");
String ser = "";
//unsigned long ledStopAt = 0;

void setup() {
    pinMode(2, OUTPUT);
    Serial.begin(9600);
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
    server.on("/light_on", HTTP_GET, [](AsyncWebServerRequest *request) {
        EventCodes eventCode = SendLEDBrightness;
        LEDBrightness brightness = LEDBrightness{255, 255, 255};
        sendEvent(eventCode, brightness);
        request->send(200, "text/plain", "Shining lights");
    });
    server.on("/light_off", HTTP_GET, [](AsyncWebServerRequest *request) {
        EventCodes eventCode = SendLEDBrightness;
        LEDBrightness brightness = LEDBrightness{0, 0, 0};
        sendEvent(eventCode, brightness);
        request->send(200, "text/plain", "Dimming lights");
    });
    server.on("/read_buffer", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(200, "text/plain", ser);
    });
    server.on("/read_photo_resistor", HTTP_GET, [](AsyncWebServerRequest *request) {
        EventCodes eventCode = ReadPhotoResistor;
        sendEvent(eventCode);
        request->send(200, "text/plain", "Reading photo resistor");
    });
    server.begin();
    EventCodes booted = Booted;
    sendEvent(booted);
}

void loop() {
    ws.cleanupClients();
    if (Serial.available()) {
        DynamicJsonDocument document(200);
        String message = Serial.readStringUntil('\n');
        ser += message;
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
                        case ReadPhotoResistor:
                            ws.textAll(String(data["value"].as<int>()));
                            break;
                        default:
                            break;
                    }
                case InvalidEvent://TODO
                    break;
                default:
                    sendEvent(InvalidEvent, *new InvalidEventReply(message));
                    break;
            }
        }
    }
}
