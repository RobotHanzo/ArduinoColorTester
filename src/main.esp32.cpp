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
#include "shared/Communication.hpp"
#include "shared/Debug.hpp"
#include "esp32/WebSockets.hpp"

ESP32Configuration configuration;
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");
String ser = "";
//unsigned long ledStopAt = 0;



void setup() {
    pinMode(2, OUTPUT);
    Serial.begin(9600);
    WiFi.mode(WIFI_AP_STA);
    WiFi.softAP(configuration.ssid, configuration.password, 6, 0, 8);
    AsyncElegantOTA.begin(&server);
    MDNS.addService("http", "tcp", 80);
    SPIFFS.begin();

    ws.onEvent(onWebSocketEvent);
    server.addHandler(&ws);

    server.addHandler(new SPIFFSEditor(SPIFFS, "admin", "adminadmin")); // /edit

    server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");
    server.serveStatic("/favicon.ico", SPIFFS, "/favicon.ico").setDefaultFile("favicon.ico");
    server.serveStatic("/icons/", SPIFFS, "/");
    server.serveStatic("/assets/", SPIFFS, "/");
    server.on("/read_buffer", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(200, "text/plain", ser);
    });
    server.on("/read_photo_resistor", HTTP_GET, [](AsyncWebServerRequest *request) {
        EventCodes eventCode = ReadPhotoResistor;
        sendEvent(eventCode);
        request->send(200, "text/plain", "Reading photo resistor");
    });
    server.onNotFound([](AsyncWebServerRequest *request) {
        request->redirect("/#/notFound");
    });
    server.begin();
    EventCodes booted = Booted;
    sendEvent(booted);
}

void loop() {
    ws.cleanupClients();
    if (Serial.available()) {
        String message = Serial.readStringUntil('\n');
        for (AsyncWebSocketClient *client: ws.getClients()) {
            client->text(message);
        }


        bourne::json object = bourne::json::parse(message.c_str());
        if (object.has_key("eventCode")) {
            int64_t eventCode = object["eventCode"].to_int();
            bourne::json data = object.has_key("data") ? object["data"] : bourne::json();
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
                    data = data.has_key("data") ? data["data"] : bourne::json();
                    switch ((short) data["code"].to_int()) {
                        case ReadPhotoResistor:
                            ws.textAll(String((short) data["value"].to_int()));
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
