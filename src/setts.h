#pragma once

#include "db.h"
#include <SettingsGyverWS.h>

//#include <WiFiUdp.h>
//#include <NTPClient.h>
#include <GyverNTP.h>

namespace setts
{
    SettingsGyverWS sett("Автополив", &db::db);

    void build(sets::Builder &b);

    void begin()
    {
        sett.begin();
        sett.onBuild(build);

        //WiFiUDP ntpUDP;
        //NTPClient timeClient(ntpUDP, "pool.ntp.org");
        //timeClient.begin();
        //timeClient.update();

        // Serial.print("Time: ");
        // Serial.println(timeClient.getEpochTime());
        //setStampZone(4);
        //sett.rtc.sync(timeClient.getEpochTime());
        //GyverNTP ntp;
        //ntp.begin();
        NTP.begin(4);
        while(!NTP.tick());
        sett.rtc.sync(NTP);
        Serial.print("Time: ");
        Serial.println(sett.rtc.daySeconds());
        // Serial.println(sett.rtc.daySeconds());
    }

    void tick()
    {
        sett.tick();

        static long timer = 0;
        long mil = millis();
        if (mil - timer >= 1000)
        {
            // Serial.println(sett.rtc.timeToString());
            // Serial.println(int(sett.rtc.daySeconds() - (uint32_t)db::db[kk::timerr]));
            timer = mil;
            sett.updater()
                .update(H(hum_1), String((float)random(80, 100) / 10, 1) + "%")
                .update(H(hum_2), String((float)random(800, 1000) / 100, 2) + "%")
                .update(H(water), (String)random(100) + "%");

            /*db::db[kk::hum_1] = String((float)random(80, 100) / 10, 1) + "%";
            db::db[kk::hum_2] = String((float)random(800, 1000) / 100, 2) + "%";
            db::db[kk::water] = (String)random(100) + "%";*/
        }
    }

    void build(sets::Builder &b)
    {
        {
            sets::Row r(b, "Первая группа", sets::DivType::Block);
            b.Label(H(hum_1), "Влажность");
            if (b.Button("Полить"))
                Serial.println("Water1");
        }

        {
            sets::Row r(b, "Вторая группа", sets::DivType::Block);
            b.Label(H(hum_2), "Влажность");
            if (b.Button("Полить"))
                Serial.println("Water2");
        }

        b.Label(H(water), "Уровень воды в бочке");

        {
            sets::Menu m(b, "Автоматизации");

            {
                sets::Row r(b, "Рабочее время", sets::DivType::Line);

                b.Time(kk::time_1, "С");
                b.Time(kk::time_2, "До");
            }

            {
                sets::Group r(b, "Первая группа");
                b.Slider2(kk::hum_min, kk::hum_max, "Влажность полива", 0, 100, 1, "%");
                b.Slider("Время полива", 0, 10, 1, "сек.");
            }

            {
                sets::Group r(b, "Вторая группа");
                b.Slider("Влажность полива", 0, 100, 1, "%");
                b.Slider("Время полива", 0, 10, 1, "сек.");
            }
        }

        {
            sets::Menu m(b, "Настройки");
            {
                sets::Group g(b, "WiFi");
                b.Input(kk::wifi_ssid, "SSID");
                b.Pass(kk::wifi_pass, "Password");
            }

            {
                sets::Group g(b, "MQTT");
                b.Switch(kk::mqtt_en, "MQTT");
                if (db::db[kk::mqtt_en])
                {
                    // b.reload(true);
                    b.Input(kk::mqtt_host, "Host");
                    b.Input(kk::mqtt_port, "Port");
                    b.Input(kk::mqtt_user, "User");
                    b.Pass(kk::mqtt_pass, "Pass");
                }
            }

            {
                sets::Group g(b, "Telegram Bot");
                b.Switch(kk::tg_en, "Telegram Bot");
                if (db::db[kk::tg_en])
                {
                    b.Input(kk::tg_id, "Chat ID");
                    b.Pass(kk::tg_token, "Token");
                }
            }

            {
                sets::Buttons btns(b);
                if (b.Button("Save"))
                    db::db.update();
                if (b.Button("Restart"))
                    ESP.restart();
            }
        }
    }
}