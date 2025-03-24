#pragma once

#include <FastBot.h>

#include "db.h"

#include "sensor/waterLevel.h"
#include "sensor/sens.h"

namespace tg
{
    FastBot bot;

    void sendHello()
    {
        if (db::db[kk::tg_en])
        {
            //String menu1 = F("Полить_1 \t Полить_2 \t Test \n Получить_данные");
            //String call1 = F("water_1,water_2,https://alexgyver.ru/,get_data");
            //bot.inlineMenuCallback("Привет. Я автополив.", menu1, call1);
            bot.sendMessage("Привет. Я автополив.");
            bot.showMenu("Полить 1 \t Полить 2 \n Получить данные");
        }
    }

    void newMsg(FB_msg &msg)
    {
        if(msg.query) Serial.println("123");
        Serial.println(msg.toString());

        if (msg.text == "Полить 1")
        {
            sensor::water(0);
        }
        else if (msg.text == "Полить 2")
        {
            sensor::water(1);
        }
        else if (msg.text == "Получить данные")
        {
            bot.sendMessage(
                "Влажность 1: " + (String)sensor::sens[0]->getWater() + "%\n"
                "Влажность 2: " + (String)sensor::sens[1]->getWater() + "%\n"
                "Уровень воды: " + sensor::get_waterLevel() + "%\n");
        }

        /*if (msg.data == "water_1")
        {
            sensor::water(0);
        }
        else if (msg.data == "water_2")
        {
            sensor::water(1);
        }
        else if (msg.data == "get_data")
        {
            bot.sendMessage(
                "Влажность 1: " + (String)sensor::sens[0]->getWater() + "%\n"
                "Влажность 2: " + (String)sensor::sens[1]->getWater() + "%\n"
                "Уровень воды: " + sensor::get_waterLevel() + "%\n");
        }*/
    }

    void init()
    {
        if (db::db[kk::tg_en])
        {
            bot.setChatID(db::db[kk::tg_id].toString());
            bot.setToken(db::db[kk::tg_token].toString());
            bot.attach(newMsg);
            sendHello();
        }
    }

    void tick()
    {
        if (db::db[kk::tg_en])
            bot.tick();
    }

    void send_waterAlarm()
    {
        if (db::db[kk::tg_en])
            bot.sendMessage("Water alarm!");
    }
}