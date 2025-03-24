#pragma once

#include <CrazyMgBot.h>

namespace sensor {
    CMB::MGR_2I2C relay(7);

    void init_water() {
        Wire.begin();
        relay.begin();
        relay.setPin(0, 0);
        relay.setPin(1, 0);
    }

    void water(byte id) {
        relay.setPin(id, 1);
        delay(1000);
        relay.setPin(id, 0);
    }
}