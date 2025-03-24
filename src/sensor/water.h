#pragma once

#include <CrazyMgBot.h>
#include "../settings.h"

namespace sensor {
    CMB::MGR_2I2C relay(RELAY_PORT);

    void init_water() {
        Wire.begin();
        relay.begin();
        relay.setPin(0, 0);
        relay.setPin(1, 0);
    }

    void water(byte id) {
        relay.setPin(id, 1);
        delay(WATER_TIME);
        relay.setPin(id, 0);
    }
}