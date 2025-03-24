#pragma once

#include <Arduino.h>

#include "../settings.h"

#include "setts.h"

#include "waterAlarm.h"

#include "waterSensorBase.h"
#include "waterSensorI2C.h"
#include "waterSensorADC.h"
#include "waterLevel.h"
#include "water.h"

namespace sensor {
    waterSensorBase* sens[] = {new waterSensorADC(WATER_PORT_FIRST), new waterSensorI2C(WATER_PORT_SECOND)};
    void init() {
        init_waterAlarm();
        init_waterLevel();
        sens[0]->init();
        sens[1]->init();
        init_water();
    }

    void tick() {
        {
            static bool b = false;
            bool v = get_waterAlarm();
            if(v && !b) {
                b = true;
                setts::waterAlarm(true);
                tg::send_waterAlarm();
            } else if(!v && b) {
                b = false;
                setts::waterAlarm(false);
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
        }
    }
}