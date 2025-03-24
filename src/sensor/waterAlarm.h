#pragma once

#include <Arduino.h>

namespace sensor {
    bool waterAlarm_bool = false;
    
    void init_waterAlarm() {

    }

    bool get_waterAlarm() {
        static long timer = 0;
        long mil = millis();
        if(mil - timer >= 500) {
            timer = mil;
            waterAlarm_bool = random(20) != 0;
        }
        return waterAlarm_bool;
    }
}