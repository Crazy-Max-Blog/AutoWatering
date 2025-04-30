#pragma once

#include "db.h"
#include <SettingsGyverWS.h>

#include <GyverNTP.h>

#include "sensor/water.h"

#include "tg.h"

namespace setts
{
    SettingsGyverWS sett("Автополив", &db::db);

    void build(sets::Builder &b);

    void begin()
    {
        sett.begin();
        sett.onBuild(build);

        if (WiFi.status() == WL_CONNECTED)
        {
            NTP.begin(4);
            while (!NTP.tick());
            sett.rtc.sync(NTP);
            Serial.print("Time: ");
            Serial.println(sett.rtc.daySeconds());
        }
    }

    void sendData(int hum_1, int hum_2, byte water)
    {
        sett.updater()
            .update(H(hum_1), String((String)hum_1 + "%"))
            .update(H(hum_2), String((String)hum_2 + "%"))
            .update(H(water), String((String)water + "%"));
    }

    void waterAlarm(bool wout)
    {
        sett.updater()
            .update(H(wout), wout ? "Протечки нет" : "Протечка 💦")
            .updateColor(H(wout), wout ? sets::Colors::Green : sets::Colors::Red);
    }

    void tick()
    {
        sett.tick();

        static long timer = 0;
        long mil = millis();
        if (mil - timer >= 500)
        {
            timer = mil;
            /*sett.updater()
                .update(H(hum_1), String((float)random(80, 100) / 10, 1) + "%")
                .update(H(hum_2), String((float)random(800, 1000) / 100, 2) + "%")
                .update(H(water), (String)random(100) + "%");*/
            

            /*sendData(
            random(80, 100),
            random(20, 50),
            random(100)
            );

            waterAlarm(random(2) == 0);*/
            
            sett.updater().update(H(wlew), analogRead(33));
        }
    }

    void build(sets::Builder &b)
    {
        {
            sets::Row r(b, "Первая группа", sets::DivType::Block);
            b.Label(H(hum_1), "Влажность");
            if (b.Button("Полить")) {
                sensor::water(0);
                Serial.println("Water1");
            }
        }

        {
            sets::Row r(b, "Вторая группа", sets::DivType::Block);
            b.Label(H(hum_2), "Влажность");
            if (b.Button("Полить")) {
                sensor::water(1);
                Serial.println("Water2");
            }
        }

        b.Label(H(water), "Уровень воды в бочке");
        b.Label(H(wout), "Протечка", "Протечки нет", sets::Colors::Green);
        b.Label(H(wlew), "ADC");

        /*static bool bb = false;
        if (b.Button("Water Out"))
        {
            bb = !bb;
            waterAlarm(bb);
        }*/

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
                b.Slider(kk::water_time_1, "Время полива", 0, 10, 1, "сек.");
            }

            {
                sets::Group r(b, "Вторая группа");
                //b.Slider("Влажность полива", 0, 100, 1, "%");
                b.Slider2(kk::hum_min1, kk::hum_max1, "Влажность полива", 0, 100, 1, "%");
                b.Slider(kk::water_time_2, "Время полива", 0, 10, 1, "сек.");
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
                    bool v = false;
                    v |= b.Input(kk::tg_id, "Chat ID");
                    v |= b.Pass(kk::tg_token, "Token");
                    if(v) tg::init();
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
