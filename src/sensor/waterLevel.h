#pragma once

#include <Arduino.h>

namespace sensor {
    byte water_level_pin = 1;

    void init_waterLevel() {
        
    }

    byte get_waterLevel() {
        return random(100);
    }
}