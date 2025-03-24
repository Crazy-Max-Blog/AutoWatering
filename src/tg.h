#pragma once

#include <FastBot.h>

#include "db.h"

namespace tg {
    FastBot bot;

    void init() {
        if (db::db[kk::tg_en])
        {
            bot.setChatID(db::db[kk::tg_id].toString());
            bot.setToken(db::db[kk::tg_token].toString());
        }
    }

    void tick() {
        if(db::db[kk::tg_en]) bot.tick();
    }

    void send_waterAlarm() {
        if(db::db[kk::tg_en]) bot.sendMessage("Water alarm!");
    }
}