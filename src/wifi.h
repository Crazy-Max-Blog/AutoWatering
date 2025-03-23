#pragma once

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "db.h"

namespace wifi {  // Переименовано в wifi
    void startAP();
    void connectSTA();
    
    void begin() {
        WiFi.mode(WIFI_AP_STA);
        db::begin();  // Инициализация базы данных

        startAP();
        connectSTA();
    }

    void startAP() {
        WiFi.softAP("AP ESP");
        Serial.print("AP IP: ");
        Serial.println(WiFi.softAPIP());
    }

    void connectSTA() {
        if (db::db[kk::wifi_ssid].length()) {
            WiFi.begin(db::db[kk::wifi_ssid], db::db[kk::wifi_pass]);
            Serial.print("Connect STA");
            int tries = 20;
            while (WiFi.status() != WL_CONNECTED) {
                delay(500);
                Serial.print('.');
                if (!--tries) break;
            }
            Serial.println();
            Serial.print("IP: ");
            Serial.println(WiFi.localIP());
        }
    }
}