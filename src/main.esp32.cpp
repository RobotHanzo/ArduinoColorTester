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

ESP32Configuration configuration;
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");
bool ledOn = false;
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
        EventCodes eventCode = SendLED;
        LEDBrightness brightness = LEDBrightness{255, 255, 255};
        sendEvent(eventCode, brightness);
        request->send(200, "text/plain", "Shining lights");
    });
    server.on("/light_off", HTTP_GET, [](AsyncWebServerRequest *request) {
        EventCodes eventCode = SendLED;
        LEDBrightness brightness = LEDBrightness{0, 0, 0};
        sendEvent(eventCode, brightness);
        request->send(200, "text/plain", "Dimming lights");
    });
    server.on("/read_buffer", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(200, "text/plain", ser);
    });
    server.begin();
}

void loop() {
    if (ledOn) {
        digitalWrite(2, HIGH);
    } else {
        digitalWrite(2, LOW);
    }
    ws.cleanupClients();
    if (Serial.available()) {
        DynamicJsonDocument document(200);
        String buf = Serial.readStringUntil('\n');
        ser += buf;
        ledOn = !ledOn;
        deserializeJson(document, buf);
        if (document.containsKey("eventCode")) {
            int eventCode = document["eventCode"];
            JsonObject data = document.containsKey("data") ? document["data"] : JsonObject();
            switch (eventCode) {
                case ScanFinished:
                    sendAck(ScanFinished);
                    break;
                case Acknowledged:
                    //blink LED
                    break;
                default:
                    sendEvent(InvalidEvent);
                    break;
            }
        }
    }
}
