#pragma once

#include <Arduino.h>

#include "../settings.h"

#include "setts.h"

#include "waterAlarm.h"
#include "waterLevel.h"
#include "water.h"
#include "sens.h"
#include "mqtt.h"

namespace sensor {
    void init() {
        init_waterAlarm();
        init_waterLevel();
        sens[0]->init();
        sens[1]->init();
        init_water();
    }

    void tick() {
        tick_water();
        {
            static bool b = false;
            bool v = get_waterAlarm();
            if(v && !b) {
                b = true;
                setts::waterAlarm(true);
                mqtt::waterAlarm(true);
                tg::send_waterAlarm();
            } else if(!v && b) {
                b = false;
                setts::waterAlarm(false);
                mqtt::waterAlarm(false);
            }
        }
        static long timer = 0;
        long mil = millis();
        if (mil - timer >= 500)
        {
            timer = mil;
            
            setts::sendData(
                sens[0]->getWater(),
                sens[1]->getWater(),
                get_waterLevel()
            );
            
            mqtt::sendData(
                sens[0]->getWater(),
                sens[1]->getWater(),
                get_waterLevel()
            );
        }
    }
}