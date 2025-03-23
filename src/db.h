#pragma once

#include <GyverDBFile.h>
#include <LittleFS.h>

DB_KEYS(
    kk,
    wifi_ssid,
    wifi_pass,

    mqtt_en,
    mqtt_host,
    mqtt_port,
    mqtt_user,
    mqtt_pass,

    tg_en,
    tg_id,
    tg_token,

    hum_min,
    hum_max,

    time_1,
    time_2
);

namespace db {
    GyverDBFile db(&LittleFS, "/data.db");

    void begin() {
        LittleFS.begin();  // Инициализация файловой системы для ESP8266
        db.begin();
        DB_INIT(
            db,
            (kk::wifi_ssid, ""),
            (kk::wifi_pass, ""),
            
            (kk::mqtt_en, true),
            (kk::mqtt_host, ""),
            (kk::mqtt_port, ""),
            (kk::mqtt_user, ""),
            (kk::mqtt_pass, ""),
            
            (kk::tg_en, true),
            (kk::tg_id, ""),
            (kk::tg_token, ""),

            (kk::hum_min, 10),
            (kk::hum_max, 50),

            (kk::time_1, 10 * 3600),
            (kk::time_2, 21 * 3600)
        );        
    }
}