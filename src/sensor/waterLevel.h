#pragma once

#include <Arduino.h>

namespace sensor {
    byte water_level_pin = 1;

    void init_waterLevel() {
        
    }

    byte get_waterLevel() {
        return constrain(map(analogRead(33), 3900, 3000, 0, 100), 0, 100);//random(100);
    }
}